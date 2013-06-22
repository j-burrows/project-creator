#FirstFile.mak
CC = gcc
WARNINGS = -Wall

all: FirstFile.exe

FirstFile.exe: FirstFile.o SecondFile.o ThirdFile.o 
	$(CC) $(WARNINGS) FirstFile.o SecondFile.o ThirdFile.o -o FirstFile.exe

FirstFile.o: FirstFile.c FirstFile.h
	$(CC) -c FirstFile.c

SecondFile.o: SecondFile.c SecondFile.h
	$(CC) -c SecondFile.c

ThirdFile.o: ThirdFile.c ThirdFile.h
	$(CC) -c ThirdFile.c

clean:
	rm -rf *o
