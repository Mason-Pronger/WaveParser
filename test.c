#include "wav.h"


int main(int argc, char const *argv[])
{

    FILE *fptr;
    wave header;

    fptr = fopen("ITGIRL.wav","rb");

    if(fptr == NULL){
        printf("Unable to open file\n");

    }else{
        printf("successfully opened file\n");
        if(RiffCheck(fptr,&header)){
            	printf("Identified wave file\n");
            	ChunkSize(fptr,&header);
		        WAVECheck(fptr,&header);
                //openwave(fptr,&header);
                WaveInformation(&header,NULL);
        }else{
            printf("Unable to identify the file\n");
        }

    }
    

    fclose(fptr);
    printf("***Program is compleate***");
    return 0;
}