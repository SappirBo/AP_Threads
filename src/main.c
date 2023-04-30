#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
	
	//Setting up the threadpool
	tpool_t *tm;
	tm = tpool_create(num_of_chunks);

	// adding chunks to different threads.
	while(i<=num_of_chunks)
	{
		//setting args variable for the thread. 
		thread_args_t th_args;
		th_args.arg_ptrCh = _ptrCh;
		th_args.arg_flag = operate_flag;
		th_args.arg_crypt_key = key;

		// add thread
        tpool_add_work(tm, _operateAction, &th_args);

		_ptrCh = _ptrCh->next;
		i++;
	}
	

	tpool_wait(tm);


	writeDataToFile(_headCh,num_of_chunks,dest_file);

	tpool_destroy(tm);
	
	return 0;
}


void _operateAction(void* args)
{
	thread_args_t* _arg = (thread_args_t*) args;
    dataChunk* _ptrCh = _arg->arg_ptrCh;
    bool _flag = _arg->arg_flag;
    int _crypt_key = _arg->arg_crypt_key;

	// Updating crypto_fn to be the right function according to the operation flag.
	crypto_fn fn = NULL;
	if (_flag) {
		fn = decrypt;
    } else {
		fn = encrypt;
    }

	fn(_ptrCh->data, _crypt_key);
}