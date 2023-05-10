#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "../include/dataChunk.h"
#include "../include/threadpool.h"
#include "../include/codec.h"

/*threads arguments*/
typedef struct _thread_args {
    dataChunk* arg_ptrCh;
	bool arg_flag;
	int arg_crypt_key;
} thread_args_t;


/*Variable declaration*/
# define MAX_SIZE 1024
typedef void (*crypto_fn)(char *s,int key);

/*Function for oparate encrypt/decrypt, 
Params:
	(flag = false) => encrypt.
	(flag = true) => decrypt.
	_head => StartPoint for the Chunks.
*/
static void _operateAction(void* args);

const int ARGC_FOR_PIPE = 3;
const int ARGC_FOR_SRC_AND_DEST = 5;

int main(int argc, char *argv[])
{

	/*Check for valid amount of arguments, expect 5 arguments exactly.*/
	if (argc != ARGC_FOR_SRC_AND_DEST && argc != ARGC_FOR_PIPE)
	{
	    printf("[Error]: missing arguments!, %d/5 found.\n",argc);
		for(int i=0; i<argc; ++i)
		{
			printf("[Error] Arg %i = %s\n",i, argv[i]);
		}
	    return 0;
	}
	else if (argc > ARGC_FOR_SRC_AND_DEST)
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
	if(argc==ARGC_FOR_SRC_AND_DEST)
	{
		// This argv will have values only if it is not piped.
		strcpy(source_file,argv[3]);
		strcpy(dest_file,argv[4]);
	}else{
		strcpy(dest_file,"send_to_std");
	}
	
	// Find out what oporate to do: encrypt or decrypt.
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
        printf("[Error] Flag is UNKNOWN: flag = %s, Try again...\n",flag);
        return 0;
    }
	
	char c;
	int counter = 0;
	int dest_size = MAX_SIZE;
	char data[dest_size]; 
	dataChunk* _headCh = (dataChunk*)malloc(sizeof(dataChunk));
	int num_of_chunks = 0;

	if(argc == ARGC_FOR_PIPE)
	{
		num_of_chunks = getData_stdIn(_headCh);
	}
	else
	{
		num_of_chunks = getData_fromFile(_headCh,source_file);
	}

	dataChunk* _ptrCh = _headCh;
	//Setting up the threadpool
	tpool_t *tm;
	tm = tpool_create(num_of_chunks);
	// adding chunks to different threads.
	int i=0;
	thread_args_t* th_args = malloc(num_of_chunks * sizeof(thread_args_t));
	if (th_args == NULL) {
		// Error handling for memory allocation failure
		printf("Error: Failed to allocate memory for th_args\n");
		return -1;
	}

	while(i<num_of_chunks)
	{
		//setting args variable for the thread. 
		th_args[i].arg_ptrCh = _ptrCh;
		th_args[i].arg_flag = operate_flag;
		th_args[i].arg_crypt_key = key;
		// add thread
        if(tpool_add_work(tm, _operateAction, th_args + i) == false){
			printf("Threadpool error: thread couldnt added to work\n");
			break;
		}
		
		_ptrCh = _ptrCh->next;
		i++;
	}
	
	tpool_wait(tm);

	sleep(1);

	tpool_destroy(tm);

	writeDataToFile(_headCh,num_of_chunks,dest_file);

	free(th_args);
	return 0;
}


void _operateAction(void* args)
{
	thread_args_t* _arg = (thread_args_t*) args;
    dataChunk* _ptrCh = _arg->arg_ptrCh;
    bool _flag = _arg->arg_flag;
    int _crypt_key = _arg->arg_crypt_key;

	// printf("[_operateAction] Chunk num: %d.\n",_ptrCh->num);
	// Updating crypto_fn to be the right function according to the operation flag.
	crypto_fn fn = NULL;
	if (_flag) {
		decrypt(_ptrCh->data, _crypt_key);
    } else {
		encrypt(_ptrCh->data, _crypt_key);
    }
}