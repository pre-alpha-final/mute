CC=g++

mute : main.o
	$(CC) -o mute.exe main.o -s -mwindows
	
main.o : main.cpp
	$(CC) -Wall -O2 -c main.cpp

.PHONY : clean	
clean :
	-rm main.o
	-rm mute.exe