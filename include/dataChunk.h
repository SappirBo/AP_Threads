/*
This Header handles the chuncks of data in the system.
*/


/*Data Chuncks Struct, each Chunk include chunk number, 1024 chars data and the next chunck*/
typedef struct _dataChunk {
	int num;
	char data[1024];
	struct _dataChunk *next;
}dataChunk;

/*Helper for Debug, Prints all the data inside each Chunk, seperated by '-' */
void printChunks(dataChunk *headChunk, int size);

/*Helper for Debug, Prints all the formal data of each chunk*/
void print_Chunck_Data(dataChunk *headChunk,int size);

/*
Given a dataChunk linklist header, this function will take all the data from stdin to chunks linked list.
Param:
	dataChunk *headChunk - head of the data chunks, where the input from stdin will enter.
*/
int getData_stdIn(dataChunk *headChunk);

/*
Given a dataChunk linklist header and a path to a file, this function will take all the data from the file to chunks linked list.
Param:
	dataChunk *headChunk - head of the data chunks, where the input from stdin will enter.
	char* path - where to take the data from.
*/int getData_fromFile(dataChunk *headChunk,char* path);


/*Free all the linked list.*/
void freeData(dataChunk *headChunk,int size);

/*
Given a dataChunk linklist header and a path to a file, this function will take all the data from the chunks linked list and write it 
to the file specified in the path.
Param:
	dataChunk *headChunk - head of the data chunks.
	char* path - where to write the data in.
return:
	1 - on sucsses
	0 - on fail.
*/
int writeDataToFile(dataChunk *_headChunk, int _chunk_amount, char* _filePath);
