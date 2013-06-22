/*
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Filename:	ProgramCreater.c
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Purpose:	An application that can create formatted files for a project.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Author:		Jonathan Burrows
 |	Date:		Nov 19 2012
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	References:	ProgramCreater.h	Predeclares all functions.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
*/
#include "ProgramCreater.h"

/*
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	main
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Purpose:	An application that can create formatted files for a project.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	@param:		argc,				Not being used.
 |				argv,				Not being used.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
*/
int main(int argc, char** argv){
	list_string* files;
	char* string_input;
	int is_main = 0;

	fprintf(stdout, "\n\nThis program will create new formatted files for a program. These"
					" include:\n\t Header files.\n\tCode files.\n\tA single make file.");
	files = NULL;
	
	while(1){
		/*	Gets the filename from the user.	*/
		string_input = input_string();		
		/*	Checks to see if the user commanded a close.	*/
		if(strcmp(string_input, "close") == 0){		
			fprintf(stdout, "\nYou have issued a close command, closing program.");
			break;
		}
		/*	Checks if error occured while getting input.	*/
		if(string_input == NULL){
			fprintf(stderr, "\nAn error has occured while trying to get input, closing program.");
			break;
		}
		
		
		/*	Checks to see if this is the main file being written.	*/
		if(files==NULL){							/*Is the first file being written.*/
			is_main = 1;							/*Flags this file as being main file.*/
			/*Starts list with this file.*/
			if( (files = init_list_string(string_input)) == NULL){
				fprintf(stderr, "\nError occured creating file, closing program.");
				break;
			}
		}
		else{										/*Not the first file.*/
			/*	Makes sure the file with given name has not already been entered.	*/
			if(in_list_string(files,string_input)){	/*Filenames are already in list.*/
				fprintf(stdout, "\nThe filename \"%s\" has already been taken.\n",
							string_input);
				continue;							/*Reprompts for another filename.*/
			}
			is_main = 0;							/*Flaged as this file not being main.*/
			/* Added to the list of files.*/
			if( (add_node_string(files, string_input)) == -1){
				fprintf(stderr, "\nError occured creating file, closing program.");
				break;
			}
		}
		
		
		/*	The files of the program are created.	*/
		fprintf(stdout, "\n\n\nFiles are being created:");
		
		/*	Main program created, and informs user once done.	*/
		if(write_c_file(DIRECTORY,string_input,is_main) == -1){
			fprintf(stderr, "\nError occured creating file, closing program.");
			break;
		}
		else fprintf(stdout, "\n\tMain program \"%s.c\" created.",string_input);	
		
		/*	Checks to see if a normal header file is needed.	*/
		if(!is_main){
			/*	Writes the header file for the non-main function.	*/
			if(write_h_file(DIRECTORY,string_input) == -1){
				fprintf(stderr, "\nError occured creating file, closing program.");
				break;
			}
			else fprintf(stdout, "\n\tHeader file \"%s.h\" created.",string_input);			
		}
		
		/*	Writes/updates the main header file to include links.	*/
		if(write_main_file_header(DIRECTORY, files) == -1){
			fprintf(stderr, "\nError occured creating file, closing program.");
			break;
		}
		else{
			if(is_main){
				fprintf(stdout, "\n\tMain header file %s.h written.", files->head->value);
			}
			else fprintf(stdout, "\n\tMain header file %s.h updated.", files->head->value);
		}
		
		/*	Writes/Updates the maker file to include all files.	*/
		if(write_m_file(DIRECTORY, files) == -1){
			fprintf(stderr, "\nError occured creating makefile, closing program.");
				break;
		}
		else{
			if(is_main){
				fprintf(stdout, "\n\tMake file \"%s.mak\" written.", string_input);
			}
			else{
				fprintf(stdout, "\n\tMake file \"%s.mak\" updated.", string_input);
			}
		} 		
		
		
		/*	Asks the user if another input is desired, and checks the result.	*/
		if(another_input() == 1){			/*Another input wanted, repeats prompt.*/
			continue;
		}
		else{								/*No more input, exits prompt.*/		
			fprintf(stdout, "\nNo more files desired, closing program.");							
			break;
		}
	}
	
	free(string_input);
	countdown(5);	
	return 0;
}
