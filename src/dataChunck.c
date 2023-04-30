#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>

#include "../include/dataChunk.h"


int getData_stdIn(dataChunk *headChunk){
	dataChunk* ptrData = headChunk;
	char c;
	int counter = 0;
	int chunckNum = 0;
	int dest_size = 1024;
	char data[dest_size];
	while ((c = getchar()) != EOF)
	{
	  data[counter] = c;
	  counter++;

	  if (counter == 1024){
		ptrData->num = chunckNum;
		strcpy(ptrData->data, data);
		ptrData->next = (dataChunk *) malloc(sizeof(dataChunk));
		ptrData = ptrData->next; 
		
		counter = 0;
		chunckNum++;
	  }
	}
	printf("getData4\n");
	if(counter > 0){
		printf("	counter = %d, Chunck number = %d\n", counter, chunckNum);
		char lastData[counter];
		ptrData->num = chunckNum;
		ptrData->data[0] = '\0';
		strncat(ptrData->data, data, counter);
		ptrData = ptrData->next; 
	}
	printf("getData5\n");

	return chunckNum;
}

void printChunks(dataChunk *headChunk, int size){
	dataChunk *ptr = headChunk; 
	int counter = 0;
	while(counter<=size)
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

void print_Chunck_Data(dataChunk *headChunk,int size){

	dataChunk *ptr = headChunk; 
	int counter = 0;
	while(counter<size)
	{
		printf("%d)--------------------------------------------------------------------------------------------------------------\n",counter++);
		printf("	chunk number: %d\n",ptr->num);
		printf("	chunk size: %ld\n", strlen(ptr->data));
		ptr = ptr->next;
	}
}

int getData_fromFile(dataChunk *headChunk,char* path)
{
	dataChunk* ptrData = headChunk;
	char c;
	int counter = 0;
	int chunckNum = 0;
	int dest_size = 1024;
	char data[dest_size];

	FILE *fp;

    fp = fopen(path, "r");
    if (fp == NULL) 
	{
        perror("Error opening file");
        return 1;
    }


	while ((c = fgetc(fp)) != EOF)
	{
	  data[counter] = c;
	  counter++;

	  if (counter == 1024){
		ptrData->num = chunckNum;
		strcpy(ptrData->data, data);
		ptrData->next = (dataChunk *) malloc(sizeof(dataChunk));
		ptrData = ptrData->next; 
		
		counter = 0;
		chunckNum++;
	  }
	}
	printf("getData4\n");
	if(counter > 0){
		printf("	counter = %d, Chunck number = %d\n", counter, chunckNum);
		char lastData[counter];
		lastData[0] = '\0';
		ptrData->num = chunckNum;
		strncat(lastData, data, counter);
		strcpy(ptrData->data, lastData);
		ptrData->data[counter] = '\0';
	}
	printf("getData5\n");
	fclose(fp);
	return chunckNum;
}

int writeDataToFile(dataChunk *_headChunk, int _chunk_amount, char* _filePath){
	FILE *fp;
    dataChunk* ptr = _headChunk;

    fp = fopen(_filePath, "w");
    if (fp == NULL)
	{
        perror("Error opening file");
        return 0;
    }
    int count = 0;
	while(count<=_chunk_amount)
	{
		fputs(ptr->data, fp);
		count++;
		ptr = ptr->next;
	}
    
    fclose(fp);
	return 1;
}









