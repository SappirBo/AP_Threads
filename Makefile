CC = gcc
LIBS = -L./build -I./build/  -l Codec



.PHONY: all

all: task stdinExample mainCoder
	export LD_LIBRARY_PATH=./build:$LD_LIBRARY_PATH

task:	include/codec.h src/basic_main.c
	$(CC) src/basic_main.c $(LIBS) -o encoder
	

stdinExample:	src/stdin_main.c
	$(CC) src/stdin_main.c $(LIBS) -o tester

mainCoder: src/main.c
	$(CC) src/main.c $(LIBS) -o coder
	

.PHONY: clean
clean:
	-rm encoder tester coder
# -rm libCodec.so 2>/dev/null