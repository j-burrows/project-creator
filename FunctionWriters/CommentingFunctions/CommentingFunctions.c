/*
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Filename:	CommentingFunctions.c
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Purpose:	Provide functions for creating comment sections.
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
#include "CommentingFunctions.h"
 
/*
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Subroutine:	write_divider
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Purpose:	Writes a divider between two sections of comments.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	@param:		to_write,			The file that the divider will be written to.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 */
void write_divider(FILE* to_write){
	int i, j;
	/*	Adds padding.	*/
	fprintf(to_write, "\n");
	
	/*	Writes an entire line of " ---"	*/
	for( i=1; i <= 23; i++){
		fprintf(to_write," ");
		for( j=1; j <= 3; j++){
			fprintf(to_write, "-");
		}
	}
}

/*
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Subroutine:	write_discriber
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Purpose:	Writes discriber, followed by a discription in a new line of text.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	@param:		to_write,			The file that the discriber will be written to.
 |				discriber,			The name of the discriber.
 |				discription,		The discription of the discriber.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 */
void write_discriber(FILE* to_write, char* discriber, char* discription){
	fprintf(to_write, "\n");
	
	/*	Writes the disciber following the " *tab".	*/
	fprintf(to_write, " |\t%s:",discriber);
	
	/*	Writes an addition tab if the discripter is small.	*/
	if((1+strlen(discriber))< 8){
		fprintf(to_write, "\t");
	}
	/*	Writes a tab to seperate discipter and the disciption.	*/
	fprintf(to_write, "\t");
	/*	Writes the discription.*/
	fprintf(to_write, "%s",discription);
}

/*
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Subroutine:	write_date
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Purpose:	Writes the date in the form month, day, year.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	@param:		to_write,			The file that the date will be written to.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 */
void write_date(FILE* to_write){
	time_t current_time;
	struct tm * timeinfo;
	char* date;
	int i;

	time ( &current_time );		/*Does a system call to get the time since January 1, 1970*/
	timeinfo = localtime ( &current_time );			/*	Converts into calendar date.*/
	date = asctime(timeinfo);						/*	Converts it into string.*/
	
	fprintf (to_write,  "\n |\tDate:\t\t");
	
	/*	Goes through the date, printing to the file only the month, day, and year.	*/
	for(i=4; i <= 9; i++){
		fprintf(to_write,"%c",date[i]);
	}
	for(i=19; i<=23; i++){
		fprintf(to_write,"%c",date[i]);
	}
	
	free(date);										/*	date is never used again.*/
	date = NULL;
}
