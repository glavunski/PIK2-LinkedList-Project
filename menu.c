#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

short menu( char *t[])
{
	
	int k,i=1;
	char ch;
	system("cls");
	printf ("\n%s\n",t[0]);
	while (t[i]){
		printf("\n%d.%s", i,t[i]);i++;}
	printf ("\n\nВашият избор:");
	i--;
	do
	{
 
		ch=getch();
		k=ch-'0';
	} while(k<=0 || k >i);

	printf("%c\n",ch);

	return ch-'0';
}
//------------------------------------------------------------------------------------------
