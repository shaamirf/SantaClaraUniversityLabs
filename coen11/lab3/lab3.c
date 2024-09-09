// includes
#include <stdio.h>
#include <string.h>
// defines
// global variables
int counter = 0;
char first_names[10][50];
char phone_numbers[10][50];
// functions
int main (void);
void insert();
void show_all(void);
void show_name();
void delete();
int check_duplicate(char name[50]);
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
        printf("2. Show Phonebook list\n");
        printf("3. Show Specific User's Number\n");
        printf("4. Delete Entry\n");
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
    char name[50];
    char number[15];

    printf("\nEnter First Name: ");
    scanf("%s",name);
    //checks for duplicate. Exits out the function if user already exists
    if(check_duplicate(name) == 1)
        {
            printf("\n \"USER ALREADY EXISTS\"\n");
            return;
        }

    printf("Enter Number: ");
    scanf("%s",number);

    //sorting idea, finds the right spot to place the user
    int i = 0;
    while(i<counter && strcmp(name,first_names[i]) >= 1){
        i++;
    }

    //when the list is either empty or the entry should be added at the end
    if(i==counter)
    {
        strcpy(first_names[counter],name);
        strcpy(phone_numbers[counter],number);
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
            strcpy(first_names[j],first_names[j-1]);
            strcpy(phone_numbers[j],phone_numbers[j-1]);
        }
    //inserts new entry at index i
        strcpy(first_names[i],name);
        strcpy(phone_numbers[i],number);
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
            printf("\nName: %s, Number: %s\n",first_names[i],phone_numbers[i]);
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
        
    char name[50];
    printf ("\nEnter First Name: ");
    scanf("%s",name);

    //returns phone number if user is found in the global array
    int i = 0;
    for(i=0;i<counter;i++)
    {
        if(strcmp(name,first_names[i])==0)
        {
            printf("\nNumber: %s\n",phone_numbers[i]);
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

    char name[50];
    printf ("\nEnter First Name: ");
    scanf("%s",name);

    int i;
    for(i=0;i<counter;i++)
    {
        if(strcmp(name,first_names[i])==0)
        {
            //moves all entries following the deleted element down by 1 
            int j;
            for(j=i;j<counter;j++)
            {
                strcpy(first_names[j],first_names[j+1]);
                strcpy(phone_numbers[j],phone_numbers[j+1]);
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

int check_duplicate(char name[50])
{
    int i;
    for(i=0;i<counter;i++)
    {
        if(strcmp(name,first_names[i])==0)
            return 1;
    }
    return 0;
}