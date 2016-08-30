#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "validation.h"

#pragma warning(disable: 4996)
#define ERR_MSG_BOOK "Грешен формат!"

char condition[] = {'y','n','b','z', NULL};
int (*p[10]) (int x) = {isalpha,isdigit,isdigit,isMinus,isdigit,
						isdigit,isalpha,isdigit,isalpha,isalpha};

int validateBookNumber(char * book_number)
{
	int i = 0;
	if(strlen(book_number) != 10)
	{
		printErrorMessage(ERR_MSG_BOOK);
		return 0;
	}
	for(i = 0; i < 10; i++)
	{
		if(!p[i](book_number[i]))
		{
			printErrorMessage(ERR_MSG_BOOK);
			return 0;
		}
	}
	return 1;
}

int validateBookCondition(char a)
{
	int i = 0;
	while(condition[i])
	{
		if(condition[i++] == a)
		{
			return 1;
		}
		i++;
	}
	printErrorMessage(ERR_MSG_BOOK);
	return 0;
}

int validateString(char * str,int length,int no_name_choice)
{
	if(strlen(str) > length)
	{
		printErrorMessage("Грешен формат!");
		return 0;
	}
	if(no_name_choice)
	{
		if(str[0]=='\0')
			strcpy(str,"-НЯМА-ИМЕ-");
	}
	return 1;
}

int validateDate(char * date, short * day, short * month, short * year)
{
	if(sscanf(date,"%02d.%02d.%04d",day,month,year) != 3)
	{
		printErrorMessage(ERR_MSG_BOOK);
		return 0;
	}
	if(*month > 12 && *month < 1)
	{
		printErrorMessage(ERR_MSG_BOOK);
		return 0;
	}
	if(*month == 2 && !isLeapYear(*year))
	{
		if(*day > 28)
		{
			printErrorMessage("Грешка, февруари има 28 дни тази година");
			return 0;
		}
	}
	else if(*month == 2 && isLeapYear(*year))
	{
		if(*day > 29)
		{
			printErrorMessage("Грешка, февруари има 29 дни тази година");
			return 0;
		}
	}
	else if(*month != 2)
	{
		if(*month % 2 == 0)
		{
			if(*day > 30)
			{
				printErrorMessage("Грешка, месецът има 30 дни");
				return 0;
			}
		}
		else 
		{
			if(*day > 31)
			{
				printErrorMessage("Грешка, месецът има 31 дни");
				return 0;
			}
		}
	}

	if(*year > yearNow())
	{
		printErrorMessage("Календарна грешка!");
		return 0;
	}
	else if(*year == yearNow())
	{
		int cur_day,cur_month;
		get_date(&cur_month,&cur_day);
		if(*month > cur_month)
		{
			printErrorMessage("Календарна грешка!");
			return 0;
		}
		else if(*month == cur_month)
		{
			if(*day > cur_day)
			{
				printErrorMessage("Календарна грешка!");
				return 0;
			}
		}
	}
	return 1;
}

int isMinus(int a)
{
	if(a == '-')return 1;
	return 0;
}

void printErrorMessage(char * msg)
{
	printf("%s\n",msg);
	system("pause");
}

int yearNow()
{
   time_t now;
   char *p;
   int yearint;
   if (time(&now) != (time_t)(-1) )
   {
      struct tm *mytime = localtime(&now);
      if (mytime)
      {
         char year[5];
         strftime(year, sizeof year, "%Y", mytime); 
		 p = year;
		 yearint = strtol(p,&p,10);
      }
   }
   return yearint;
}

void get_date(int * month, int * day)
{
	struct tm *current;
	time_t timenow;
	time(&timenow);
	current = localtime(&timenow);
	*month = current->tm_mon + 1;
	*day = current->tm_mday;
	return;
}

int isLeapYear(int year)
{
	if(year % 4!=0)return 0;
	else if(year % 100!=0)return 1;
	else if(year % 400!=0)return 0;
	else return 1;
}

char * getInput(char * src ,char * msg)
{
	fflush(stdin);
	printf(msg);
	gets(src);
	return src;
}