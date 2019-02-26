#include "flexsea_multi_circbuff.h"
#include "flexsea_comm_multi.h"
#include "flexsea_circular_buffer.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define TOTAL_DATA (3*120)
#define MAX_NUM_TEST 1
#define DO_PRINT 1
#define PRINTN(message_array) printf("***** %s ******\n",message_array);

uint8_t test(void)
{
	// start with a smaller example
	MultiWrapper testWrapper;
	circularBuffer_t cb;
	circ_buff_init(&cb);
	uint8_t message[TOTAL_DATA];
	uint8_t bufferMessage[2*TOTAL_DATA + 5*(TOTAL_DATA/150)];
	uint8_t intermediateBuffer[2*TOTAL_DATA + 5*(TOTAL_DATA/150)];
	testWrapper.unpackedIdx = TOTAL_DATA;
	for(int byte_val = 0; byte_val < TOTAL_DATA; byte_val++)
	{
		message[byte_val] = (uint8_t)(rand() % 255); //byteVal
		testWrapper.unpacked[byte_val] = message[byte_val];
	}
	#if DO_PRINT
	PRINTN("Original message");
	for(int j = 0; j < TOTAL_DATA ; j++){printf("%u ",message[j]);}
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
		PRINTN("Packed Frame");
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
	PRINTN("Message in circular buffer");
	for(int j = 0; j < total_bytes; j++){printf("%u ",bufferMessage[j]);}
	printf("\n");
	#endif
	for(int byte_val = 0; byte_val < TOTAL_DATA; byte_val ++)
	{
		testWrapper.unpacked[byte_val] = 0;
	}
	
	unpack_multi_payload_cb(&cb,&testWrapper);
	

	uint8_t result = 1;
	#if DO_PRINT
	PRINTN("Received message");
	for(int i =0; i < testWrapper.unpackedIdx; i ++){printf("%u ", testWrapper.unpacked[i]);}
	printf("\n");
	#endif

	
	for(int i =0; i < testWrapper.unpackedIdx; i ++){result &= (testWrapper.unpacked[i] == message[i]);}
	result &= (testWrapper.unpackedIdx == TOTAL_DATA);
	return result;
}

int main()
{
   // printf() displays the string inside quotation
   uint8_t results = 1, numFailures = 0;
   srand(time(0));
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

