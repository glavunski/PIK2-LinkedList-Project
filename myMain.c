#include <windows.h>
#include "menu.h"
#include "myList.h"

//------------- ������ -----------------------
char *menu_main[]=
{
	"�������� <������ ������>\n--------------------------",
	"�������� �� ����� ��� ������� �� ������������",
	"���������� �� ����� �� ������� �� ����������� �����",
	"������������ �� ���������� �� ����� �� �����",
	"������������ �������������� �� ������� �� �����",
	"��������� �� ������� ��� ����",
	"��������� �� ��� ������ �� ����",
	"��������� �� ����� �� ����� ��� ���� �� ��������",
	"������������ �� ����� �� ����� �����",
	"����",
	NULL
};

char *menu_add_book[]=
{
	"---�������� �� �����---",
	"�������� � �������� �� �������",
	"�������� � ���� �� �������",
	"�����",
    NULL
};

char *menu_write_file[]=
{
	"---����� ��� ����---",
	"�������",
	"�������",
	"�����",
	 NULL
};

char *menu_read_file[]=
{
	"---������ �� ����---",
	"�������",
	"�������",
	"�����",
    NULL
};

char *menu_sort_list[]=
{
    "---��������� �� �����---",
	"��������� �� �����",
	"��������� �� ���� �� ��������",
	"�����",
	 NULL			
};

char *menu_sort_list_choice[]=
{
	"---����� ������ �� ���������---",
	"��������",
	"��������",
	"�����",
	 NULL
};

char *menu_write_book[]=
{
	"---������������ �� ���������� �� ����� �� �����---",
	"�� �������",
	"�� ����� ���",
	"�����",
	NULL
};

int main()
{
	short mode, submenu1,submenu2;
	Node *head = NULL;
	FILE *fin,*fout;
	char name_file[256],BN[11];
	char name[256];
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	do
	{
		mode = menu(menu_main);
		switch (mode)
		{
			case 1:	
				submenu1 = menu(menu_add_book);
				switch(submenu1)
				{
					case 1:	
						head = addToHead(head,newElement(stdin));
						break;
					case 2:
						head = addToTail(head,newElement(stdin));
						break;
					case 3: break;					
				}
				break;
			case 2:
				if(head == NULL)
				{
					printf("������ ������!\n");
					system("pause");
					break;
				}
				printf("�������� ����� �� �������\n");
				scanf("%s",BN);
				head = deleteByBN(head,BN);
				break;
			case 3:
				printf("�������� ����� �� �������\n");
				scanf("%s",BN);
				FindByBN(head, BN);
				system("pause");
				break;
			case 4:
				PrintList(head);
				break;
			case 5:
				submenu1 = menu(menu_write_file);
				if(head == NULL)
				{
					printf("������ ������!\n");
					system("pause");
					break;
				}
				switch(submenu1)
				{
					case 1:	
						fout = GetNameFile(name_file,"w","�� �����");
						if(writeListTextFile(head,fout) != NULL)
						{
							printf("������\n");
						}
						system("pause");
						break;
					case 2:
						fout = GetNameFile(name_file,"wb","�� �����");
						if(writeListBinaryFile(head,fout) != NULL)
						{
							printf("������\n");
						}
						system("pause");
						break;
					case 3:break;
					
				}break;
			case 6:
				submenu1 = menu(menu_read_file);
				switch(submenu1)
				{
					case 1:
						fin = GetNameFile(name_file,"r","�� ������");
						if(fin == NULL)break;
						head = deleteList(head);
						head = readListTextFile(head,fin);
						break;
					case 2:
						fin = GetNameFile(name_file,"rb","�� ������");
						if(fin == NULL)break;
						head = deleteList(head);
						head = readListBinaryFile(head,fin);
						break;
					case 3:break;
					
				}
				break;
			case 7:
				submenu1 = menu(menu_sort_list);
				if(head == NULL)
				{
					printf("������ ������!\n");
					system("pause");
					break;
				}
				switch(submenu1)
				{
					case 1:
						submenu2 = menu(menu_sort_list_choice);
						switch(submenu2)
						{
							case 1:
								SortListByName(head,1);
								break;
							case 2:
								SortListByName(head,0);
								break;
							case 3:break;
						}
						break;
					case 2:
						submenu2 = menu(menu_sort_list_choice);
						switch(submenu2)
						{
							case 1:
								SortListByDate(head,1);
								break;
							case 2:
								SortListByDate(head,0);
								break;
							case 3:break;
						}
						break;							
					case 3:break;
				}
				break;
			case 8:
				submenu1 = menu(menu_write_book);
				switch(submenu1)
				{
					case 1:
						fflush(stdin);
						printf("�������� ������� �� ������:\n");
						scanf("%s",name);
						FindByAuthor(head,name,1);
						break;
					case 2:
						fflush(stdin);
						printf("�������� ����� ��� �� ������:\n");
						gets(name);
						FindByAuthor(head,name,2);
						break;
					case 3:break;
				}
				break;				
		}
	}
	while (mode != 9);
	deleteList(head);
	fcloseall();	
}
