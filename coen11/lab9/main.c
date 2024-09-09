// includes
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lab9.h"
#include <pthread.h>
#include <unistd.h>
// defines

pthread_mutex_t mutex;

// main
int
main (int argc, char *argv[])
{
    if(argc < 3)
    {
        printf("missing arguments\n");
        return 0;
    }
    else
    {
        read_from_file(argv[1]);
    }

    pthread_t thread;
    pthread_mutex_init(&mutex,NULL);
    pthread_create(&thread,NULL,autosave,(void*)argv[2]);

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
        printf("6. Show binary file contents\n");
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
                read_from_keyboard();
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
            case 6:
            {
                read_from_binary_file(argv[2]);
                break;
            }
            case 0:
            {
                //just for fun
                printf ("\n \"RIP :(\"\n");

                pthread_mutex_lock(&mutex);
                pthread_cancel(thread);
                pthread_mutex_unlock(&mutex);

                save_to_file(argv[1]);
                deleteall();
                return 0;
            }

            default:
                printf ("\n \"WRONG OPTION\"\n");
        }
    }
}

