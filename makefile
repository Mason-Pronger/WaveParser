CC = gcc
CFLAGS = -Wall


#	Program files
test: test.o wav.o
#	Object files
test.o: test.c wav.h

wave.o: wav.c wav.h

clean:
	rm *.exe *.o
