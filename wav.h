//includes
#include <stdio.h>
#include <stdlib.h>

typedef struct WAV{ 
    char ChunkID[4];    //The wave format spec says that chunkid is 4 bytes. However I need a null terminator char to print this value correctly
    char ChunkSize[4];
    char Format[4];     //Much like the ChunkId explanation, I need a null terminator character.
    char Subchunk1Id[4];
    char Subchunk1Size[4];
    char AudioFormat[2];
    char NumChannels[2];
    char SampleRate[4];
    char ByteRate[4];
    char BlockAlign[2];
    char BitsPerSample[4];
    char Subchunk2Id[4];
    char Subchunk2Size[4];
    void *Data;
}wave;
#define ChunkOffset 4
#define DescriptorSize 4

int RiffCheck(FILE *File,wave *wav);   //Read the first 4 bytes of the file to check if the file being read is a wav
int ChunkSize(FILE *File,wave *wav);   // Offset the reading of the file by 4 bytes
int WAVECheck(FILE *File,wave *wav);




void WaveInformation(wave *wav, FILE *out);    //  Print out the information in the header into the file out
//int openwave(void *File, wave *header);
