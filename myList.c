#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "myList.h"
#include "validation.h"

#pragma warning(disable: 4996)

char * inputMessages[] = 
{
	"Въведете име на книгата:",
	"Въведете състояние на книгата:",
	"Въведете сериен буквено-цифрен номер на книгата:",
	"Въведете собствено име на автора:",
	"Въведете бащино име на автор:",
	"Въведете фамилно име на автора:",
	"Въведете име на издателя:",
	"Въведете дата на издаване(дд.мм.ГГГГ):"
};

Node * addToHead(Node *head, Node *newE)
{
	if(newE == NULL)return newE;
	newE->next = head;
	return newE;
}

Node * addToTail(Node*head, Node *newE)
{
	Node *last = head;
	if(head == NULL)
	{
		addToHead(head,newE);
		return newE;
	}
	while(last->next!=NULL)
		last = last->next;

	newE->next = NULL;
	last->next = newE;

	return head;
}

void PrintElement(Node * El,FILE * stream)
{
	fprintf(stream,
	"Име:%s \n Номер:%s \n Състояние:%c \n"
	"Автор(Име):%s \n Автор(Презиме):%s \n Автор(Фамилия):%s \n "
	"Име на издателството:%s \n Дата на публикуване:%02d.%02d.%04d \n"
	" -------------------\n",
	El->bk.title, El->bk.book_number, El->bk.av,
	El->bk.name.firstname ,El->bk.name.surname ,El->bk.name.family,
	El->bk.pubname,El->bk.date.day ,El->bk.date.month ,El->bk.date.year);	
}

void PrintList(Node * head)
{
	Node *tmp = head;
	if(tmp == NULL)
	{
		printf("празен списък!\n");
		system("pause");
		return;
	}
	while(tmp != NULL)
	{
		PrintElement(tmp,stdout);
		system("pause");
		tmp = tmp->next;
	}
}

Node * newElement(FILE * fin)
{
	Node * newE = (Node*)malloc(sizeof(Node));
	if (newE != NULL ) 
	{
		if (readElement(newE))
		{
			 free (newE);
			 newE = NULL;
		}
	}
	return newE;
}

short readElement(Node * newE)
{		
	char buf[256];

	strcpy(newE->bk.title,getInput(buf,inputMessages[0]));
	if(!validateString(newE->bk.title,80,1))return 1;

	newE->bk.av = getInput(buf,inputMessages[1])[0];
	if(!validateBookCondition(newE->bk.av))return 1;

	strcpy(newE->bk.book_number,getInput(buf,inputMessages[2]));
	if(!validateBookNumber(newE->bk.book_number))return 1;
	
	strcpy(newE->bk.name.firstname,getInput(buf,inputMessages[3]));
	if(!validateString(newE->bk.name.firstname,20,1))return 1;
	
	strcpy(newE->bk.name.surname,getInput(buf,inputMessages[4]));
	if(!validateString(newE->bk.name.surname,20,1))return 1;

	strcpy(newE->bk.name.family, getInput(buf,inputMessages[5]));
	if(!validateString(newE->bk.name.family,20,1))return 1;
	
	strcpy(newE->bk.pubname,getInput(buf,inputMessages[6]));
	if(!validateString(newE->bk.pubname,50,1))return 1;

	getInput(buf,inputMessages[7]);
	if(!validateDate(buf,&newE->bk.date.day,&newE->bk.date.month,&newE->bk.date.year))return 1;

	return 0; 
}

Node * deleteHead(Node * head)
{
	Node * newHead = NULL;
	if (head != NULL) 
	{
		newHead = head->next;
		free(head);
	}
	
	return newHead;  
}

FILE *GetNameFile(char *name_file, char *mode, char *text)
{
	FILE *fp;
	int err;
	fflush(stdin);
	do
	{
		printf("\nВъведете име на файла %s:",text);
		err = scanf("%s", name_file);
	}
	while(err!=1);
	if ((fp=fopen(name_file,mode))==NULL)
	{
		printf("\nФайлът <%s> Не може да се отвори - error No % d !!!\n",name_file,errno);
		printf("Грешка No %d %s",errno,strerror(errno));
		system("pause");
	}
	else
		printf("\nФайлът  <%s> е отворен успешно за обработка !\n\n", name_file);
	
	system("pause");
	return fp;
}

Node * deleteList(Node * head)
{
	while(!isEmptyList(head))
		head = deleteHead( head );
	
	return head;
}

short isEmptyList(Node * head)
{
	return head == NULL ? 1 : 0;
}

