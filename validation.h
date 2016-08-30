
int validateBookNumber(char * book_number);
int validateBookCondition(char a);
int validateString(char * str,int length,int no_name_choice);
int validateDate(char * date,short * day,short * month,short * year);
int isMinus(int a);

void get_date(int * month, int * day);
int isLeapYear(int year);
int yearNow();

void printErrorMessage(char * msg);
char * getInput(char * src, char * msg);