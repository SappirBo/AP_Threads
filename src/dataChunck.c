#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../include/dataChunk.h"


int getData(dataChunk *headChunk,char* path){
	printf("getData1\n");
	dataChunk* ptrData = headChunk;
	printf("getData2\n");
	char c;
	int counter = 0;
	int chunckNum = 0;
	int dest_size = 1024;
	char data[dest_size];
	printf("getData3\n");
	while ((c = getchar()) != EOF)
	{
	  data[counter] = c;
	  counter++;

	  if (counter == 1024){
		printf("DEBUG: Size=1024,ChunkNUmber: %d Data = %s\n",chunckNum, data);
		ptrData->num = chunckNum;
		strcpy(ptrData->data, data);
		printf("DEBUG:------------------------- HERE\n");
		ptrData->next = (dataChunk *) malloc(sizeof(dataChunk));
		ptrData = ptrData->next; 
		
		counter = 0;
		chunckNum++;
	  }
	}
	printf("getData4\n");
	// if(counter > 0){
	// 	char lastData[counter];
	// 	ptrData->num = chunckNum;
	// 	ptrData->data[0] = '\0';
	// 	strncat(ptrData->data, data, counter);
	// 	ptrData = ptrData->next; 
	// }
	printf("getData5");

	return chunckNum;
}


void printChunks(dataChunk *headChunk, int size){
	dataChunk *ptr = headChunk; 
	int counter = 0;
	while(counter<size)
	{
		printf("%d)--------------------------------------------------------------------------------------------------------------\n",counter++);
		printf("%s\n",ptr->data);
		ptr = ptr->next;
	}
}


void freeData(dataChunk *headChunk,int size){
	int counter = 0;
	dataChunk* curr = headChunk;
	dataChunk* tmp = curr;

	while (curr->next != NULL && counter <size)
	{
		tmp = curr;
		curr = curr->next;
		free(tmp);
	}
}

