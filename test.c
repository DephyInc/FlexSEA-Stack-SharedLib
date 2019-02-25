#include "flexsea_multi_circbuff.h"
#include "flexsea_comm_multi.h"
#include "flexsea_circular_buffer.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define NUM_FRAMES_TEST 4
#define NUM_BYTES_FRAME 50
#define MAX_NUM_TEST 1000000
#define DO_PRINT 0

uint8_t test(void)
{
	// start with a smaller example
	MultiWrapper testWrapper;
	circularBuffer_t cb;
	circ_buff_init(&cb);
	uint8_t message[NUM_FRAMES_TEST*NUM_BYTES_FRAME];
	uint8_t bufferMessage[NUM_FRAMES_TEST*NUM_BYTES_FRAME + 5*NUM_FRAMES_TEST + 50];
	uint8_t intermediateBuffer[NUM_FRAMES_TEST*NUM_BYTES_FRAME + 5*NUM_FRAMES_TEST + 50];
	testWrapper.unpackedIdx = NUM_FRAMES_TEST*NUM_BYTES_FRAME;
	srand(time(0));
	for(int frame = 0; frame < NUM_FRAMES_TEST; frame ++)
	{
		for(int byte_val = 0; byte_val < NUM_BYTES_FRAME;byte_val++)
		{
			message[frame * NUM_BYTES_FRAME + byte_val] = byte_val; //(uint8_t)(rand() % 255); 
			testWrapper.unpacked[frame * NUM_BYTES_FRAME + byte_val] = message[frame * NUM_BYTES_FRAME + byte_val];
		}
	}
	#if DO_PRINT
	for(int j = 0; j < NUM_BYTES_FRAME ; j++){printf("%u ",message[j]);}
	printf("\n");
	#endif
	packMultiPacket(&testWrapper);
	uint8_t num_frames = 0;
	for(num_frames = 0; num_frames < MAX_FRAMES_PER_MULTI_PACKET &&  (testWrapper.frameMap >> num_frames) > 0;num_frames++);
	int total_bytes = 0;
	for(int frame = 0; frame < num_frames; frame ++)
	{	
		int numBytes = testWrapper.packed[frame][1];
		#if DO_PRINT
		for(int j = 0; j < numBytes +5; j++){printf("%u ",testWrapper.packed[frame][j]);}
		printf("\n");
		#endif
		for(int j = 0; j < numBytes +5; j++){intermediateBuffer[j] = testWrapper.packed[frame][j];} //{printf("%u ",testWrapper.packed[frame][j]);}
		uint8_t start = 0;
		circ_buff_write(&cb,intermediateBuffer,(numBytes + 5));
		total_bytes += (numBytes + 5);
	}
	
	circ_buff_read(&cb,bufferMessage, total_bytes);
	#if DO_PRINT
	for(int j = 0; j < total_bytes; j++){printf("%u ",bufferMessage[j]);}
	printf("\n");
	#endif
	for(int frame = 0; frame < NUM_FRAMES_TEST; frame ++)
	{
		for(int byte_val = 0; byte_val < NUM_BYTES_FRAME;byte_val++)
		{
			testWrapper.unpacked[frame * NUM_BYTES_FRAME + byte_val] = 0;
		}
	}
	
	unpack_multi_payload_cb(&cb,&testWrapper);
	

	uint8_t result = 1;
	for(int i =0; i < testWrapper.unpackedIdx; i ++){result |= (testWrapper.unpacked[i] == message[i]);}
	return result;
}

int main()
{
   // printf() displays the string inside quotation
   uint8_t results = 1, numFailures = 0;
   for( int test_case = 0; test_case < MAX_NUM_TEST; test_case++)
   {
	   #if DO_PRINT
	   printf("********** TEST %u of %u COMMENCING ***********\n", test_case,MAX_NUM_TEST );
	   #endif
	   uint8_t result = test();
	   
	   if(result == 0)
	   {
		   printf("Test %u FAILED\n", test_case);
		   numFailures++;
	   }
	
	}
	printf("In total there were %u failures\n",numFailures);
   return 0;
}

