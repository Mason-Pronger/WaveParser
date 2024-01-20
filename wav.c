#include "wav.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/*  This function does not work yet do not use.
int PrintProper(char *incoming,char **destination,uint8_t size){
    uint8_t result = 0;
    char buffer[size];

    strncpy(buffer,incoming,DescriptorSize);
    buffer[size] = '\0';
    *destination = buffer;

    result = destination != NULL;

    return result;
}
*/

//Reverse the order of the endian
uint32_t ReverseEndian(unsigned char *data,int size){
    //This needs to be cleaned up and tested
    uint32_t Reversed;
    printf("%x\n",data[0]);
    printf("%x\n",data[1]<<8);
    printf("%x\n",data[2]<<16);
    printf("%x\n",data[3]<<24);

    Reversed = ((data[0])) | // move byte 3 to byte 0
                    ((data[1]<<8)) | // move byte 1 to byte 2
                    ((data[2]<<16)) | // move byte 2 to byte 1
                    ((data[3]<<24)); // byte 0 to byte 3

    printf("%u\n",Reversed);
    //Incorrect output for 0x0027A612
    return Reversed;
}

int RiffCheck(FILE *File,wave *wav){
    	int result = 0;
    
    	char buffer[4];
    	fread(buffer,sizeof(char),DescriptorSize,File);
	    char *ChunkId = "RIFF";

    	result = !strncmp(buffer,ChunkId,DescriptorSize);

        memcpy(wav->ChunkID,buffer,sizeof(char)*DescriptorSize);

    	return result;
}

int ChunkSize(FILE *File, wave *wav){
	//ChunkSize is in little endian format
    uint8_t result = 0; //Assume the final result is false
	char buffer[4];
	result = fread(buffer,sizeof(char),4,File);

    memcpy(wav->ChunkSize,buffer,sizeof(char)*DescriptorSize);
    
    return (result != 0);
}

int WAVECheck(FILE *File, wave *wav){
	uint8_t result;
	char buffer[4];
	fread(buffer,sizeof(char),DescriptorSize,File);
	char *WAVEId = "WAVE";
	result = !strncmp(buffer,WAVEId,DescriptorSize);

    memcpy(wav->Format,buffer,DescriptorSize*sizeof(char));

	return result;
}

void WaveInformation(wave *wav, FILE *out){
    //char *ChunkId=NULL,*Format=NULL;
    uint32_t ChunkSize;
    //PrintProper(wav->ChunkID,&ChunkId,DescriptorSize);
    //PrintProper(wav->Format,&Format,DescriptorSize);
    ChunkSize = ReverseEndian(wav->ChunkSize,DescriptorSize);

    if(out == NULL){
        //fprintf(stdout,"Chunk Id:%-8s\nChunk Size:%-8d\nFormat:%-8s\n",ChunkId,ChunkSize,Format);
        printf("%u\n",ChunkSize);
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

