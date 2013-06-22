#ProgramCreater.mak
CC = gcc
WARNINGS = -Wall

#Locations of the following files:
INPUTS = ../inputs/inputs
LINKEDLISTSTRING = ../LinkedListString/LinkedListString
PROGRAMCREATER = ../ProgramCreater/ProgramCreater
EXE = ../../
#Location of the Writing Functions:
FUNCTIONWRITERS = ../FunctionWriters
COMMENTINGFUNCTIONS = $(FUNCTIONWRITERS)/CommentingFunctions/CommentingFunctions
CFILEWRITER = $(FUNCTIONWRITERS)/CFileWriter/CFileWriter
HEADERFILEWRITER = $(FUNCTIONWRITERS)/HeaderFileWriter/HeaderFileWriter
MAKEFILEWRITER = $(FUNCTIONWRITERS)/MakeFileWriter/MakeFileWriter
MAINFILEHEADERWRITER = $(FUNCTIONWRITERS)/MainFileHeaderWriter/MainFileHeaderWriter

all: ProgramCreater.exe

ProgramCreater.exe:	CFileWriter.o inputs.o LinkedListString.o CommentingFunctions.o \
	 ProgramCreater.o HeaderFileWriter.o MakeFileWriter.o MainFileHeaderWriter.o
	$(CC) $(WARNINGS) inputs.o LinkedListString.o ProgramCreater.o  CommentingFunctions.o \
	CFileWriter.o HeaderFileWriter.o MakeFileWriter.o MainFileHeaderWriter.o \
	-o $(EXE)ProgramCreater.exe
	
MainFileHeaderWriter.o: $(MAINFILEHEADERWRITER).c $(MAINFILEHEADERWRITER).h
	$(CC) -c $(MAINFILEHEADERWRITER).c
	
MakeFileWriter.o: $(MAKEFILEWRITER).c $(MAKEFILEWRITER).h
	$(CC) -c $(MAKEFILEWRITER).c
	
HeaderFileWriter.o: $(HEADERFILEWRITER).c $(HEADERFILEWRITER).h
	$(CC) -c $(HEADERFILEWRITER).c
	
CommentingFunctions.o: $(COMMENTINGFUNCTIONS).c $(COMMENTINGFUNCTIONS).h
	$(CC) -c $(COMMENTINGFUNCTIONS).c
	
CFileWriter.o: $(CFILEWRITER).c $(CFILEWRITER).h
	$(CC) -c $(CFILEWRITER).c
	
inputs.o: $(INPUTS).c $(INPUTS).h
	$(CC) -c $(INPUTS).c
	
LinkedListString.o: $(LINKEDLISTSTRING).c $(LINKEDLISTSTRING).h
	$(CC) -c $(LINKEDLISTSTRING).c
	
ProgramCreater.o: $(PROGRAMCREATER).c $(PROGRAMCREATER).h
	$(CC) -c $(PROGRAMCREATER).c

clean:
	rm -rf *.o core
