CC = gcc
LIBS = -L./build -I./build/  -l Codec



.PHONY: all
all: task stdinExample

task:	include/codec.h src/basic_main.c
	$(CC) src/basic_main.c $(LIBS) -o encoder
	export LD_LIBRARY_PATH=./build:$LD_LIBRARY_PATH

stdinExample:	src/stdin_main.c
	$(CC) src/stdin_main.c $(LIBS) -o tester
	export LD_LIBRARY_PATH=./build:$LD_LIBRARY_PATH

.PHONY: clean
clean:
	-rm encoder tester
# -rm libCodec.so 2>/dev/null