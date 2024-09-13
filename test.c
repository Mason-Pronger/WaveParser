#include "wav.h"


int main(int argc, char const *argv[])
{

    FILE *fptr;
    wave header;

    if(argc > 1){
        fptr = fopen(argv[2],"rb");

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
    }else{
        printf("Please input a wave file as an argument\n");
    }
    
    printf("***Program is compleate***\n");
    return 0;
}