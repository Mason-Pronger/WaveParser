//includes
#include <stdio.h>
#include <stdlib.h>

typedef struct WAV{ 
    unsigned char ChunkID[4];
    unsigned int ChunkSize;
    unsigned char Format[4];
    unsigned char Subchunk1Id[4];
    unsigned char Subchunk1Size[4];
    unsigned char AudioFormat[2];
    unsigned char NumChannels[2];
    unsigned int SampleRate;
    unsigned int ByteRate;
    unsigned int BlockAlign;
    unsigned int BitsPerSample;
    unsigned char Subchunk2Id[4];
    unsigned int Subchunk2Size;
    void *Data;
}wave;
#define ChunkOffset 4


int RiffCheck(FILE *File);   //Read the first 4 bytes of the file to check if the file being read is a wav
int FileSize(FILE *File);   // Offset the reading of the file by 4 bytes
int WAVECheck(FILE *File);
//int openwave(void *File, wave *header);
