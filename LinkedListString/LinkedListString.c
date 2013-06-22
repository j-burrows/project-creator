/*
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Filename:	LinkedListString.c
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Purpose:	Functions for traversing, and adding to a linked list.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Author:		Jonathan Burrows
 |	Date:		November 17th 2012
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Dependancy:	stdlib.h			all
 |				string.h			init_node_string
 |									set_node_string
 |				stdio.h				print_list_string
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 */
#include "LinkedListString.h"

/*
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Subroutine:	fprint_list_string
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Purpose:	Prints off all the words in a list of strings.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	@param:		stream,				Where the words will be printed to.
 |				traverse,			The list whos words will be printed.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 */
void fprint_list_string(FILE* stream, list_string* traverse){
	node_string* current;
	fprintf(stream,"\n");
	for(current = traverse->head;current!=NULL;current=current->next){
		fprintf(stream,"%s\t",current->value);
	}
	fprintf(stream,"\n");
}

/*
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Function:	in_list_string
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Purpose:	Checks to see if an item is stored in a linked list.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	@param:		head,				The first node in a linked list.
 |				target,				The name of the file that will be searched for.
 |	@return:	0,					Not in list.
 |				1,					Is in list.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
*/
int in_list_string(list_string* files, char* target){
	node_string* conductor;							/*Pointer used to conduct transverse.*/
	int in = 0;										/*Boolean for if value is in list.*/
	
	/*	Every element in a list is checked to see if it has the target element.	*/
	/*	Starting at the head, the list is traversed until the end is reached.	*/
	for(conductor = files->head; conductor != NULL; conductor = conductor->next){
		/*	The value of the current node is compared with the target value.	*/
		if(strcmp(target, conductor->value) != 0){			/*No match found.*/
			/*	Continue searching.	*/
			continue;
		}
		else{												/*Match is found.*/
			/*	Stop searching.	*/
			in = 1;
			break;
		}
	}
	/* in is 1 if and only if a match has been found, 0 otherwise. */
	return in;
}

/*
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Function:	init_node_string
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Purpose:	Creates and returns a node with a value of a given word.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	@param:		word,				The word the nodes value will be set to.
 |	@return:	node_making,		The newly created node with a value of the given word.
 |				NULL,				Initialisation was unsuccessful.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 */
node_string* init_node_string(char* word){
	node_string* node_making;						/*The new node to be created.*/
	char* adder;									/*Will hold a copy of the word.*/
	
	/*	The word is copied into another string.	*/
	/*	Allocated enough space for word and null characters, checks if successful.	*/
	if( (adder = malloc((1+strlen(word))*sizeof(char))) == NULL){
		/*	Allocation was unsuccessful, return error value.	*/
		return NULL;
	}
	strcpy(adder, word);
	adder[strlen(adder)] = '\0';					/*Ends it with a null character.*/
	
	/*	The node is allocated memory and the value points to a copy of the word. */
	if( (node_making = malloc(sizeof(node_string))) == NULL){
		/*	Allocation was unsuccessful.	*/
		free(adder);
		adder = NULL;
		return NULL;
	}
	node_making->value = adder;
	node_making->next = NULL;
	
	return node_making;
}

/*
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Function:	init_list_string
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Purpose:	Creates and returns a node with a value of a given word.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	@param:		word,				The word the head nodes value will be set to.
 |	@return:	list_making			The newly created list with the head value set to the
 |									given word.
 |				NULL,				Initialisation was unsuccessful.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 */
list_string* init_list_string(char* word){
	list_string* list_making;
	
	/*	Allocates memory for the structures.*/
	if( (list_making = malloc(sizeof(list_string))) == NULL){	/*	Allocation failed.	*/
		return NULL;							
	}
	if( (list_making->head = init_node_string(word)) == NULL){	/*	Allocation failed.	*/
		free(list_making);
		list_making = NULL;
		return NULL;
	}
	list_making->tail = list_making->head;
	return list_making;
}

/*
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Subroutine:	add_node_string
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Purpose:	Creates a node with a given value and adds it to the end of a given list.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	@param:		current,			The list that the node will be added to.
 |				word,				The value the to-be-added node will take.
 |	@return:	0,					The add was successful.
 |				-1,					The add was unsuccessful.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 */
int add_node_string(list_string* current, char* word){
	/*	Declares and sets value of the node to be added.	*/
	node_string* adder;
	if( (adder = init_node_string(word)) == NULL){
		/*	Initialisation of node was unsuccessful.	*/
		return -1;
		
	}
	/*	Adds the new node to the end of the list.	*/
	current->tail->next = adder;
	current->tail = adder;
	
	return 0;
}

/*
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Subroutine:	set_node_string
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Purpose:	Sets the value of a node to a given value.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	@param:		current,			The list that the node will be added to.
 |				word,				The value the to-be-added node will take.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 */
void set_node_string(node_string* current, char* word){
	char* adder;							/*Used to store a copy of the given word.*/
	
	/*	A copy of the word is stored in another string, which ends in a null character.*/
	if( (adder = malloc((1+strlen(word))*sizeof(char))) != NULL){
		/*	Allocation was successful.	*/
		strcpy(adder, word);
		adder[strlen(adder)] = '\0';
	
		free(current->value);					/*Current value is not used again.*/
		current->value = adder;					/*Value points at the new word.*/
	}
	
}
