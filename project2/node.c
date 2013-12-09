// David Chan (N00668317@students.ncc.edu)
// CSC 217
// Project 2: "Data Validation"
// Due 12/03/09 11:59 pm
// Node.c

#include "node.h"

/********************************* CreateNode Module ***********************************
 * Creates a node from the data, return it.
 */

node *CreateNode(char *data)
{
	/*I have to parse the line to extract the informations (name, amount...)
	To do that I'll read the line character by character and search for delimiters
	ex if I want the month, i'll search for / and copy the the characters between the beginning and this /
	to the month integer of the structure*/

	int lastmatch; /*The position to copy from*/
	char temp[512]; /*A temporary string needed when converting to integer*/
	size_t i; 
	node *node;/*the node pointer*/
	node=malloc(sizeof(struct node));
	if(node==NULL)
	{
		fprintf(stderr,"Unable to malloc");
		exit (1);
	}
	/*Copy the given data to our node*/
	strcpy(node->line,data);
	/*No ndex node*/
	node->next=NULL;
	/*Parse data*/
	/*Put the copy from at position 0 (we'll copy the year first)*/
	/*Initialize members*/
	lastmatch=0;
	node->amount=node->day=node->month=node->year=0;
	strcpy(node->lName,"");
	strcpy(node->fName,"");
	/*Go through the data char by char*/
	for(i=0;i<strlen(data);i++)
	{
		/*Found a delimiter: can either be month or day*/
		if(data[i]=='/')
		{
			/*Get the relevant data in temp*/
			strncpy(temp,data+lastmatch,i-lastmatch);
			temp[i-lastmatch]='\0';
			/*if month is null in our struct -> month found*/
			if(node->month==0)
			{
				/*Get the integer*/
				node->month=strtol(temp,0,10);
				/*Update the copy from position for the next match*/
				lastmatch=i+1;
			}
			/*else, day found*/
			else if(node->day==0)
			{
			/*Get the integer*/
				node->day=strtol(temp,0,10);
				/*Update the copy from position for the next match*/
				lastmatch=i+1;
			}
		}
		/*I can either have year, lastname or fist name*/
		else if(data[i]==' ')
		{
			strncpy(temp,data+lastmatch,i-lastmatch);
			temp[i-lastmatch]='\0';
			/*if the year member is null, I've found the year*/
			if(node->year==0)
			{/*Get the integer*/
				node->year=strtol(temp,0,10);
				/*Update the copy from position for the next match*/
				lastmatch=i+1;
			}
			/*If I have a comma before the space, it's the last name*/
			else if(data[i-1]==',')
			{
				strcpy(node->lName,temp);
				/*It contains the comma, remove it!*/
				node->lName[i-lastmatch-1]='\0';
				lastmatch=i+1;
			}
			/*Else it's the first name*/
			else
			{/*Get the integer*/
				strcpy(node->fName,temp);
				/*Update the copy from position for the next match*/
				lastmatch=i+1;
			}
		}
		/*If we found a dollar, we have the amount from it to the end of the string*/
		else if(data[i]=='$')
		{
			strcpy(temp,data+i+1);
			node->amount=strtod(temp,0);
			i=strlen(data);
		}
	}
	return node;
}

/********************************* AddNode Module ***********************************
 * Adds node to the nodeCollection, returns the new collection
 */
node *AddNode(node *nodeCollection, node *nodeToAdd)
{
	/*if node to add is null, then don't make any changes*/
	if(nodeToAdd==NULL)return nodeCollection;
	/*add the node in first position and return the new node collection*/
	nodeToAdd->next=nodeCollection;
	return nodeToAdd;
}

/********************************* FindNode Module ***********************************
 * Find node in nodeCollection, returns the found node, or null.
 */
node *FindNode(node *nodeCollection, node *nodeToFind)
{
	/*navigate through the collection*/
	node *n;
	n=nodeCollection;
	while(n!=NULL)
	{
		/*If found, return the node found node*/
		if(strcmp(n->line,nodeToFind->line)==0)return n;
		n=n->next;
	}
	/*Nothing found, return NULL*/
	return NULL;
}
/********************************* DisplayNode Module ***********************************
 * Displays the nodes in nodeCollection by date, last name, first name, amount (see workcited)
 */
