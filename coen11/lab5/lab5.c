// includes
#include <stdio.h>
#include <string.h>
// defines
// unions
typedef union u{
    int bday[2];
    char ophone[20];
} U;
//structures
typedef struct entry{
    char first_name[50];
    char last_name[50];
    char phone_number[15];
    int flag;
    U info;
} Entry;
// global variables
int counter = 0;
Entry phonebook[10]; 
// functions
int main (void);
void insert();
void show_all(void);
void show_name();
void delete();
void delete_name();
int check_duplicate(char fname[], char lname[]);
// main
int
main (void)
{
    int option;
    while (1)
    {
        // basic menu options
        printf("\nWhat would you like to do?\n");
        printf("1. Add a new entry\n");
        printf("2. Show phonebook list\n");
        printf("3. Show user's info\n");
        printf("4. Delete entry\n");
        printf("5. Delete all entries with given first name\n");
        printf("0. Exit\n");
        printf("\nCurrent number of entries: %d/10\n",counter);
        printf ("\nEnter option: ");
        if (scanf ("%d", &option) != 1)
        {
            printf ("error\n");
            return 0;
        }
        switch (option)
        {
            case 1:
            {
                if(counter==10)
                    printf("\n \"PHONEBOOK IS FULL, CANNOT ADD ENTRY\"\n");
                else
                    insert();
                break;
            }

            case 2:
            {
                show_all();
                break;
            }
                
            case 3:
            {
                show_name();
                break;
            }
            case 4:
            {
                delete();
                break;
            }
            case 5:
            {
                delete_name();
                break;
            }
            case 0:
            {
                //just for fun
                printf ("\n \"RIP :(\"\n");
                return 0;
            }

            default:
                printf ("\n \"WRONG OPTION\"\n");
        }
    }
}

void insert()
{
    char fname[50];
    char lname[50];
    char number[15];

    printf("\nEnter First Name: ");
    scanf("%s",fname);
    printf("\nEnter Last Name: ");
    scanf("%s",lname);
    //checks for duplicate. Exits out the function if user already exists
    if(check_duplicate(fname,lname) == 1)
        {
            printf("\n \"USER ALREADY EXISTS\"\n");
            return;
        }

    printf("\nEnter Number: ");
    scanf("%s",number);

    //creates a struct holding all the information
    Entry e;

    strcpy(e.first_name,fname);
    strcpy(e.last_name,lname);
    strcpy(e.phone_number,number);
    //
    printf("\nEnter Flag Number: ");
    scanf ("%d", &e.flag);
    while(e.flag < 0 || e.flag > 2)
        {
            printf ("\nWrong Option. Try again");
            printf("\nEnter Flag Number: ");
            scanf ("%d", &e.flag);
        }

    //scans flag number for extra info
    switch(e.flag)
    {
        case 0:
        {
            printf("\nEnter Birthday Month: ");
            scanf ("%d", &e.info.bday[0]);
            printf("\nEnter Birthday Date: ");
            scanf ("%d", &e.info.bday[1]);
            break;
        }
        case 1:
        {
            printf("\nEnter Office Phone Number: ");
            scanf ("%s", e.info.ophone);
            break;
        }
        case 2:
        {
            break;
        }
    }

    //sorting idea, finds the right spot to place the user
    Entry *p = &phonebook[0];
    Entry *q = &phonebook[counter];
    while(p<q && strcmp(lname,p->last_name) > 0)
        p++;

    //sorts by last name if first names are the same
    if(p<q && strcmp(lname,p->last_name) == 0)
    {
        while(p<q && strcmp(fname,p->first_name) > 0 && strcmp(lname,p->last_name) == 0)
        {
            p++;
        }
            
    }

    //when the list is either empty or the entry should be added at the end
    if(p==q)
    {
        *p = e;
        counter++;
        printf("\n \"ENTRY SUCCESSFULLY ADDED\"\n");
        return;
    }
    else
    //shifts everything after index i up by 1 to make room for new entry
    {
        while(q>p)
        {
            *q = *(q-1);
            q--;
        }
    //inserts new entry at index i
        *p = e;
        counter++;
        printf("\n \"ENTRY SUCCESSFULLY ADDED\"\n");
        return;
    }
}

