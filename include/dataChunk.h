

/*Data Chuncks Struct, each Chunk include chunk number, 1024 chars data and the next chunck*/
typedef struct _dataChunk {
	int num;
	char data[1024];
	struct _dataChunk *next;
}dataChunk;


void printChunks(dataChunk *headChunk, int size);

int getData(dataChunk *headChunk,char* path);

void freeData(dataChunk *headChunk,int size);

