// includes
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lab6.h"
// defines

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
        printf("\nCurrent number of entries: %d\n",counter);
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

