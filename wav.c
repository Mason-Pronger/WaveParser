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
uint32_t ReverseEndian(uint32_t data,int size){
    //This needs to be cleaned up and tested
    uint32_t Reversed;

    Reversed =  ((data>>24)&0xff) | // move byte 3 to byte 0
                    ((data<<8)&0xff0000) | // move byte 1 to byte 2
                    ((data>>8)&0xff00) | // move byte 2 to byte 1
                    ((data<<24)&0xff000000); // byte 0 to byte 3

    return Reversed;
}

int RiffCheck(FILE *File,wave *wav){
    	int result = 0;
    
    	uint32_t buffer;
    	fread(&buffer,sizeof(uint8_t),DescriptorSize,File);

	    uint32_t ExpectedChunkId = 0x52494646;  //This is the hex representation of the asci letters "RIFF"

        buffer = ReverseEndian(buffer,sizeof(uint32_t));
    	result = buffer == ExpectedChunkId;

        memcpy(wav->ChunkID,buffer,DescriptorSize);

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

