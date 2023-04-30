#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../include/dataChunk.h"
#include "../include/threadpool.h"
#include "../include/codec.h"

/*Variable declaration*/
# define MAX_SIZE 1024
typedef void (*crypto_fn)(char *s,int key);

/*Function for oparate encrypt/decrypt, 
Params:
	(flag = false) => encrypt.
	(flag = true) => decrypt.
	_head => StartPoint for the Chunks.
*/
static void _operateAction(dataChunk* _ptrCh, bool _flag, int _crypt_key);


int main(int argc, char *argv[])
{
	/*Check for valid amount of arguments, expect 5 arguments exactly.*/
	if (argc < 5)
	{
	    printf("Eror: missing arguments!, %d/5 found.\n",argc);
	    return 0;
	}
	else if (argc > 5)
	{
	    printf("Eror: to much arguments!, %d/5 found.\n",argc);
	    return 0;
	} 

	/*Parse input arguments
		1. Key for the encrypt/decrypt
		2. flag (e/d) for encrypt/decrypt
		3. {source file name}  OR ">" for pipe.
		4. {destination file name}. 
	*/
	int key = atoi(argv[1]);
    char flag[MAX_SIZE];
	bool operate_flag;
    char source_file[MAX_SIZE];
    char dest_file[MAX_SIZE];
    strcpy(flag, argv[2]);
    strcpy(source_file,argv[3]);
    strcpy(dest_file,argv[4]);
	

    
    if(!strcmp(flag,"-d"))
    {
		operate_flag = true;  
    }
    else if(!strcmp(flag,"-e"))
    {
		operate_flag = false; 
    }
    else
    {
        printf("Flag is UNKNOWN.\n");
        return 0;
    }

    // printf("Source: %s, Dest: %s\n",source_file,dest_file);

	char c;
	int counter = 0;
	int dest_size = MAX_SIZE;
	char data[dest_size]; 
	dataChunk* _headCh = (dataChunk*)malloc(sizeof(dataChunk));
	int num_of_chunks = 0;

	if(!(strcmp(source_file,">")))
	{
		num_of_chunks = getData_stdIn(_headCh);
	}
	else
	{
		num_of_chunks = getData_fromFile(_headCh,source_file);
	}
	int i=0;
	dataChunk* _ptrCh = _headCh;
	
	while(i<=num_of_chunks)
	{
		_operateAction(_ptrCh,operate_flag,key);
		_ptrCh = _ptrCh->next;
		i++;
	}
	


	writeDataToFile(_headCh,num_of_chunks,dest_file);

	return 0;
}


void _operateAction(dataChunk* _ptrCh, bool _flag, int _crypt_key)
{
	// Updating crypto_fn to be the right function according to the operation flag.
	crypto_fn fn = NULL;
	if (_flag) {
		fn = decrypt;
    } else {
		fn = encrypt;
    }

	fn(_ptrCh->data, _crypt_key);
}