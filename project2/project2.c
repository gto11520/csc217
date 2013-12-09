// David Chan (N00668317@students.ncc.edu)
// CSC 217
// Project 2: "Data Validation"
// Due 12/03/09 11:59 pm
// Project2.c

#include "node.h"

#define MAX_LINE 512 /*max number of chartacter per lines in the files*/

int main(int argc, char *argv[])
{
	FILE *file; /*file stream*/
	char line[MAX_LINE]; /*line which will hold the read data*/
	char c; /*character used to read char by char*/
	int pos; /*the actual position where c has to be put in line*/
	int nSwitch=0; /*was the -n switch invoked?*/
	node *nodeCollection,*nodeCollectionCompare;  /*pointers to the collections of nodes (file1 - file2)*/
	node *node,*foundNode; /*variables to ease navigation in the collection*/

	/*check if I have the filenames?*/
	if(argc<1 + 2) /*less than two arguments*/
	{
		fprintf(stderr, "Not enough filenames!");
		return 1;
	}
	/* chech for n switch in the first argument. extra credit */
	if(strcmp(argv[1],"-n")==0)nSwitch=1;

	/*Read first file in read mode and store transactions*/
	file=fopen(argv[1+nSwitch],"r");
	if(file==NULL)
	{
		fprintf(stderr, "Unable to open file %s",argv[1+nSwitch]);
		return 1;
	}
	/*initialize my two node collection: the first one comes from the first file,
	the second one stores the data not present in the first collection*/
	nodeCollection=NULL;
	nodeCollectionCompare=NULL;

	/*Read the file character by character, and line by line*/
	c=getc(file);
	pos=0;
	/*While its not in the end of the file, keep reading*/
	while(feof(file)==0)
	{
		/*read every character until its see the next line char (\n)*/
		while(feof(file)==0 && c!='\n')
		{
			if(pos>MAX_LINE-1)/*Too many characters in line!*/
			{
				fprintf(stderr, "Line is more than %i chars in file %s",MAX_LINE,argv[1+nSwitch]);
				return 1;
			}
			/* check to see if it can have \r\n instead of \n*/
			if(c!='\r')
			{
			/*Put the read data in our line string*/
				line[pos]=c;
				pos++;				
			}/*read the next character*/
			c=getc(file);
		}
		/*I have found the next line character. Terminate the string correctly*/
		line[pos]='\0';

		/* Line is in line. Create a node and add it to the collection*/

		node=CreateNode(line);
		nodeCollection=AddNode(nodeCollection,node);

		/*Do the same for the next line and so on*/
		pos=0;
		c=getc(file);
	}

	/*All transactions are in the collection.*/
	fclose(file);

	/*Read the second file, exactly the same algorithm*/
	file=fopen(argv[2+nSwitch],"r");
	if(file==NULL)
	{
		fprintf(stderr, "Unable to open file %s",argv[2+nSwitch]);
		return 1;
	}

	c=getc(file);
	pos=0;
	while(feof(file)==0)
	{
		while(feof(file)==0 && c!='\n')
		{
			if(pos>MAX_LINE)
			{
				fprintf(stderr, "Line is more than %i chars in file %s",MAX_LINE,argv[2+nSwitch]);
				return 1;
			}
			if(c!='\r')
			{
				line[pos]=c;
				pos++;				
			}
			c=getc(file);
		}
		line[pos]='\0';

		/*Create and add or node in the nodeCollectionCompare only if not found in the first collection.*/
		node=CreateNode(line);
		foundNode=FindNode(nodeCollection,node);
		if(foundNode==NULL)
		nodeCollectionCompare=AddNode(nodeCollectionCompare,node);
		else free(node);

		pos=0;
		c=getc(file);
	}

	/*File has been read. Display differences according to the nswitch presence*/
	if(nSwitch) DisplayNodesEx(nodeCollectionCompare);
	else DisplayNodes(nodeCollectionCompare);

	/*Cleanup the collection, free all objects one by one(see workcited)*/

	node=nodeCollection;
	if(node!=NULL)
	foundNode=nodeCollection->next;
	while(node!=NULL)
	{
		free(node);
		node=foundNode;
		if(node!=NULL)
		foundNode=node->next;
	}

	node=nodeCollectionCompare;
	if(node!=NULL)
	foundNode=nodeCollectionCompare->next;
	while(node!=NULL)
	{
		free(node);
		node=foundNode;
		if(node!=NULL)
		foundNode=node->next;
	}

	fclose(file);
	return 0;
	
}
