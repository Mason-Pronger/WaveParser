#include "wav.h"
#include <math.h>
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
uint32_t ReverseEndian(uint32_t data){
    return ntohl(data);
}

int RiffCheck(FILE *File,wave *wav){
    	int result = 0;
    
    	uint32_t buffer;
    	fread(&buffer,sizeof(uint8_t),DescriptorSize,File);

	    uint32_t ExpectedChunkId = 0x52494646;  //This is the hex representation of the asci letters "RIFF"

        buffer = ReverseEndian(buffer);
    	result = buffer == ExpectedChunkId;

        memcpy(&wav->ChunkID,&buffer,DescriptorSize);

    	return result;
}

int ChunkSize(FILE *File, wave *wav){
	//ChunkSize is in little endian format
    uint8_t result = 1; //Assume the final result is failed
	uint32_t buffer;


	result = fread(&buffer,sizeof(uint32_t),1,File);

    memcpy(&wav->ChunkSize,&buffer,sizeof(wav->ChunkSize));
    
    return result;
}

int WAVECheck(FILE *File, wave *wav){
	uint8_t result;
	uint32_t buffer;
	
    fread(&buffer,sizeof(uint32_t),1,File);
	uint32_t ExpectedWAVEId = "WAVE";
    
    buffer = ReverseEndian(buffer);
	result = buffer == ExpectedWAVEId;

    memcpy(&wav->Format,&buffer,sizeof(uint32_t));

	return result;
}

void WaveInformation(wave *wav, FILE *out){
    char ChunkId[5],Format[5];
    uint32_t ChunkSize = wav->ChunkSize;

    snprintf(ChunkId, sizeof(ChunkId), "%c%c%c%c", 
             (wav->ChunkID >> 24) & 0xFF,
             (wav->ChunkID >> 16) & 0xFF,
             (wav->ChunkID >> 8) & 0xFF,
             wav->ChunkID & 0xFF);

    snprintf(Format, sizeof(Format), "%c%c%c%c", 
             (wav->Format >> 24) & 0xFF,
             (wav->Format >> 16) & 0xFF,
             (wav->Format >> 8) & 0xFF,
             wav->Format & 0xFF);

    if(out == NULL){
        fprintf(stdout,"Chunk Id:%-8s\nChunk Size:%-8d\nFormat:%-8s\n",ChunkId,ChunkSize,Format);
        //printf("%u\n",ChunkSize);
    }
}

int openwave(FILE *File, wave *header){
	int read = 0;

	// Read the RIFF chunk descriptor
	read = fread(&header->ChunkID, sizeof(header->ChunkID), 1, File);
	if (read != 1) {
		printf("Error reading ChunkID\n");
		return -1;
	}

	read = fread(&header->ChunkSize, sizeof(header->ChunkSize), 1, File);
	if (read != 1) {
		printf("Error reading ChunkSize\n");
		return -1;
	}

	read = fread(&header->Format, sizeof(header->Format), 1, File);
	if (read != 1) {
		printf("Error reading Format\n");
		return -1;
	}

	// Print the information
	WaveInformation(header, stdout);

	return 0;
}



int createSineWave(FILE *File, wave *wav, uint32_t frequency, uint32_t duration, uint32_t sampleRate, uint16_t bitsPerSample, uint16_t numChannels) {
	uint32_t numSamples = sampleRate * duration;
	uint32_t dataSize = numSamples * numChannels * (bitsPerSample / 8);

	// Allocate memory for the data
	wav->Data = (uint8_t *)malloc(dataSize);
	if (wav->Data == NULL) {
		printf("Memory allocation failed\n");
		return -1;
	}

	// Generate the sine wave
	for (uint32_t i = 0; i < numSamples; i++) {
		double t = (double)i / sampleRate;
		double sample = sin(2.0 * M_PI * frequency * t);

		// Scale the sample to the appropriate range
		int16_t intSample = (int16_t)(sample * 32767);

		// Write the sample to the data buffer
		for (uint16_t channel = 0; channel < numChannels; channel++) {
			memcpy(&wav->Data[(i * numChannels + channel) * (bitsPerSample / 8)], &intSample, sizeof(int16_t));
		}
	}

	// Write the WAV header
	fwrite("RIFF", 1, 4, File);
	uint32_t chunkSize = 36 + dataSize;
	fwrite(&chunkSize, 4, 1, File);
	fwrite("WAVE", 1, 4, File);
	fwrite("fmt ", 1, 4, File);
	uint32_t subchunk1Size = 16;
	fwrite(&subchunk1Size, 4, 1, File);
	uint16_t audioFormat = 1;
	fwrite(&audioFormat, 2, 1, File);
	fwrite(&numChannels, 2, 1, File);
	fwrite(&sampleRate, 4, 1, File);
	uint32_t byteRate = sampleRate * numChannels * (bitsPerSample / 8);
	fwrite(&byteRate, 4, 1, File);
	uint16_t blockAlign = numChannels * (bitsPerSample / 8);
	fwrite(&blockAlign, 2, 1, File);
	fwrite(&bitsPerSample, 2, 1, File);
	fwrite("data", 1, 4, File);
	fwrite(&dataSize, 4, 1, File);
	fwrite(wav->Data, 1, dataSize, File);

	// Free the allocated memory
	free(wav->Data);

	return 0;
}