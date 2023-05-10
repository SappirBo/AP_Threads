#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include "../include/dataChunk.h"

/*
Test File for the Chunks struct and functions.

Run with: gcc -o chunks testDataChuncks.c ../include/dataChunk.h ../src/dataChunck.c 
*/


int main()
{
    printf("DEBUG: ChunkTester 0. Run Test for chunks.\n");
    dataChunk* head = (dataChunk *) malloc(sizeof(dataChunk));
    printf("DEBUG: ChunkTester 1.\n");
    int ch_num = getData_fromFile(head, "data/az.txt");
    printf("DEBUG: ChunkTester 2, Chunk Size = %d\n", ch_num);
    writeDataToFile(head,ch_num,"data/result.txt");
    printf("DEBUG: ChunkTester 3.\n");

    freeData(head,ch_num);
    return 0;
}