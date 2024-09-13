//includes
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <arpa/inet.h>


typedef enum CHANNELS {
    MONO = 1,
    STEREO = 2
} WaveChannels;

typedef struct WAV{ //This struct will be used to hold the header information of the wave file
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
int Subchunk1(FILE *File,wave *wav);
int Subchunk2(FILE *File,wave *wav);
void Data(FILE *File,wave *wav);

/**
 *
 * @param File pointer to the file that the wave will be written to
 * @param wav struct that holds the information of the wave file
 * @param frequency frequency of the sine wave
 * @param duration Time in seconds that the wave will last
 * @param sampleRate resolution of the wave
 * @param bitsPerSample Size of the sample in bits
 * @param numChannels number of channels in the wave
 * @return
 * @brief This function will create a sine wave and write it to a file
 */
int createSineWave(FILE *File, wave *wav, uint32_t frequency, uint32_t duration, uint32_t sampleRate, uint16_t bitsPerSample, uint16_t numChannels);


/**
 *
 * @param wav
 * @param out
 */
void WaveInformation(wave *wav, FILE *out);    //  Print out the information in the header into the file out
//int openwave(void *File, wave *header);

