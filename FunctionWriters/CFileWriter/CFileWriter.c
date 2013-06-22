/*
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Filename:	CFileWriter.c
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Purpose:	A program that can set up a formatted header file, c-file, and makefile.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Author:		Jonathan Burrows
 |	Date:		November 17th 2012
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Dependancy:	stdlib.h				
 |				stdio.h	
 |				string.h
 |				time.h 
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 */
#include "CFileWriter.h"

/*
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Subroutine:	write_c_head
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Purpose:	Writes the comment section for the c file, and includes the respected header
 |				for the given file.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	@param:		c_file,				The file that information will be written to.
 |				c_file_name,		The name of the file.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 */
void write_c_head(FILE* c_file, char* file_name){	
	fprintf(c_file, "/*");
	
	/*	Filename is added.	*/
	write_divider(c_file);
	write_discriber(c_file, "Filename", file_name);
	fprintf(c_file, ".c");
	
	/*	Purpose is added.	*/
	write_divider(c_file);
	write_discriber(c_file, "Purpose", "what_this_program_is_for");
	
	/*	Author and date is written.	*/
	write_divider(c_file);
	write_discriber(c_file, "Author", AUTHOR);
	write_date(c_file);								/*Function enters the current date.*/
	
	/*	References and dependancies are added. */
	write_divider(c_file);
	/*	Writes the reference to the header file.	*/
	write_discriber(c_file, "References", file_name);
	fprintf(c_file, "\t\t\t\tPredeclares all functions.");
	
	/*	Writes the dependancy discripter.	*/
	write_discriber(c_file, "Dependancy", "<library>");
	fprintf(c_file,"\t\t\tfunctions_that_use_lib");
	
	/*	Writing is finished with a final divider line and a closing comment bracket.	*/
	write_divider(c_file);
	fprintf(c_file, "\n*/");
	
	fprintf(c_file, "\n#include \"%s.h\"\n",file_name);
}

/*
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Subroutine:	write_function_head
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Purpose:	Writes the comment section for a function.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	@param:		c_file,				The file that information will be written to.
 |				type,				The return type of the function.
 |				function_name,		The name the function will be.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 */
void write_function_head_c(FILE* c_file, char* type, char* function_name){
	/*	Writes out the header for function, starting with an opening
	 *	commenting brace and a divider	*/
	fprintf(c_file, "\n/*");	
	write_divider(c_file);
	
	/*	Checks to see if the method is a subroutine or a function, and writes the type as
	 *	a discriber.	*/
	(strcmp(type,"void")==0)? 
		write_discriber(c_file,"Subroutine",function_name)
		:write_discriber(c_file,"Function",function_name);
		
	write_divider(c_file);
	
	/*	Writes the purpose discriber.	*/
	write_discriber(c_file,"Purpose","what_does_this_function_do");
	write_divider(c_file);
	
	/*	Writes the parameter and return discribers.	*/
	write_discriber(c_file,"@param","var_name,\t\t\tWhat_is_this");
	/*	Checks to see if the method will return anything*/
	if(strcmp(type,"void")!=0){
		write_discriber(c_file,"@return","another_var,\t\tWhat_is_this");
	}
	write_divider(c_file);
	
	/*	Writes the algorithm discriber.	*/
	write_discriber(c_file,"Algorithm","How_does_this_program_do_what_it_does");
	write_divider(c_file);
	
	/*	Writes the notes and error discribers.	*/
	write_discriber(c_file,"Notes","Why_must_cryptic_code_be_cryptic");
	write_discriber(c_file,"Errors","What_input_results_in_unexpected");
	write_divider(c_file);
	
	/*	Writes the reference and dependancy discriber.	*/
	write_discriber(c_file, "References", "another_funciton");
	write_discriber(c_file, "Dependancy", "any_libraries");
	write_divider(c_file);
	
	/*	Closes the commenting brace.	*/
	fprintf(c_file, "\n*/");
}

