#include "../include/codec.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
	    printf("usage: key < file \n");
	    printf("!! data more than 1024 char will be ignored !!\n");
	    return 0;
	}

	int key = atoi(argv[1]);
	printf("key is %i \n",key);
	clock_t start_time, end_time;
    double execution_time;

	char c;
	int counter = 0;
	int dest_size = 1024;
	char data[dest_size]; 
	
	// Start measuring time
    start_time = clock();

	while ((c = getchar()) != EOF)
	{
	  data[counter] = c;
	  counter++;

	  if (counter == 1024){
		encrypt(data,key);
		// printf("encripted data: %s\n",data);
		printf("Block\n");
		counter = 0;
	  }
	}
	
	if (counter > 0)
	{
		char lastData[counter];
		lastData[0] = '\0';
		strncat(lastData, data, counter);
		encrypt(lastData,key);
		// printf("encripted data:\n %s\n",lastData);
		printf("Block\n");
	}

	// End measuring time
    end_time = clock();

    // Calculate the execution time in seconds
    execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    printf("Execution time: %.6f seconds\n", execution_time);

	return 0;
}