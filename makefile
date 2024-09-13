CC = gcc
CFLAGS = -Wall -g -lm

Default: test

all: test sine

# Program files
test: test.o wav.o
	$(CC) -o test test.o wav.o $(CFLAGS)

sine: sine.o wav.o
	$(CC) -o sine sine.o wav.o $(CFLAGS)

# Object files
test.o: test.c wav.h
	$(CC) -c test.c $(CFLAGS)

wav.o: wav.c wav.h
	$(CC) -c wav.c $(CFLAGS)

sine.o: sine.c wav.h
	$(CC) -c sine.c $(CFLAGS)

clean:
	rm -f test sine *.o
