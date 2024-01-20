#include "wav.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int RiffCheck(FILE *File,wave *wav){
    	int result = 0;
    
    	char buffer[4];
    	fread(buffer,sizeof(char),4,File);
	    char *ChunkId = "RIFF";

    	result = strcmp(buffer,ChunkId);

        memcpy(wav->ChunkID,buffer,sizeof(char)*4);
        wav->ChunkID[5] = '\0';

    	return !result;
}

int FileSize(FILE *File, wave *wav){
	//Offset for the chunk size
    uint8_t result = 0; //Assume the final result is false

	char buffer[4];
	fread(buffer,sizeof(char),4,File);

    uint32_t b0,b1,b2,b3;
    uint32_t res;

    b0 = (buffer[0] & 0x000000ff) << 24u;
    b1 = (buffer[1] & 0x0000ff00) << 8u;
    b2 = (buffer[2] & 0x00ff0000) >> 8u;
    b3 = (buffer[3] & 0xff000000) >> 24u;

    res = b0 | b1 | b2 | b3;

    wav->ChunkSize = res;

    return (result != 0);
}
int WAVECheck(FILE *File, wave *wav){
	uint8_t result;
	char buffer[4];
	fread(buffer,sizeof(char),4,File);
	char *WAVEId = "WAVE";
	result = strcmp(buffer,WAVEId);

    memcpy(wav->Format,buffer,4*sizeof(char));
    wav->Format[5] = '\0';

	return !result;
}

void WaveInformation(wave *wav, FILE *out){
    if(out == NULL){
        fprintf(stdout,"Chunk Id:%-8s\nChunk Size:%-8d\nFormat:%-8s\n",wav->ChunkID,wav->ChunkSize,wav->Format);
    }
}
/*
int openwave(void *File, wave *header){
    int read = 0;
    
    read = fread(header->ChunkID, sizeof(header->ChunkID),1,File);
    printf("(1-4): %s n", header->ChunkID);
    
    return 0;
}
*/

