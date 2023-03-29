#include<stdio.h>
#include<string.h>
#include <stdlib.h>

long getFileSize(FILE* fp) {
    fseek(fp, 0L, SEEK_END);
    long size = ftell(fp);
    fseek(fp, 0L, SEEK_SET);
    return size;
}

char* XORCipher(char* data, int len) {
	char* output = (char*)malloc(sizeof(char) * len);

	for (int i = 0; i < len; ++i) {
		output[i] = data[i] ^ 157;
	}

    //printf("%c", *output);
	return output;
}

int main (int argc, char** argv) {
    char * filepath;
    if (argc != 2){
        printf("[*]No inputfile provided...\n");
        return -1;
    }
    else
        filepath = argv[1];

    FILE * dst;
    if((dst = fopen(filepath,"r")) == NULL){
        printf("[!]ERROR: unable to open file %s for reading\n",filepath);
        return -1;
    }

    char* buf = malloc(sizeof(char) * 128);
    size_t numread;
    char* outBuf;
    do{
        numread = fread(buf,sizeof(char),128, dst);
        outBuf = XORCipher(buf, numread);
        fwrite(outBuf,sizeof(char),numread, stdout);
        free(outBuf);
    } while(numread == 128);

    fclose(dst);
    return 0;
}
