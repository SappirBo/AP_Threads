/*
File: dataChunck.c
Author: Sappir Bohbot
Date: 5/12/2023.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>

#include "../include/dataChunk.h"


int getData_stdIn(dataChunk *headChunk){
	dataChunk* ptrData = headChunk;
	char c;
	int counter = 0;
	int chunckNum = 1;
	int dest_size = Max_Size_Data;
	char data[dest_size];
	while ((c = getchar()) != EOF)
	{
	  data[counter] = c;
	  counter++;

	  if (counter == Max_Size_Data){
		ptrData->num = chunckNum;
		strcpy(ptrData->data, data);
		ptrData->next = (dataChunk *) malloc(sizeof(dataChunk));
		ptrData = ptrData->next; 
		
		counter = 0;
		chunckNum++;
	  }
	}
	if(counter > 0){
		char lastData[counter];
		ptrData->num = chunckNum;
		ptrData->data[0] = '\0';
		strncat(ptrData->data, data, counter);
		ptrData = ptrData->next; 
	}

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
	int chunckNum = 1;
	int dest_size = Max_Size_Data;
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

	  if (counter == Max_Size_Data){
		ptrData->num = chunckNum;
		strcpy(ptrData->data, data);
		ptrData->next = (dataChunk *) malloc(sizeof(dataChunk));
		ptrData = ptrData->next; 
		
		counter = 0;
		chunckNum++;
	  }
	}
	if(counter > 0){
		char lastData[counter];
		lastData[0] = '\0';
		ptrData->num = chunckNum;
		strncat(lastData, data, counter);
		strcpy(ptrData->data, lastData);
		ptrData->data[counter] = '\0';
	}
	fclose(fp);
	return chunckNum;
}

int writeDataToFile(dataChunk *_headChunk, int _chunk_amount, char* _filePath){
	FILE *fp;
    dataChunk* ptr = _headChunk;
	// printf("[writeDataToFile] _chunks amout: %d\n",_chunk_amount);
	if(!strcmp(_filePath,"send_to_std"))
	{
		fp = stdout;
	}
	else
	{
		fp = fopen(_filePath, "w");
		if (fp == NULL)
		{
			perror("Error opening file");
			return 0;
		}
	}
    
    int count = 0;
	
	while(count<_chunk_amount)
	{
		// printf("[writeDataToFile] count: %d, ptr num: %d\n",count, ptr->num);
		size_t length = strlen(ptr->data);
		size_t numChars = (length < Max_Size_Data) ? length : Max_Size_Data;

		fwrite(ptr->data, sizeof(char), numChars, fp);
		
		count++;
		ptr = ptr->next;
	}
    
    fclose(fp);
	return 1;
}









