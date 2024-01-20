Wave: main.c wav.h
	echo "Hello world"
	gcc -Wall main.c wav.h -o wave

clean:
	rm *.gch *.exe
