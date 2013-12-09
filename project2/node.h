// David Chan (N00668317@students.ncc.edu)
// CSC 217
// Project 2: "Data Validation"
// Due 12/03/09 11:59 pm
// node.h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node{

	char line[512]; /*The line read in the file*/

	/*The informations parsed from the line*/
	long year,month,day;
	double amount;
	char fName[512],lName[512];
	/*The next node, if any*/
	struct node *next;

} node ;


/*Creates a node from the data, return it.*/
node *CreateNode(char *data);
/*Adds node to the nodeCollection, returns the new node collection*/
node *AddNode(node *nodeCollection, node *nodeToAdd);
/*Find node in nodeCollection, returns the found node, or null if not found.*/
node *FindNode(node *nodeCollection, node *nodeToFind);
/*Displays the nodes in nodeCollection by date, last name, first name, amount*/
node *DisplayNodes(node *nodeCollection);
/*Displays the nodes in nodeCollection by name, amount, date*/
node *DisplayNodesEx(node *nodeCollection);
