/*
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Filename:	MainFileHeaderWriter.c
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Purpose:	To write the main file of a program that is formatted and linked to the
 |				other files of the project.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Author:		Jonathan Burrows
 |	Date:		Nov 18 2012
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 */
#ifndef MAINFILEHEADERWRITER_H
#define MAINFILEHEADERWRITER_H 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../LinkedListString/LinkedListString.h"
#include "../CommentingFunctions/CommentingFunctions.h"

/*
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Subroutine:	write_main_file_comments
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Purpose:	Write the commenting header for the main file of the program.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	@param:		mainfile, 		The stream name that the contents will be written to.
 |				list_string_files,	The list of files used in this program.
 |				filename, 		The name of the file without extensions or directory.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 */
extern void write_main_file_comments(FILE* mainfile, list_string* files, char* filename);

/*
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Subroutine:	write_guards
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Purpose:	Writes the opening guards of the file.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	@param:		mainfile,		The file which the guards will be written to.
 |				filename,		The name of the file, will produce the headers name.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 */
extern void write_guards(FILE* mainfile, char* filename);

/*
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Subroutine:	write_main_file_links
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Purpose:	Write all the links of the files that the program will use.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	@param:		mainfile, 		The stream where to contents will be written to.
 |				files, 			A complete list of files for the linking.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 */
extern void write_main_file_links(FILE* mainfile, list_string* files);

/*
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Function:	write_main_file_comments
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Purpose:	Creates a file for the main program and writes all the contents.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	@param:		directory,		The location of the folder where this file will be saved.
 |				files,			A list of previously made files.
 |	@return:	0,				The file was successfully writen.
 |				-1,				An error occured whilst writing the file.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 */
extern int write_main_file(char* directory, list_string* files);

#endif
