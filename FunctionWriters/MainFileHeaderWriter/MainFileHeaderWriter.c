/*
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Filename:	MainFileHeaderWriter.h
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Purpose:	To write the main file of a program that is formatted and linked to the
 |				other files of the project.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Author:		Jonathan Burrows
 |	Date:		Nov 18 2012
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	References:	CommentingFunctions.h	all
 |	Dependancy:	stdio.h	
 |				stdlib.h
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 */
#include "MainFileHeaderWriter.h"

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
void write_main_file_comments(FILE* mainfile, list_string* files, char* filename){
	node_string* conductor;					/*Used to traverse the list of files.*/
	
	fprintf(mainfile, "/*");
	
	/*	Filename is added.	*/
	write_divider(mainfile);
	write_discriber(mainfile, "Filename", filename);
	fprintf(mainfile, ".c");
	/*	Purpose is added.	*/
	write_divider(mainfile);
	write_discriber(mainfile, "Purpose", "what_this_program_is_for");
	/*	Author and date is written.	*/
	write_divider(mainfile);
	write_discriber(mainfile, "Author", AUTHOR);
	write_date(mainfile);					/*Function enters the current date.*/
	/*	References and dependancies are added. */
	write_divider(mainfile);
	/*	Writes the reference to the header file.	*/
	write_discriber(mainfile, "References", "");
	
	if(files->head != NULL){
		conductor = files->head;
	}
	for(conductor = conductor->next; conductor!=NULL; conductor = conductor->next){
		fprintf(mainfile,"%s.h", conductor->value);
		
		if(conductor->next != NULL){
			fprintf(mainfile, "\n *\t\t\t\t");
		}
	}
	/*	Writes the dependancy discripter.	*/
	write_discriber(mainfile, "Dependancy", "<library>");
	fprintf(mainfile,"\t\t\tfunctions_that_use_lib");
	
	/*	Writing is finished with a final divider line and a closing comment bracket.	*/
	write_divider(mainfile);
	fprintf(mainfile, "\n*/");
}

/*
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Subroutine:	write_guards
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Purpose:	Writes the opening guards of the file by producing and defining a unique
 |				macro based on the filename.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	@param:		mainfile,		The file which the guards will be written to.
 |				filename,		The name of the file, will produce the headers name.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 */
extern void write_guards(FILE* mainfile, char* filename){
	char uppercase;
	int i;
	
	fprintf(mainfile, "\n#ifndef ");
	for(i=0;i<strlen(filename);i++){
		uppercase = toupper(filename[i]);
		fprintf(mainfile, "%c", uppercase);
	}
	fprintf(mainfile, "_H");
	
	fprintf(mainfile, "\n#define ");
	for(i=0;i<strlen(filename);i++){
		uppercase = toupper(filename[i]);
		fprintf(mainfile, "%c", uppercase);
	}
	fprintf(mainfile, "_H 1");
}

/*
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Subroutine:	write_main_file_header_links
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Purpose:	Write all the links of the files that the program will use.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	@param:		mainfile, 		The stream where to contents will be written to.
 |				files, 			A complete list of files for the linking.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 */
void write_main_file_header_links(FILE* mainfile, list_string* files){
	node_string* conductor;
	
	/*	Checks if the list is empty.	*/
	if(files->head != NULL){
		conductor = files->head;
	}
	for(conductor = conductor->next; conductor != NULL; conductor = conductor->next){
		fprintf(mainfile, "\n#include \"%s.h\"", conductor->value);
	}
	fprintf(mainfile, "\n");
}

/*
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Function:	write_main_file_header
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Purpose:	Creates a file for the main program and writes all the contents.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	@param:		directory,		The location of the folder where this file will be saved.
 |				files,			A list of previously made files.
 |	@return:	0,				The file was successfully writen.
 |				-1,				An error occured whilst writing the file.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 */
int write_main_file_header(char* directory, list_string* files){
	FILE* main_file_header;
	char* main_file_header_name;
	
	if( ( main_file_header_name = malloc((strlen(directory) + strlen(files->head->value)
			+strlen(".h"))*sizeof(char))) == NULL){
		/*	Allocation of memory failed, return error value.	*/
		return -1;
	}
	/*	Produces the name of the location where file will be saved.	*/									
	strcpy(main_file_header_name,directory);
	strcat(main_file_header_name, files->head->value);
	strcat(main_file_header_name,".h");
	
	/*	Writes the contents of the main header file.	*/
	main_file_header = fopen(main_file_header_name, "w");
	
	/*	Writes the opening guards.	*/
	write_main_file_comments(main_file_header,files, files->head->value);
	write_guards(main_file_header,files->head->value);
	write_main_file_header_links(main_file_header,files);
	/*	Writes the closing guards.	*/
	fprintf(main_file_header, "\n\n#endif\n");
	
	if(ferror( main_file_header) != 0){
		/*	Error has occured whilst writing file.	*/
		fclose( main_file_header);
		return -1;
	}
	fclose(main_file_header);
	
	return 0;
}