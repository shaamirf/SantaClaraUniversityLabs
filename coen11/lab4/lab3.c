// includes
#include <stdio.h>
#include <string.h>
// defines
//structures
typedef struct entry{
    char first_name[50];
    char last_name[50];
    char phone_number[15];
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
void deleteAll();
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
        printf("3. Show specific user's number\n");
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
                deleteAll();
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

    printf("Enter Number: ");
    scanf("%s",number);

    //creates a struct holding all the information
    Entry e;

    strcpy(e.first_name,fname);
    strcpy(e.last_name,lname);
    strcpy(e.phone_number,number);

    //sorting idea, finds the right spot to place the user
    int i = 0;
    while(i<counter && strcmp(fname,phonebook[i].first_name) > 0)
        i++;

    //sorts by last name if first names are the same
    if(i<counter && strcmp(fname,phonebook[i].first_name) == 0)
    {
        while(i<counter && strcmp(lname,phonebook[i].last_name) > 0)
            i++;
    }

    //when the list is either empty or the entry should be added at the end
    if(i==counter)
    {
        phonebook[i] = e;
        counter++;
        printf("\n \"ENTRY SUCCESSFULLY ADDED\"\n");
        return;
    }
    else
    //shifts everything after index i up by 1 to make room for new entry
    {
        int j;
        for(j=counter;j>i;j--)
        {
            phonebook[j] = phonebook[j-1];
        }
    //inserts new entry at index i
        phonebook[i] = e;
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
    //displays name next to number for each entry
    {
        int i = 0;
        for(i=0;i<counter;i++)
            printf("\nName: %s %s, Number: %s\n",phonebook[i].first_name,phonebook[i].last_name,phonebook[i].phone_number);
    }
    return;
}

void show_name()
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

    //returns phone number if user is found in the global array
    int i = 0;
    for(i=0;i<counter;i++)
    {
        if(strcmp(fname,phonebook[i].first_name)==0 && strcmp(lname,phonebook[i].last_name)==0)
        {
            printf("\nNumber: %s\n",phonebook[i].phone_number);
            return;
        }
    }
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

    int i;
    for(i=0;i<counter;i++)
    {
        if(strcmp(fname,phonebook[i].first_name)==0 && strcmp(lname,phonebook[i].last_name)==0)
        {
            //moves all entries following the deleted element down by 1 
            int j;
            for(j=i;j<counter;j++)
            {
                phonebook[j] = phonebook[j+1];
            }
            //first_names[counter] and phone_numbers[counter] still exists but will never be shown because the value of counter will be decremented by 1.
            counter--;
            printf("\n \"ENTRY SUCCESSFULLY REMOVED\"\n");
            return;
        }
    }
    printf("\n \"NO SUCH USER\"\n");
    return;
}

int check_duplicate(char fname[], char lname[])
{
    int i;
    for(i=0;i<counter;i++)
    {
        if(strcmp(fname,phonebook[i].first_name)==0 && strcmp(lname,phonebook[i].last_name)==0)
            return 1;
    }
    return 0;
}


/// CONTINUE FROM HERE
void deleteAll()
{
    //checks if list is empty
    if(counter==0)
    {
        printf("\n \"PHONEBOOK IS EMPTY\"\n");
        return;
    }
    char fname[50];
    printf ("\nEnter First Name: ");
    scanf("%s",fname);

    int i;
    for(i=0;i<counter;i++)
    {
        if(strcmp(fname,phonebook[i].first_name)==0)
        {
            //moves all entries following the deleted element down by 1 
            int j;
            for(j=i;j<counter;j++)
            {
                phonebook[j] = phonebook[j+1];
            }
            //first_names[counter] and phone_numbers[counter] still exists but will never be shown because the value of counter will be decremented by 1.
            counter--;
            i--;
        }
    }
    printf("\n \"ENTRIES SUCCESSFULLY REMOVED\"\n");
    return;
}