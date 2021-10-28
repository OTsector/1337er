/*
        _
 07    [|] 0ffensive 7ester

 License: GLP v2.0
 by: -07 @github.com/OTsector

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

long long getFileSize(char *file) {
	long long length;
	char *content;
	FILE *ptr;
	ptr = fopen(file,"rb");
		if (ptr) {
			fseek(ptr, 0, SEEK_END);
			length = ftell(ptr);
			fseek(ptr, 0, SEEK_SET);
			content = (char*)malloc(length + 1);
			if (content) {
				length = fread(content, 1, length, ptr);
				return length;
			}
		}
	return 0;
}
char *afterChar(char *input, char c) {
	char *tmp = (char*)malloc(sizeof(char)*strlen(input));
	char *out = (char*)malloc(sizeof(char)*strlen(input));
	int x = 0;
	for(int i=strlen(input); i>=0; i--) {
		if(input[i] == c) break;
		if(i==strlen(input)) continue;
		tmp[x] = input[i];
		x++;
	}
	x=strlen(tmp)-1;
	for (int i=0; i<strlen(tmp); ++i) {
		out[x] = tmp[i];
		--x;
	}
	return out;
}

int main(int argc, char **argv) {

	if(argc < 3) {
		puts("\nBy:             _\n\
        07     [|] 0ffensive 7ester\n\n");
		printf("use: %s [patched.exe] [original.exe]\n", argv[0]);
		return 1;
	}

	unsigned char buffer[2];
	unsigned char buffer2[2];
	long long length, length2;
	FILE *ptr;
	FILE *ptr2;
	ptr = fopen(argv[1],"rb");
	ptr2 = fopen(argv[2],"rb");
	length = getFileSize(argv[1]);
	length2 = getFileSize(argv[2]);

	if(!ptr) {
		printf("ERROR: can't read the file: \"%s\"", argv[1]);
		return 1;
	} else if(!ptr2) {
		printf("ERROR: can't read the file: \"%s\"", argv[2]);
		return 1;
	} else if(length != length2) {
		puts("ERROR: this two file is not equal sizes");
		return 1;
	}
	
	printf(">%s\n", afterChar(afterChar(argv[1], '/'), '\\'));
	for(long long i=0; i<length; i++) {
		fseek(ptr, i, SEEK_SET);
		fseek(ptr2, i, SEEK_SET);
		fread(buffer, 1, 1, ptr);
		fread(buffer2, 1, 1, ptr2);
		if(buffer[0] != buffer2[0])
			printf("%016llX:%02X>%02X\n", i, buffer[0], buffer2[0]);
		fseek(ptr, i, SEEK_END);
		fseek(ptr2, i, SEEK_END);
	}
	return 0;
}
