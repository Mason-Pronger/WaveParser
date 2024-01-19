#include "wav.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int RiffCheck(FILE *File){
    	int result = 0;
    
    	char buffer[4];
    	fread(buffer,sizeof(char),4,File);
	    char *ChunkId = "RIFF";

    	result = !strcmp(buffer,ChunkId);

    	return result;
}

int FileSize(FILE *File){
	//Offset for the chunk size

	char buffer[4];
	fread(buffer,sizeof(char),4,File);

    uint32_t b0,b1,b2,b3;
    uint32_t res;

    b0 = (buffer[0] & 0x000000ff) << 24u;
    b1 = (buffer[1] & 0x0000ff00) << 8u;
    b2 = (buffer[2] & 0x00ff0000) >> 8u;
    b3 = (buffer[3] & 0xff000000) >> 24u;

    res = b0 | b1 | b2 | b3;

    printf("%d\n", res);

}
int WAVECheck(FILE *File){
	uint8_t result;
	char buffer[4];
	fread(buffer,sizeof(char),4,File);
	char *WAVEId = "WAVE";
	result = !strcmp(buffer,WAVEId);

	return result;
}
/*
int openwave(void *File, wave *header){
    int read = 0;
    
    read = fread(header->ChunkID, sizeof(header->ChunkID),1,File);
    printf("(1-4): %s n", header->ChunkID);
    
    return 0;
}


*/
int main(int argc, char const *argv[])
{

    FILE *fptr;
    wave header;

    fptr = fopen("Crunch_It_Girl.wav","rb");

    if(fptr == NULL){
        printf("Unable to open file\n");

    }else{
        printf("successfully opened file\n");
        if(RiffCheck(fptr)){
            	printf("Identified wave file\n");
            	FileSize(fptr);
		WAVECheck(fptr);	
            //openwave(fptr,&header);
        }else{
            printf("Unable to identify the file");
        }

    }
    
    fclose(fptr);
    printf("***Program is compleate***");
    return 0;
}
