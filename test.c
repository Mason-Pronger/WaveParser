#include "wav.h"


int main(int argc, char const *argv[])
{

    FILE *fptr;
    wave header;

    fptr = fopen("Crunch_It_Girl.wav","rb");

    if(fptr == NULL){
        printf("Unable to open file\n");

    }else{
        printf("successfully opened file\n");
        if(RiffCheck(fptr,&header)){
            	printf("Identified wave file\n");
            	FileSize(fptr,&header);
		        WAVECheck(fptr,&header);
            //openwave(fptr,&header);
        }else{
            printf("Unable to identify the file\n");
        }

    }
    
    WaveInformation(&header,NULL);
    fclose(fptr);
    printf("***Program is compleate***");
    return 0;
}