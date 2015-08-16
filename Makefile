songs.out: main.o song.o
	g++ -Wall -ansi -o songs.out main.o song.o

song.o: song.cpp song.h 
	g++ -Wall -g -ansi -c song.cpp

clean:
	rm -f songs.out song.o main.o 
