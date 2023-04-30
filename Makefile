CC = gcc
# LIBS = -L./build -I./build/  -l Codec
LIBS = ./build/libCodec.so include/codec.h include/threadpool.h src/threadpool.c
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

.PHONY: clean
clean:
	-rm encoder tester coder
# -rm libCodec.so 2>/dev/null