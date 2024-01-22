//includes
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct WAV{ 
    uint32_t ChunkID;    //The wave format spec says that chunkid is 4 bytes. However I need a null terminator char to print this value correctly
    uint32_t ChunkSize;
    uint32_t Format;     //Much like the ChunkId explanation, I need a null terminator character.
    uint32_t Subchunk1Id;
    uint32_t Subchunk1Size;
    uint16_t AudioFormat;
    uint16_t NumChannels;
    uint32_t SampleRate;
    uint32_t ByteRate;
    uint16_t BlockAlign;
    uint16_t BitsPerSample;
    uint32_t Subchunk2Id;
    uint32_t Subchunk2Size;
    uint8_t *Data;
}wave;
#define ChunkOffset 4
#define DescriptorSize 4

int RiffCheck(FILE *File,wave *wav);   //Read the first 4 bytes of the file to check if the file being read is a wav
int ChunkSize(FILE *File,wave *wav);   // Offset the reading of the file by 4 bytes
int WAVECheck(FILE *File,wave *wav);




void WaveInformation(wave *wav, FILE *out);    //  Print out the information in the header into the file out
//int openwave(void *File, wave *header);
