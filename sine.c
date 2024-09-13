//
// Created by mason on 9/12/24.
//
#include "wav.h"

int main(int argc, char *argv[]){


    FILE *File;
    wave *wav;

    File = fopen("sine.wav","wb");

    //Create a sine wave that has a duration of 5 seconds and a frequency of 440Hz
    createSineWave( File, wav, 440, 5, 44100, 16, MONO);



}