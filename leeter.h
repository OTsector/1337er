#ifndef LEETER_H
#define LEETER_H
#endif

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

long long hex2dec(char *input) {
	return (long long)strtoul(input, NULL, 16);
}

unsigned char hex2char(char *input) {
	return (unsigned char)strtoul(input, NULL, 16);
}

char *beforeChar(char *input, char breaker) {
	char *out=(char*)malloc(sizeof(char)*strlen(input));
	for(int i=0; input[i] != '\0'; i++) {
		if(input[i] == breaker)
			break;
		out[i] = input[i];
	}
	return out;
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
