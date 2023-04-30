CC = gcc
# LIBS = -L./build -I./build/  -l Codec
LIBS = ./build/libCodec.so include/codec.h include/threadpool.h src/threadpool.c include/dataChunk.h src/dataChunck.c
EXPORT=export LD_LIBRARY_PATH=./build:$LD_LIBRARY_PATH



all: task stdinExample mainCoder
	$(EXPORT)

task:	include/codec.h src/basic_main.c
	$(CC) src/basic_main.c $(LIBS) -o encoder
	

stdinExample:	src/stdin_main.c
	$(CC) src/stdin_main.c $(LIBS) -o tester

mainCoder: src/main.c
	$(CC) src/main.c $(LIBS) -o coder

threadpool.o: include/threadpool.h src/threadpool.c
	$(CC) -c src/threadpool.c

chunksTest:
	gcc -o chunks test/testDataChuncks.c include/dataChunk.h src/dataChunck.c 

.PHONY: clean
clean:
# remove encoder, but only if it exists
	if [ -e encoder ]; then rm encoder; fi
	if [ -e tester ]; then rm tester; fi
	if [ -e coder ]; then rm coder; fi
	if [ -e chunks ]; then rm chunks; fi
# -rm libCodec.so 2>/dev/null