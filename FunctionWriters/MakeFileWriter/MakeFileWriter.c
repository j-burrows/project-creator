/*
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Filename:	MakeFileWriter.c
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Purpose:	To write and a makefile for a project that compiles all created files.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Author:		Jonathan Burrows
 |	Date:		Nov 18 2012
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Dependancy:	stdio.h	
 |				stdlib.h
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
*/
#include "MakeFileWriter.h"


/*
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Function:	write_stamp
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Purpose:	This will write stamp on the makfile discribing its name.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	@param:		make_file,			The file to be written on.
 |				filename,			The name that will be written in the stamp, will have
 |									.mak added.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
*/
void write_stamp(FILE* mak_file, char* filename){
	fprintf(mak_file, "#%s.mak", filename);
}

/*
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Subroutine:	write_variables
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Purpose:	This will write the declaration of global variables of the mak file.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	@param:		mak_file,		The file the global variables will be written to.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 */
void write_variables(FILE* mak_file){
	fprintf(mak_file, "\nCC = %s",CC);
	fprintf(mak_file, "\nWARNINGS = %s",WARNINGS);
}

/*
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Subroutine:	write_dependancies
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Purpose:	This will write the dependancies of every file in the project for the 
 |				makefile.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	@param:		mak_file, 		The file where the dependancies are written to.
 |				files,			A list of all the files in the project.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 */
void write_dependancies(FILE* mak_file, list_string* files){
	node_string* conductor;
	
	/*	All dependancy is written.	*/
	fprintf(mak_file,"\n\nall: %s.exe",files->head->value);
	
	/*	Dependancy for the executible code is written.	*/
	fprintf(mak_file,"\n\n%s.exe: ");
	/*	Every file stored's object code is added to the dependancy.	*/
	for(conductor = files->head; conductor != NULL; conductor = conductor->next){
		fprintf(mak_file,"%s.o ",conductor->value);
	}
	/*	compiler code for creating the executible is written. 	*/
	fprintf(mak_file, "\n\t$(CC) $(WARNINGS) ");
	
	/*	Every files object code is added to the code.	*/
	for(conductor = files->head; conductor != NULL; conductor = conductor->next){
		fprintf(mak_file,"%s.o ", conductor->value);
	}
	fprintf(mak_file, "-o %s.exe",files->head->value);	/*Code for actual executable.*/
	
	/*	Writes the dependancies for every files object code.	*/
	/*	Every file stored is visited.	*/
	for(conductor = files->head; conductor != NULL; conductor = conductor->next){
		/*	Dependancies are written.	*/
		fprintf(mak_file,"\n\n");
		fprintf(mak_file,"%s.o: %s.c %s.h", conductor->value,
											conductor->value, conductor->value);
											
		fprintf(mak_file,"\n\t$(CC) -c %s.c", conductor->value);
	}
	
	/*	The clean command is added.	*/
	fprintf(mak_file, "\n\nclean:\n\trm -rf *o\n");
}

/*
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Function:	write_makefile
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Purpose:	This will write the contents of a makefile for a desired program.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	@param:		file_name,			The name of the file to be created without extensions.
 |	@return:	0,					The file was successfully written.
 |				-1,					An error occured whilst writing.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
*/
int write_m_file(char* dependancy, list_string* files){
	FILE* mak_file;
	char* mak_file_name;
	
	/*	Allocates enough memory for the directory, name of the file, and the extension.*/
	if( (mak_file_name = malloc((strlen(dependancy) + strlen(files->head->value) +
		strlen(".mak") + 1)*sizeof(char))) == NULL){
		/*	Allocation was unsuccessful, return error value.	*/
		return -1;
	}
	/*	Contructs the complete file name for the make file.	*/						
	strcpy(mak_file_name, dependancy);
	strcat(mak_file_name, files->head->value);
	strcat(mak_file_name, ".mak");
	mak_file_name[(strlen(dependancy) + strlen(files->head->value) + strlen(".mak"))] = '\0';
		
	mak_file = fopen(mak_file_name, "w");
	
	/*	Writes the contents of the mak file.	*/
	write_stamp(mak_file, files->head->value);	/*The stamp the includes the name of file.*/
	write_variables(mak_file);					/*The global variables.*/
	write_dependancies(mak_file, files);		/*The compile code.*/
	
	free(mak_file_name);						/*mak_file_name never used again.*/
	mak_file_name = NULL;
	
	if( ferror(mak_file) != 0){
		/*	An error occured sometime whilst writing, return error value.	*/
		fclose( mak_file);
		return -1;
	}
	fclose(mak_file);							/*Done writing the file.*/
	return 0;
}
