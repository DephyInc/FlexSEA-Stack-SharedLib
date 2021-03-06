/****************************************************************************
	[Project] FlexSEA: Flexible & Scalable Electronics Architecture
	[Sub-project] 'flexsea-execute' Advanced Motion Controller
	Copyright (C) 2016 Dephy, Inc. <http://dephy.com/>

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*****************************************************************************
	[Lead developper] Jean-Francois Duval, jfduval at dephy dot com.
	[Origin] Based on Jean-Francois Duval's work at the MIT Media Lab 
	Biomechatronics research group <http://biomech.media.mit.edu/>
	[Contributors]
*****************************************************************************
	[This file] trapez: trapezoidal trajectory generation
*****************************************************************************
	[Change log] (Convention: YYYY-MM-DD | author | comment)
	* 2016-09-29 | jfduval | Released under GPL-3.0 release
	*
****************************************************************************/

//****************************************************************************
// Include(s)
//****************************************************************************

//Comment the next line to use in your application:
//#define DEBUGGING_OUTPUT

#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include "trapez.h"


#ifdef __cplusplus
extern "C" {
#endif

//****************************************************************************
// Local variable(s)
//****************************************************************************

//Common variables - careful, do not change "manually"!
long long d_pos = 0, d_spd = 0, a_t = 0, a_t_discrete = 0, spd_inc = 0;
long long acc_pos = 0, acc = 0;
long long init_pos = 0, cte_spd_pos = 0, cte_spd_pos_discrete = 0;
long long skip_sspeed = 0;
long long pos_step = 0;
long long trapez_transitions[3] = {0,0,0};
long long sign = 0;

int use_smooth = 0, no_trap = 0;
long long no_trap_pos = 0;
long long smooth_A = 0, smooth_pos_i = 0, smooth_pos_f = 0, smooth_max_steps = 0, smooth_t = 0;

//****************************************************************************
// Shared Variable(s):
//****************************************************************************

int32_t steps;

//****************************************************************************
// Private Function Prototype(s):
//****************************************************************************

static long long trapez_compute_params(long long pos_i, long long pos_f, \
										long long spd_max, long long a);

//****************************************************************************
// Public Function(s)
//****************************************************************************

//Based on trapez_motion_2.m
//Assumes 0 initial speed
long long trapez_gen_motion_1(long long pos_i, long long pos_f, \
								long long spd_max, long long a)
{
	smooth_t = 0;  
	use_smooth = 0;
	no_trap = 0;
	
	if (a<=10)
	{
		if (spd_max <= 1)
		{
			no_trap_pos = pos_f;
			no_trap = 1;
			return spd_max;
		}
		trapez_gen_smooth_motion_1(pos_i,pos_f,spd_max);
		use_smooth = 1;
		return spd_max;
	}
	
	
	long long abs_d_pos = 0, abs_acc_pos = 0, dual_abs_acc_pos = 0;

	//spd_max & a have to be positive
	spd_max = llabs(spd_max);
	a = llabs(a);

	//Compute parameters (in global variables)
	trapez_compute_params(pos_i, pos_f, spd_max, a);

	//Absolute values
	abs_d_pos = llabs(d_pos);
	abs_acc_pos = llabs(acc_pos);
	dual_abs_acc_pos = 2*abs_acc_pos;

	#ifdef DEBUGGING_OUTPUT
	printf("d_pos = %lld, abs_d_pos = %lld.\n", d_pos, abs_d_pos);
	printf("1) acc_pos = %lld, abs_acc_pos = %lld.\n", acc_pos, abs_acc_pos);
	#endif

	//It's possible to overshoot position if the acceleration is too low.
	//In that case we should sacrifice the top speed
	if(dual_abs_acc_pos > abs_d_pos)
	{
		#ifdef DEBUGGING_OUTPUT
		printf("Position overshoot.\n");
		#endif

		//New top speed:
		spd_max = sqrt(a*abs_d_pos);
		#ifdef DEBUGGING_OUTPUT
		printf("New spd_max: %lld.\n", spd_max);
		#endif

		//Redo the initial math:
		//Compute parameters (in global variables)
		trapez_compute_params(pos_i, pos_f, spd_max, a);

		//Absolute values (they probably changed)
		abs_d_pos = abs(d_pos);
		abs_acc_pos = abs(acc_pos);
		dual_abs_acc_pos = 2*abs_acc_pos;
	}

	//Plateau - constant speed
	#ifdef DEBUGGING_OUTPUT
	printf("d_pos = %lld, abs_d_pos = %lld.\n", d_pos, abs_d_pos);
	printf("2) acc_pos = %lld, abs_acc_pos = %lld.\n", acc_pos, abs_acc_pos);
	#endif

	cte_spd_pos = abs_d_pos - (2*abs_acc_pos);
	cte_spd_pos_discrete = (SPD_FACTOR*cte_spd_pos/spd_max)*TRAPEZ_ONE_OVER_DT;
	cte_spd_pos_discrete = cte_spd_pos_discrete / SPD_FACTOR;
	#ifdef DEBUGGING_OUTPUT
	printf("cte_spd_pos = %lld, cte_spd_pos_discrete = %lld.\n", cte_spd_pos, \
			cte_spd_pos_discrete);
	#endif
	if(cte_spd_pos_discrete < 0)
	{
		cte_spd_pos_discrete = 0;
		#ifdef DEBUGGING_OUTPUT
		printf("No steady speed!\n");
		#endif
	}

	//Transitions:
	trapez_transitions[0] = a_t_discrete;
	trapez_transitions[1] = a_t_discrete + cte_spd_pos_discrete;
	trapez_transitions[2] = 2*a_t_discrete + cte_spd_pos_discrete;
	#ifdef DEBUGGING_OUTPUT
	printf("tr[0] = %lld, tr[1] = %lld, tr[2] = %lld.\n", trapez_transitions[0], \
			trapez_transitions[1], trapez_transitions[2]);
	#endif
	pos_step = 0;   //Variable used to output the current position command

	return (2*a_t_discrete + cte_spd_pos_discrete); //Returns the number of steps
}

//Runtime function - gives the next position setpoint
long long trapez_get_pos(long long max_steps)
{
	static long long tmp_spd = 0, last_tmp_spd = 0, tmp_pos = 0;
	long long position = 0;
	static long long pos_integral = 0;

	//At this point all the parameters are computed, we can get the 3 plots

	smooth_t++;
	if (use_smooth)
	{
		if (smooth_t<=smooth_max_steps/2)
		{
			position = smooth_A*smooth_t*smooth_t/smooth_max_steps/smooth_max_steps+smooth_pos_i;
		}
		else if (smooth_t<=smooth_max_steps)
		{
			position = smooth_pos_f - smooth_A*(smooth_max_steps-smooth_t)*(smooth_max_steps-smooth_t)/smooth_max_steps/smooth_max_steps;
		}
		else
		{
			position = smooth_pos_f;
		}
		return position;
	}
	else if (no_trap)
	{
		position = no_trap_pos;
		return position;
	}
	
	//First time:
	if(pos_step == 0)
	{
		tmp_spd = 0;
		last_tmp_spd = 0;
		tmp_pos = 0;
		pos_integral = 0;
		#ifdef DEBUGGING_OUTPUT
		printf("pos_step = 0, pos_integral = %lld.\n", pos_integral);
		#endif
	}

	//Acceleration:
	if(pos_step <= trapez_transitions[0])
	{
		last_tmp_spd = tmp_spd;
		tmp_spd = last_tmp_spd + spd_inc;
	}
	//if(skip_sspeed == 0)	//ToDo useful?
	{
		//Constant speed
		//last_tmp_spd = tmp_spd;
		if((pos_step >= trapez_transitions[0]) && (pos_step <= trapez_transitions[1]))
		{
			tmp_spd = last_tmp_spd;
		}
	}
	//Negative Acceleration:
	if((pos_step >= trapez_transitions[1]) && (pos_step <= trapez_transitions[2]))
	{
		last_tmp_spd = tmp_spd;
		tmp_spd = last_tmp_spd - spd_inc;
	}

	if(pos_step <= max_steps)
	{
		//Ready for next one.
		pos_step++;

		//Common math:
		pos_integral += tmp_spd;
		tmp_pos = pos_integral/(TRAPEZ_ONE_OVER_DT * SPD_FACTOR);
		position = tmp_pos + init_pos;
		#ifdef DEBUGGING_OUTPUT
		if(pos_step < 10)
			printf("pos_step = %lld, pos_integral = %lld, position = %lld.\n", \
					pos_step, pos_integral, position);
		#endif
	}
	else
	{
		position = tmp_pos + init_pos;
	}

	//New setpoint
	return position;
}

//****************************************************************************
// Private Function(s)
//****************************************************************************

//Computes all the parameters for a new trapezoidal motion trajectory
//Called by trapez_gen_motion_1()
static long long trapez_compute_params(long long pos_i, long long pos_f, \
										long long spd_max, long long a)
{
	long long tmp = 0, i = 0;

	//Sign
	if(pos_f < pos_i)
		sign = -1;
	else
		sign = 1;

	acc = a;
	init_pos = pos_i;
	d_pos = pos_f - pos_i;								  //Difference in position
	d_spd = spd_max ;									   //Difference in speed
	a_t = (ACC_FACTOR*d_spd) / a;						   //How long do we accelerate?
	a_t_discrete = a_t * TRAPEZ_ONE_OVER_DT / ACC_FACTOR;   //   (in ticks)
	//a_t_discrete = a_t; //Simplification of *100/100
	spd_inc = (sign*SPD_FACTOR*d_spd) / a_t_discrete;	   //Every tick, increase spd by
	#ifdef DEBUGGING_OUTPUT
	printf("d_spd = %lld, a_t_discrete = %lld, spd_inc = %lld, d_pos = %lld.\n", \
			d_spd, a_t_discrete, spd_inc, d_pos);
	#endif

	acc_pos = 0;
	for(i = 0; i < a_t_discrete; i++)
	{
		tmp += spd_inc; //tmp = i*spd_inc;
		acc_pos = acc_pos + tmp;
	}
	acc_pos = acc_pos / (SPD_FACTOR * TRAPEZ_ONE_OVER_DT); //Combine terms
	#ifdef DEBUGGING_OUTPUT
	printf("acc_pos = %lld (2x = %lld), %f%% of d_pos.\n", acc_pos, (2*acc_pos), \
			(float)(2*acc_pos*100/d_pos));
	#endif

	return 0;
}

void trapez_gen_smooth_motion_1(long long pos_i,long long pos_f,long long spd_max)
{	
	smooth_pos_i = pos_i;
	smooth_pos_f = pos_f;
	smooth_A = 2*smooth_pos_f-2*smooth_pos_i;
	smooth_max_steps = spd_max;	
}

#ifdef __cplusplus
}
#endif