/*
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Subroutine:	write_function_head
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Purpose:	Writes the comment section for a function.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	@param:		c_file,				The file that information will be written to.
 |				type,				The return type of the function.
 |				function_name,		The name the function will be.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 */
void write_function_contents_c(FILE* c_file, char* type, char* function_name){
	/*	Adds padding between itself and comment section.	*/
	fprintf(c_file,"\n");

	
	fprintf(c_file, "%s", type);					/*	Writes the type of the function.*/
	fprintf(c_file, " %s",function_name);			/*	Writes the name of the function.*/
	
	fprintf(c_file, "(){");							/*	Adds the braces and brackets.*/
	
	/* Checks if not a subroutine.	*/
	if(strcmp(type,"void")){						/*	Method is not a subroutine.*/
		/*	Checks if the return value requires a null or a zero.	*/
		if(strcmp(type, "int")==0){					/*	Function is of integer type.*/
			fprintf(c_file, "\n\treturn 0;");		/*	zero return is written.	*/
		}
		else{										/*	Function is not returning an int.*/	
			fprintf(c_file, "\n\treturn NULL;");	/*	NULL return is written.	*/
		}
	}
	
	/*	Closing parenthesis is added.	*/
	fprintf(c_file,"\n}\n");
}

/*
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Subroutine:	write_function_c
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Purpose:	Calls functions to write the comment and code section for a function.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	@param:		c_file,				The file that information will be written to.
 |				type,				The return type of the function.
 |				function_name,		The name the function will be.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 */
void write_function_c(FILE* c_file, char* type, char* function_name){
	write_function_head_c(c_file,type,function_name);
	write_function_contents_c(c_file,type,function_name);
	fprintf(c_file,"\n");
}

/*
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Subroutine:	write_main
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Purpose:	Writes the formatted skeleton code for a main function.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	@param:		file_name,		the name the file will be based off.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 */
void write_main(FILE* c_file){
	write_function_head_c(c_file,"int","main");
	
	fprintf(c_file, "\nint main(int argc, char** argv){\n\treturn 0;\n}\n");
}

/*
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Function:	write_c_file
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Purpose:	Writes the formatted skeleton code for a c file program.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	@param:		directory,		the directory (based on executible location), where the file
 |								will be stored. 
 |				file_name,		the name the file will be based off.
 |	@return		0,				File was successfully written.
 |				-1,				Error occured while writing the file.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 */
int write_c_file( char* directory, char* file_name, int is_main){
	FILE* c_file;
	char* c_file_name, *function_name;
	
	/*	Sets a string to hold the location that the file will be in.	*/
	if((c_file_name = malloc((strlen(directory)+strlen(file_name)+
		strlen(".c")+1)*sizeof(char))) == NULL){
		/*	Allocation of memory for the word has failed.	*/
	}
	strcpy(c_file_name,directory);
	strcat(c_file_name,file_name);
	strcat(c_file_name,".c");
	c_file_name[strlen(directory)+strlen(file_name)+strlen(".c")] = '\0';
	
	/*	Begins to write the formatted c file.	*/
	c_file = fopen(c_file_name,"w");
	
	/*	Writes the head comments for the c file.	*/
	write_c_head(c_file, file_name);
	
	/*	If the main function, it will only write a single function for the main program.*/
	if(is_main){
		write_main(c_file);
	}
	else{
		/*	Makes the unique function name.	*/
		if( (function_name = malloc((strlen(file_name) + strlen("_function") + 1)
			*sizeof(char))) == NULL){
			/*	Allocation of memory has failed, return error value.	*/
			return -1;
		}
		strcpy(function_name,file_name);
		strcat(function_name,"_function");
		function_name[(strlen(file_name) + strlen("_function"))] = '\0';
		
		/*	Writes a sample function.	*/
		write_function_c(c_file,"int",function_name);
	}
	
	free(function_name);
	function_name = NULL;
	
	if(ferror(c_file) != 0){
		/*	An error occured while writting the file.	*/
		fclose(c_file);
		return -1;
	}
	fclose(c_file);
	return 0;
}