Node *deleteByBN(Node * head, char *FN)
{
	int flag = 0;
	Node *temp,*first = NULL;
	while(head != NULL)
	{
		if(!strcmp(head->bk.book_number,FN))
		{   
			//delete head
			temp = head;
			head = head->next;
			free(temp);
			flag = 1;
		}
		else
		{   
				//delete head->next
			if (first == NULL)
				first = head;

			if (head->next == NULL)
				break;

			if(!strcmp(head->next->bk.book_number,FN))
			{
				temp = head->next;
				head->next = head->next->next;
				free(temp);
				flag = 1;
			}
			else
				head = head->next;
		}
	}
	if(flag)
	{
		printf("Готово!\n");
	}
	else
	{
		printf("Няма такава книга!\n");
	}
	system("pause");
	return first;
}
//----------------------------------------------------------------------
void FindByBN( Node * head, char *FN){

	Node*tmp = head;
	int flag = 0;
	while(tmp != NULL)
	{
		if(!strcmp(tmp->bk.book_number,FN))
		{
			PrintElement(tmp,stdout);
			flag = 1;
		}		
		tmp = tmp->next;
	}

	if(!flag)
		printf("няма такава книга\n");
}
//---------------------------------------------------------------
short writeListBinaryFile(Node *head, FILE *fout){

	Node *tmp = head;
	while(tmp != NULL)
	{
		fwrite(&tmp->bk,sizeof(tmp->bk),1,fout);
		tmp = tmp->next;
	}

	fclose(fout);
	return 0;
}
//---------------------------------------------------------------
Node * readListBinaryFile( Node * head, FILE * fin)
{
	 Node * p;
	 do
	 { 
		 p = (Node *)malloc(sizeof(Node)); 
		 if(!p)
		 {
			 printErrorMessage("Грешка!");
			 return 0;
		 }
		 p->next = NULL; 
		 if(!fread(&(p->bk),sizeof(Book),1,fin))
		 { 
			free(p);
			break; 
		 } 
		 p->next = head; 
		 head = p; 
	 }
	 while(1); 
 return head; 


}
//---------------------------------------------------------------
short writeListTextFile(Node *head, FILE *fout){

	Node *tmp = head;
	while(tmp != NULL)
	{
		PrintElement(tmp,fout);
		tmp = tmp->next;
	}

	fclose(fout);
	return 0;
}
//---------------------------------------------------------------
Node* readListTextFile( Node * head, FILE * fin)
{
	Node * tmp;
	char line[256];
	char state[2];

	tmp =(Node *)malloc(sizeof(Node));
	//tmp->bk.av = 'c';

	 if(!tmp)
	 {
		 printErrorMessage("Грешка!");
		 return 0;
	 }

	 while(fgets(line,256,fin) != NULL)
	 {	 
		sscanf(line,"Име: %[^\n]s",tmp->bk.title);
		sscanf(line,"Номер: %s",tmp->bk.book_number);
		if(sscanf(line,"Състояние: %s",state))
			tmp->bk.av = state[0];
		sscanf(line,"Автор(Име): %s",tmp->bk.name.firstname);
		sscanf(line,"Автор(Презиме): %s",tmp->bk.name.surname);
		sscanf(line,"Автор(Фамилия): %s",tmp->bk.name.family);
		sscanf(line,"Име на издателството: %s",tmp->bk.pubname);
		if(sscanf(line,"Дата на публикуване: %02d.%02d.%04d",
			&tmp->bk.date.day,&tmp->bk.date.month,&tmp->bk.date.year))
		{
			head = addToTail(head,tmp);
			tmp =(Node *)malloc(sizeof(Node));

			if(!tmp)
			{
				printErrorMessage("Грешка!");
				return 0;
			}
		}	
	 }
	 free(tmp);
	return head;
}
//----------------------------------------------------------------------
void FindByAuthor(Node * head, char *name,int choice)
{
	
	Node *tmp = head;
	int flag = 0;
   
	if(choice)
	{
		while(tmp!=NULL)
		{
			if(!strcmp(tmp->bk.name.family,name))
			{
				PrintElement(tmp,stdout);
				system("pause");
				flag = 1;
			}
			tmp=tmp->next;
		}
	}
	else
	{
		while(tmp != NULL)
		{
			if(!strcmp(getFullName(tmp),name))
			{
				PrintElement(tmp,stdout);
				flag = 1;
			}
			tmp=tmp->next;
		}
	}

	if(!flag)
	{
		printf("няма книги с такъв автор\n");
		system("pause");
	}

}

void SortListByName(Node * head,short order)
{
	Node *tmp,*tmp2;
	for(tmp = head; tmp != NULL; tmp = tmp->next)
	{
		for(tmp2 = tmp->next; tmp2 != NULL; tmp2 = tmp2->next)
		{
			if(order)
			{
				if(getNodeNameDifference(tmp,tmp2) > 0)
				{
					SwitchNodes(tmp,tmp2);
				}					
			}
			else
			{
				if(getNodeNameDifference(tmp,tmp2) < 0)
				{
					SwitchNodes(tmp,tmp2);
				}	
			}			
		}
	}
}

void SortListByDate(Node * head,short order)
{
	Node *tmp,*tmp2;
	for(tmp = head; tmp != NULL; tmp = tmp->next)
	{
		for(tmp2 = tmp->next; tmp2 != NULL; tmp2 = tmp2->next)
		{
			if(order)
			{
				if(getNodeDateDifference(tmp,tmp2) > 0)
				{
					SwitchNodes(tmp,tmp2);
				}					
			}
			else
			{
				if(getNodeDateDifference(tmp,tmp2) < 0)
				{
					SwitchNodes(tmp,tmp2);
				}	
			}		
		}
	}
}



void SwitchNodes(Node * tmp,Node * tmp2)
{
	Book temp_book = tmp2->bk;
	tmp2->bk = tmp->bk;
	tmp->bk = temp_book;
}

int getNodeNameDifference(Node * tmp,Node * tmp2)
{
	int x = 0;
	x = strcmp(tmp->bk.name.firstname,tmp2->bk.name.firstname);
	if(!x)x = strcmp(tmp->bk.name.surname,tmp2->bk.name.surname);
	if(!x)x = strcmp(tmp->bk.name.family,tmp2->bk.name.family);
	return x;
}

int getNodeDateDifference(Node * tmp,Node * tmp2)
{
	int x = 0;
	x = tmp->bk.date.year-tmp2->bk.date.year;
	if(!x)x = tmp->bk.date.month-tmp2->bk.date.month;
	if(!x)x = tmp->bk.date.day-tmp2->bk.date.day;
	return x;
}

char * getFullName(Node * tmp)
{
	char name[256];
	strcpy(name,tmp->bk.name.firstname);
	strcat(name," ");
	strcat(name,tmp->bk.name.surname);
	strcat(name," ");
	strcat(name,tmp->bk.name.family);
	return name;
}



