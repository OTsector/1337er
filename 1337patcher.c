/*
        _
 07    [|] 0ffensive 7ester

 License: GLP v2.0
 by: -07 @github.com/OTsector

*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "leeter.h"

int main(int argc, char **argv) {

	if(argc < 3) {
		puts("\nBy:             _\n\
        07     [|] 0ffensive 7ester\n\n");
		printf("use: %s [patched.1337] [original.exe]\n", argv[0]);
		return 1;
	}

	unsigned char buffer[2];
	long long length;
	FILE *fptr;
	FILE *ptr;
	char ch;
	char string[24];
	int i=0, l=0, x=0;
	char need[] = ":>";
	long long line;
	unsigned char newChar, oldChar;

	fptr = fopen(argv[1], "r");
	ptr = fopen(argv[2],"rb+");
	length = getFileSize(argv[2]);

	if(fptr == NULL) {
		printf("ERROR: can't read the file: \"%s\"\n", argv[1]);
		return 1;
	} else if (!ptr) {
		printf("ERROR: can't read the file: \"%s\"\n", argv[2]);
		return 1;
	}
	ch = fgetc(fptr);
	while (ch != EOF && ch != 0xFF) {
		ch = fgetc(fptr);
		if(l > 0 && ch != '\n') {
			if(l>1) {
				string[i] = ch;
				i++;
			}
		} else {
			l++;
			if(l>2) {
				for(int a=0; a<strlen(string); a++) {
					for(int b=0; b<strlen(need); b++) {
						if(need[b] == string[a]) {
							x++;
						}
					}
				}
				line=hex2dec(beforeChar(string, ':'));
				oldChar=hex2char(beforeChar(afterChar(string, ':'), '-'));
				newChar=hex2char(afterChar(string, '>'));
				fseek(ptr, line, SEEK_SET);
				fread(buffer, 1, 1, ptr);
				fseek(ptr, line, SEEK_END);
				fseek(ptr, line, SEEK_SET);
				if(x!=2) {
					printf("ERROR: .1337 syntax is not correct line %d\n", 
						(l-1));
					return 1;
				} else if(line>length) {
					printf("ERROR: offset \"%s\" is bigger then file size\n", 
						beforeChar(string, ':'));
					return 1;
				} else if(buffer[0] != oldChar) {
					printf("ERROR: original binary \"%02X\" hex is not equal for current \"%02X\" hex value\n", 
						buffer[0], oldChar);
					return 1;
				}
				if(fwrite(&newChar, 1, 1, ptr))
					printf("INFO: %s - done!\n", string);
				fseek(ptr, line, SEEK_END);
				x=0;
				i=0;
			}
		}
	}
	fclose(fptr);
	fclose(ptr);
	return 0;
}