void show_all(void)
{
    //checks if list is empty
    if(counter==0)
        printf("\n \"PHONEBOOK IS EMPTY\"\n");
    else
    //displays name and number for each entry
    {
        Entry *p = &phonebook[0];
        Entry *q = &phonebook[counter-1];
        while(p<=q)
        {
            printf("\nName: %s %s, Number: %s",p->first_name,p->last_name,p->phone_number);
            //checks flag number
            if(p->flag==0)
            {
                printf(", Birthday: %d/%d\n", p->info.bday[0],p->info.bday[1]);
            }
            else if (p->flag==1)
            {
                printf(", Office Phone: %s\n",p->info.ophone);
            }
            else if(p->flag==2)
            {
                printf("\n");
            }
            p++;
        }
    }
            
    return;
}

void show_name()
{
    int howMany = 0;
    //checks if list is empty
    if(counter==0)
    {
        printf("\n \"PHONEBOOK IS EMPTY\"\n");
        return;
    }
        
    char lname[50];

    printf ("\nEnter Last Name: ");
    scanf("%s",lname);

    //returns info if user is found in the global array
    Entry *p = &phonebook[0];
    Entry *q = &phonebook[counter-1];
    while(p<=q)
    {
        if(strcmp(lname,p->last_name)==0)
        {
            howMany++;
            printf("\nName: %s %s, Number: %s",p->first_name,p->last_name,p->phone_number);
            
            //checks flag number
            if(p->flag==0)
            {
                printf(", Birthday: %d/%d\n", p->info.bday[0],p->info.bday[1]);
            }
            else if (p->flag==1)
            {
                printf(", Office Phone: %s\n",p->info.ophone);
            }
            else if(p->flag==2)
            {
                printf("\n");
            }
        }
        p++;
    }
    if(howMany==0)
        printf("\n \"NO SUCH USER\"\n");
    return;
}

void delete()
{
    //checks if list is empty
    if(counter==0)
    {
        printf("\n \"PHONEBOOK IS EMPTY\"\n");
        return;
    }

    char fname[50];
    char lname[50];

    printf ("\nEnter First Name: ");
    scanf("%s",fname);
    printf("\nEnter Last Name: ");
    scanf("%s",lname);

    Entry *p = &phonebook[0];
    Entry *q = &phonebook[counter-1];
    while(p<=q)
    {
        if(strcmp(fname,p->first_name)==0 && strcmp(lname,p->last_name)==0)
        {
            //moves all entries following the deleted element down by 1 
            Entry *t = p;
            while(t<=q)
            {
                *t = *(t+1);
                t++;
            }
            //first_names[counter] and phone_numbers[counter] still exists but will never be shown because the value of counter will be decremented by 1.
            counter--;
            printf("\n \"ENTRY SUCCESSFULLY REMOVED\"\n");
            return;
        }
        p++;
    }
    printf("\n \"NO SUCH USER\"\n");
    return;
}

int check_duplicate(char fname[], char lname[])
{
    Entry *p = &phonebook[0];
    Entry *q = &phonebook[counter-1];
    while(p<=q)
    {
        if(strcmp(fname,p->first_name)==0 && strcmp(lname,p->last_name)==0)
            return 1;
        p++;
    }
    return 0;
}


void delete_name()
{
    int howMany = 0;
    //checks if list is empty
    if(counter==0)
    {
        printf("\n \"PHONEBOOK IS EMPTY\"\n");
        return;
    }
    char fname[50];
    printf ("\nEnter First Name: ");
    scanf("%s",fname);

    Entry *p = &phonebook[0];
    Entry *q = &phonebook[counter-1];
    while(p<=q)
    {
        if(strcmp(fname,p->first_name)==0)
        {
            howMany++;
            //moves all entries following the deleted element down by 1 
            Entry *t = p;
            while(t<=q)
            {
                *t = *(t+1);
                t++;
            }
            //first_names[counter] and phone_numbers[counter] still exists but will never be shown because the value of counter will be decremented by 1.
            counter--;
            p--;
        }
        p++;
    }
    if(howMany == 1)
        printf("\n \"1 ENTRY SUCCESSFULLY REMOVED\"\n");
    else if(howMany == 0)
        printf("\n \"NO SUCH USER\"\n");
    else
        printf("\n \"%d ENTRIES SUCCESSFULLY REMOVED\"\n",howMany);
    return;
}