node *DisplayNodes(node *nodeCollection)
{
	node *n,*o,*t;
	/*temporary node to ease sorting*/
	node temp;
	temp.next=nodeCollection;
	/*sort*/
	n=nodeCollection;
	/*This is a classic sorting by insertion*/

	while(n!=NULL)
	{
		if(n->next!=NULL)
		{
			if(n->next->year < n->year || 
			  (n->next->year == n->year && n->next->month < n->month) ||
			  (n->next->year == n->year && n->next->month == n->month && n->next->day < n->day) ||
			  (n->next->year == n->year && n->next->month == n->month && n->next->day == n->day && strcmp(n->next->lName,n->lName) < 0) ||
			  (n->next->year == n->year && n->next->month == n->month && n->next->day == n->day && strcmp(n->next->lName,n->lName) == 0 && strcmp(n->next->fName,n->fName) < 0) ||
			  (n->next->year == n->year && n->next->month == n->month && n->next->day == n->day && strcmp(n->next->lName,n->lName) == 0 && strcmp(n->next->fName,n->fName) == 0 && n->next->amount < n->amount))
			{
				/*Where to insert?*/
				o=&temp;
				while(o!=NULL)
				{
					if(o->next!=NULL)
					{
						if(o->next == n || 
							(n->next->year < o->next->year || 
			  (n->next->year == o->next->year && n->next->month < o->next->month) ||
			  (n->next->year == o->next->year && n->next->month == o->next->month && n->next->day < o->next->day) ||
			  (n->next->year == o->next->year && n->next->month == o->next->month && n->next->day == o->next->day && strcmp(n->next->lName,o->next->lName) < 0) ||
			  (n->next->year == o->next->year && n->next->month == o->next->month && n->next->day == o->next->day && strcmp(n->next->lName,o->next->lName) == 0 && strcmp(n->next->fName,o->next->fName) < 0) ||
			  (n->next->year == o->next->year && n->next->month == o->next->month && n->next->day == o->next->day && strcmp(n->next->lName,o->next->lName) == 0 && strcmp(n->next->fName,o->next->fName) == 0 && n->next->amount < o->next->amount)))
							
						{
							t=n->next;
							n->next=n->next->next;
							/*insert here*/
							t->next=o->next;
							o->next=t;
							o=NULL;
							n=t;
						}
					}
					if(o!=NULL)o=o->next;
				}
			}
		}
		n=n->next;
	}
	

	/*display*/
	n=temp.next;
	while(n!=NULL)
	{
		printf("%s\n",n->line);
		n=n->next;
	}
	return temp.next;
} //ends DisplayNodes

/********************************* DisplayNodeEx Module ***********************************
 * Displays the nodes in nodeCollection by name, amount, date(see workcited)
 */

node *DisplayNodesEx(node *nodeCollection)
{
	node *n,*o,*t;
	/*temporary node to ease sorting*/
	node temp;
	temp.next=nodeCollection;
	/*sort*/
	n=nodeCollection;
	
	/*This is a classic sorting by insertion*/

	while(n!=NULL)
	{
		if(n->next!=NULL)
		{
			if(strcmp(n->next->lName,n->lName) < 0 || 
			  (strcmp(n->next->lName,n->lName) == 0 && strcmp(n->next->fName,n->fName) < 0) ||
			  (strcmp(n->next->lName,n->lName) == 0 && strcmp(n->next->fName,n->fName) == 0 && n->next->amount < n->amount) ||
			  (strcmp(n->next->lName,n->lName) == 0 && strcmp(n->next->fName,n->fName) == 0 && n->next->amount == n->amount && n->next->year < n->year) ||
			  (strcmp(n->next->lName,n->lName) == 0 && strcmp(n->next->fName,n->fName) == 0 && n->next->amount == n->amount && n->next->year == n->year && n->next->month < n->month) ||
			  (strcmp(n->next->lName,n->lName) == 0 && strcmp(n->next->fName,n->fName) == 0 && n->next->amount == n->amount && n->next->year == n->year && n->next->month == n->month && n->next->day < n->day ))
			{
				/*Where to insert?*/
				o=&temp;
				while(o!=NULL)
				{
					if(o->next!=NULL)
					{
						if(o->next == n ||
							(strcmp(n->next->lName,o->next->lName) < 0 || 
			  (strcmp(n->next->lName,o->next->lName) == 0 && strcmp(n->next->fName,o->next->fName) < 0) ||
			  (strcmp(n->next->lName,o->next->lName) == 0 && strcmp(n->next->fName,o->next->fName) == 0 && n->next->amount < o->next->amount) ||
			  (strcmp(n->next->lName,o->next->lName) == 0 && strcmp(n->next->fName,o->next->fName) == 0 && n->next->amount == o->next->amount && n->next->year < o->next->year) ||
			  (strcmp(n->next->lName,o->next->lName) == 0 && strcmp(n->next->fName,o->next->fName) == 0 && n->next->amount == o->next->amount && n->next->year == o->next->year && n->next->month < o->next->month) ||
			  (strcmp(n->next->lName,o->next->lName) == 0 && strcmp(n->next->fName,o->next->fName) == 0 && n->next->amount == o->next->amount && n->next->year == o->next->year && n->next->month == o->next->month && n->next->day < o->next->day )))
						{
							t=n->next;
							n->next=n->next->next;
							/*insert here*/
							t->next=o->next;
							o->next=t;
							o=NULL;
							n=t;
						}
					}
					if(o!=NULL)o=o->next;		
				}
			}
		}
		n=n->next;
	}
	/*display*/
	n=temp.next;
	while(n!=NULL)
	{
		printf("%s\n",n->line);
		n=n->next;
	}
	return temp.next;
}
