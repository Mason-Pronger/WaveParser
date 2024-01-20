//includes
#include <stdio.h>
#include <stdlib.h>

typedef struct WAV{ 
    char ChunkID[5];    //The wave format spec says that chunkid is 4 bytes. However I need a null terminator char to print this value correctly
    int ChunkSize;
    char Format[5];     //Much like the ChunkId explanation, I need a null terminator character.
    char Subchunk1Id[4];
    char Subchunk1Size[4];
    char AudioFormat[2];
    char NumChannels[2];
    int SampleRate;
    int ByteRate;
    int BlockAlign;
    int BitsPerSample;
    char Subchunk2Id[4];
    int Subchunk2Size;
    void *Data;
}wave;
#define ChunkOffset 4


int RiffCheck(FILE *File,wave *wav);   //Read the first 4 bytes of the file to check if the file being read is a wav
int FileSize(FILE *File,wave *wav);   // Offset the reading of the file by 4 bytes
int WAVECheck(FILE *File,wave *wav);
void WaveInformation(wave *wav, FILE *out);    //  Print out the information in the header into the file out
//int openwave(void *File, wave *header);
