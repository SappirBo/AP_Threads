#include "../include/codec.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

# define MAX_SIZE 1024

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
    char source_file[MAX_SIZE];
    char dest_file[MAX_SIZE];
    strcpy(flag, argv[2]);
    strcpy(source_file,argv[3]);
    strcpy(dest_file,argv[4]);
	
    
    printf("key is %i,",key);
    if(!strcmp(flag,"-d"))
    {
        printf("Flag = decrypt\n");    
    }
    else if(!strcmp(flag,"-e"))
    {
        printf("Flag = encrypt\n");   
    }
    else
    {
        printf("Flag is UNKNOWN.\n");
        return 0;
    }

    printf("Source: %s, Dest: %s\n",source_file,dest_file);

	char c;
	int counter = 0;
	int dest_size = MAX_SIZE;
	char data[dest_size]; 
	

	while ((c = getchar()) != EOF)
	{
	  data[counter] = c;
	  counter++;

	  if (counter == 1024){
		encrypt(data,key);
		printf("encripted data: %s\n",data);
		counter = 0;
	  }
	}
	
	if (counter > 0)
	{
		char lastData[counter];
		lastData[0] = '\0';
		strncat(lastData, data, counter);
		encrypt(lastData,key);
		printf("encripted data:\n %s\n",lastData);
	}

	return 0;
}
