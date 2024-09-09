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
void insert(char name[50], char number[15]);
void show_all(void);
void show_name(char name[50]);
// main
int
main (void)
{
    int option;
    while (1)
    {
        printf("\nWhat would you like to do?\n");
        printf("1. Add a new entry\n");
        printf("2. Show Phonebook list\n");
        printf("3. Show Specific User's Number\n");
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
                    printf("\nPhonebook is full, cannot add entry\n");
                else
                {
                    char name[50];
                    char number[15];
                    printf("\nEnter First Name: ");
                    scanf("%s",name);
                    printf("Enter Number: ");
                    scanf("%s",number);

                    insert(name,number);
                }
                break;
            }

            case 2:
            {
                show_all();
                break;
            }
                
            case 3:
            {
                char name[50];
                printf ("\nEnter First Name: ");
                scanf("%s",name);
                show_name(name);

                break;
            }

            case 0:
            {
                printf ("\nexit\n");
                return 0;
            }

            default:
                printf ("\nwrong option\n");
        }
    }
}

void insert(char name[50], char number[15])
{
    {
        strcpy(first_names[counter],name);
        strcpy(phone_numbers[counter],number);
        counter++;
        printf("\nEntry Successfully Added\n");
        return;
    }
}

void show_all(void)
{
    if(counter==0)
        printf("\nPhonebook is empty\n");
    else
    {
        int i = 0;
        for(i=0;i<counter;i++)
            printf("\nName: %s, Number: %s\n",first_names[i],phone_numbers[i]);
    }
    return;
}

void show_name(char name[50])
{
    int i = 0;
    for(i=0;i<counter;i++)
    {
        if(strcmp(name,first_names[i])==0)
        {
            printf("\nNumber: %s\n",phone_numbers[i]);
            return;
        }
    }
    printf("\nNo such user");
    return;
}