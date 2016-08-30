#include <stdio.h>
//-----------------------------------

#define 	MAX_AUTHOR_NAME 20

struct dateOfPub
{
	short day;
	short month;
	short year;
};


struct author_name
{
	char firstname[MAX_AUTHOR_NAME+1];
	char surname[MAX_AUTHOR_NAME+1];
	char family[MAX_AUTHOR_NAME+1];
};
	
typedef struct bk
{
	struct author_name name;
	char book_number[11];
	char title[81];
	char pubname[51];
	char av;
	struct dateOfPub date;

}Book;

typedef struct item
{
	Book bk;
	struct item *next;

}Node;
	

short readElement(Node * newE);
short readElementBinaryFile( Node * newE, FILE * fin);
Node * readListBinaryFile( Node * head, FILE * fin);
Node * newElement(FILE *fin);
Node * addToHead( Node * head, Node * newE);
Node * addToTail( Node * head, Node * newE);

Node * deleteByBN( Node * head, char *FN);
Node * deleteList( Node * head );
short isEmptyList( Node * head );

void PrintElement(Node *El,FILE * stream);

void PrintBooks(Node *head);
void PrintList(Node *head);

short writeListBinaryFile(Node *head, FILE *fout);
FILE *GetNameFile(char *name_file, char *mode, char *text);

void SortListByName( Node * head, short order );
void SortListByDate( Node * head, short order );
void SwitchNodes(Node * tmp,Node * tmp2);

void FindByBN( Node * head, char *FN);
void FindByAuthor(Node * head, char *name,int choice);

Node * newElementTextFile(FILE *fin);
short readElementTextFile( Node * newE, FILE * fin);
Node * readListTextFile( Node * newE, FILE * fin);
short writeListTextFile(Node *head, FILE *fout);
short writeElementTextFile( Node * curE, FILE * fout);

char * getFullName(Node * tmp);
int getNodeDateDifference(Node * tmp,Node * tmp2);
int getNodeNameDifference(Node * tmp,Node * tmp2);
