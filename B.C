#include<stdio.h>																																																																		#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<ctype.h>
void clearInput(void);
void addNewcontact(void);
void listAll(void);
void deletecontact(void);
int findcontact(void);
int findnum (int);


typedef struct emp {
    int number,empno,sal,ded,hol;
    char empname[20];
    struct emp *next;
    int count;
    } emp;
emp *firstc,*currentc,*newc;
int cnum = 0;



int main()
{
    FILE *datafile;
    char *filename = "employeedatabase.dat";
    char ch;
    firstc = NULL;

    datafile = fopen(filename,"r");

    if(datafile)
    {
	    firstc = (struct emp *)malloc(sizeof(struct emp));

	    currentc = firstc;
	    while(1)
	    {
		    newc = (struct emp *)malloc(sizeof(struct emp));
		    fread(currentc,sizeof(struct emp),1,datafile);
		    if(currentc->next == NULL)
			    break;
		    currentc->next = newc;
	    currentc->count=0;
		    currentc = newc;
	    }
	    fclose(datafile);
	    cnum = currentc->number;

    }

    do
    {
	fflush(stdin);
	puts("\nWelcome to Employee Database");
	puts("-- -----------------------------");
	puts("1 - Create a new record");
	puts("2 - Delete Record");
	puts("3 - Display all record");
	puts("4 - Searh record");
	puts("-- -----------------------------");
	puts("Q - Save and quit\n");
	printf("\tYour choice:");
	ch = getchar();
	    ch = toupper(ch);
	switch(ch)
	{
	    case '1':
		puts("Add a new record\n");
		fflush(stdin);
		addNewcontact();
		break;
	    case '2':
		puts("Delete a record\n");
		deletecontact();
		break;
	    case '3':
		puts("List all Records\n");
		listAll();
		break;
	    case '4':
		puts("Search a record\n");
		findcontact();
		break;
	    case 'Q':
		puts("Save and quit\n");
		default:
		break;
	}
    }
    while(ch != 'Q');
    currentc = firstc;

    if(currentc == NULL)
	    return(0);
    datafile = fopen(filename,"w");

    if(datafile == NULL)
    {
	    printf("Error writing to %s\n",filename);
	    return(1);
    }

    while(currentc != NULL)
    {
	    fwrite(currentc,sizeof(struct emp),1,datafile);
	    currentc = currentc->next;
    }
    fclose(datafile);
    return(0);
}
/*----------------------------------------------------------------------------*/
void addNewcontact(void)
{
    newc = (struct emp *)malloc(sizeof(struct emp));

    if(firstc==NULL)
	firstc = currentc = newc;

   else
    {
	currentc = firstc;

	while(currentc->next != NULL)currentc = currentc->next;

	currentc->next = newc;
	currentc = newc;
    }

    cnum++;
    printf("%27s: %5i\n","Record number",cnum);
    currentc->number = cnum;

    printf("%27s: ","Enter Employee name");
    gets(currentc->empname);

    printf("%27s: ","Enter Employee number");
    scanf("%d",&currentc->empno);

    printf("%27s: ","Enter Employee salary");
    scanf("%d",&currentc->sal);

    printf("%27s: ","Enter Employee deductions");
    scanf("%d",&currentc->ded);

    printf("%27s: ","Enter No of holidays given to employee");
    scanf("%d",&currentc->hol);
    printf("Employee added!");
    currentc->count=0;

    currentc->next = NULL;
}

void listAll(void)
{
    if(firstc==NULL)
	puts("There are no records of employees!");

    else
    {
	    printf("%6s %-20s %-15s %-7s %-12s %-8s\n","Acct#","Employee Name","Employee No","Salary","Deductions","Holiday");
	puts("------ -------------------- ------------- ------- ------------ -------");
			    /*prints table titles*/
	currentc=firstc;

	do
	{

		printf("%6d %-20s %-15d %-7d %-12d %-8d\n",\
		currentc->number,\
		currentc->empname,\
		currentc->empno,\
		currentc->sal,\
		currentc->ded,\
		currentc->hol);
	}

	while((currentc=currentc->next) != NULL);
    }
}
void deletecontact(void)
{
    int record;
    struct emp *previousa;

    if(firstc==NULL)
    {
	puts("There are no records to delete!");
	return;
    }

    listAll();
    printf("Enter employee account number to delete: ");
    scanf("%d",&record);

    currentc = firstc;

    while(currentc != NULL)
    {
	if(currentc->number == record)
	{
	    if(currentc == firstc)
		firstc=currentc->next;
	    else
		previousa->next = currentc->next;

	free(currentc);
	    printf("record %d deleted!\n",record);
	    return;
	}

	else
	{
	previousa = currentc;
	    currentc = currentc->next;
	}
    }
    printf("Record %d not found!\n",record);
 }
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
int findnum (int recordnum)
{
    int record;
    record = recordnum;
    currentc = firstc;
    while(currentc != NULL)
    {

	if(currentc->number == record)
	     {
	   return 1;
	 }

	else
	{
	    currentc = currentc->next;
	}
    }
    return -1;
}
/*----------------------------------------------------------------------------*/
int findcontact(void) /* find contact function*/
{
     char buff[20];

     if(firstc==NULL)
	{
	puts("There are no Records to find!");
	    return 1;
    }

    printf("Enter Employee name: ");
    fflush(stdin);/*clears any text from the input stream*/
    gets(buff);

    currentc = firstc;
    while(currentc != NULL)
    {
	if( strcmp(currentc->empname, buff) == 0 )
	    {

	      printf("%6s %-20s %-15s %-7s %-12s %-8s\n","Acct#","Employee Name","Employee No","Salary","Deductions","Holiday");
		puts("------ -------------------- ------------- ------- ------------ -------");
		/*prints table titles*/
		printf("%6d %-20s %-15d %-7d %-12d %-8d\n",\
		currentc->number,\
		currentc->empname,\
		currentc->empno,\
		currentc->sal,\
		currentc->ded,\
		currentc->hol);

			return 0;
	    }
		else
		{
			currentc = currentc->next;
		}
    }
    printf("Record %s was not found!\n",buff);
	  return 1;
}
/*----------------------------------------------------------------------------*/
