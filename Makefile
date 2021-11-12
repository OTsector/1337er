CC = gcc
DIR = ./bin

all: MKDIR_P 1337er 1337patcher


MKDIR_P:
	 mkdir -p $(DIR)

1337er:
	$(CC) 1337er.c -o ./bin/1337er
1337patcher:
	$(CC) 1337patcher.c -o ./bin/1337patcher
install:
	cp ./bin/* /usr/bin
clean:
	rm -rf ./bin
