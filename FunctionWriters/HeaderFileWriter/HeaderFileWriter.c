/*
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Filename:	HeaderFileWriter.c
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Purpose:	A program that can set up a formatted header file for a c source file.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Author:		Jonathan Burrows
 |	Date:		November 17th 2012
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Dependancy:	stdlib.h				All		
 |				stdio.h					All
 |				string.h
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 */
#include "HeaderFileWriter.h"

/*
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Subroutine:	write_h_head
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Purpose:	Writes the comment section for the header file. Writes a generic purpose of
 |				a header file, the default author name, the current date, and the guards.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	@param:		h_file,				The file that information will be written to.
 |				h_file_name,		The name of the file.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 */
void write_h_head(FILE* h_file, char* file_name){
	int i;									/*Loop control.*/
	
	fprintf(h_file, "/*");
	/*	Filename is added.	*/
	write_divider(h_file);
	write_discriber(h_file, "Filename", file_name);
	fprintf(h_file,".h");
	
	/*	Purpose is added.	*/
	write_divider(h_file);
	write_discriber(h_file, "Purpose", "what_this_program_is_for");
	
	/*	Author and date is written.	*/
	write_divider(h_file);
	write_discriber(h_file, "Author", AUTHOR);
	write_date(h_file);									/*Function enters current date.*/
	
	/*	References and dependancies are added. */
	write_divider(h_file);
	write_discriber(h_file, "References", "");
	/*	Writes the dependancy discripter.	*/
	write_discriber(h_file, "Dependancy", "<library>");
	fprintf(h_file,"\t\t\tfunctions_that_use_todo_lib");
	
	/*	Writing is finished with a final divider line and a closing comment bracket.	*/
	write_divider(h_file);
	fprintf(h_file, "\n*/");
	
	/*	Writes the guard by printing out the upper case form followed by a '_H'.	*/
	fprintf(h_file, "\n#ifndef ");
	for(i=0; i < strlen(file_name); i++){
		fprintf(h_file, "%c", toupper(file_name[i]));
	}
	fprintf(h_file, "_H");
	/*	Writes the second part of the guard.	*/
	fprintf(h_file, "\n#define ");
	for(i=0; i < strlen(file_name); i++){
		fprintf(h_file, "%c", toupper(file_name[i]));
	}
	fprintf(h_file, "_H 1");
}

/*
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Subroutine:	write_function_head
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Purpose:	Writes the comment section for a function. Declares the type, and 
 |				a section including a generic purpose.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	@param:		h_file,				The file that information will be written to.
 |				type,				The return type of the function.
 |				function_name,		The name the function will be.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 */
void write_function_head_h(FILE* h_file, char* type, char* function_name){
	/*	Writes out the header for the function, starting with an opening commenting brace 
	 *	and divider.	*/
	fprintf(h_file, "\n\n/*");	
	write_divider(h_file);
	
	/*	Checks to see if the method is a subroutine or a function, and writes the type.	*/
	(strcmp(type,"void")==0)?
		write_discriber(h_file,"Subroutine",function_name):
		write_discriber(h_file,"Function",function_name);
	write_divider(h_file);
	
	/*	Writes the purpose discriber.	*/
	write_discriber(h_file,"Purpose","what_does_this_function_do");
	write_divider(h_file);
	
	/*	Closes the commenting brace.	*/
	fprintf(h_file, "\n */");
}

/*
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Subroutine:	write_function_head
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Purpose:	Writes the content section for a function. Declares it as external, the 
 |				functions type, and a unique name.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	@param:		h_file,				The file that information will be written to.
 |				type,				The return type of the function.
 |				function_name,		The name the function being written will be.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 */
void write_function_contents_h(FILE* h_file, char* type, char* function_name){
	/*	Adds padding between itself and comment section.	*/
	fprintf(h_file,"\n");
	fprintf(h_file, "extern ");						/*	Writes the external statement.	*/
	fprintf(h_file, "%s", type);					/*	Writes the type of the function.*/
	fprintf(h_file, " %s",function_name);			/*	Writes the name of the function.*/
	fprintf(h_file, "();");							/*	Adds the braces and a semicolin.*/
}

/*
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Subroutine:	write_function
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Purpose:	Calls functions to write the comment and code section for a function.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	@param:		h_file,				The file that information will be written to.
 |				type,				The return type of the function.
 |				function_name,		The name the function will be.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 */
void write_function_h(FILE* h_file, char* type, char* function_name){
	write_function_head_h(h_file,type,function_name);
	write_function_contents_h(h_file,type,function_name);
	fprintf(h_file,"\n");
}

/*
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Function:	write_h_file
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Purpose:	Creates a header file for the given filename, and calls upon other functions
 |				to write its contents.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	@param:		file_name,		the name the file will be based off.
 |	@return:	0,				File was successfully written.
 |				-1,				Error has occured while writting the file.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 */
int write_h_file(char* directory, char* file_name){
	FILE* h_file;
	char* h_file_name, *function_name;
	int i;									/*Used for loop control.*/
	
	/*	Allocates enough memory for the directory, filename, and extension of the file.	*/
	if( (h_file_name = malloc((strlen(directory)+strlen(file_name)+strlen(".h")+1)*
		sizeof(char))) == NULL){
		/*	Memory allocation was unsuccessful, return error value.	*/
		return -1;
	}
	
	/*	Constructs the complete name of the file for the header file.	*/
	strcpy(h_file_name,directory);
	strcat(h_file_name, file_name);
	strcat(h_file_name,".h");
	h_file_name[strlen(directory) + strlen(file_name)+strlen(".h")] = '\0';
	/*	Begins to write the formatted h file.	*/
	h_file = fopen(h_file_name,"w");
	/*	Writes the head comments for the h file.	*/
	write_h_head(h_file, file_name);
	/*	Makes a name for a function that has a unique name (dependant on filename)	*/
	if( (function_name = malloc((strlen(file_name) + strlen("_function") + 1)*
		sizeof(char))) == NULL){
		/*	Memory allocation was unsuccessful, return error value.	*/
		return -1;
	}
	strcpy( function_name, file_name);
	strcat( function_name, "_function");
	function_name[ (strlen(file_name) + strlen("_function"))] = '\0';
	write_function_h(h_file,"int",function_name);		/*Writes the function to the file.*/
	
	/*	Ends the guard block started in header.	*/
	fprintf(h_file, "\n#endif\n");
	free(function_name);
	function_name = NULL;
	
	if( ferror( h_file) != 0){
		/*	Error has occured somewhere in writing the file.	*/
		fclose(h_file);
		return -1;
	}
	fclose(h_file);
	return 0;
}
