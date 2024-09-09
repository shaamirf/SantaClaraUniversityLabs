#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lab10.h"
#include <pthread.h>

// global variables

int counter = 0;
NODE* phonebook[3] = { 0 };

//functions

void read_from_keyboard()
{
    //creates a struct holding all the information
    Entry e;

    printf("\nEnter First Name: ");
    scanf("%s",e.first_name);
    printf("\nEnter Last Name: ");
    scanf("%s",e.last_name);
    //checks for duplicate. Exits out the function if user already exists
    if(check_duplicate(e.first_name,e.last_name) == 1)
        {
            printf("\n \"USER ALREADY EXISTS\"\n");
            return;
        }
    
    printf("\nEnter Number: ");
    scanf("%s",e.phone_number);

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
    pthread_mutex_lock(&mutex);
    insert(e);
    pthread_mutex_unlock(&mutex);
    return;
}

void insert(Entry e)
{

    //creating a new node to store the info
    NODE* new = (NODE*)malloc(sizeof(NODE));
    new->ent = e;
    new->next = NULL;

    //temporary node to traverse the linked list
    char c = e.last_name[0];
    int i;

    if((c >= 65 && c <= 75) || (c >=97 && c <= 107))
        i = 0;
    else if((c > 75 && c < 82) || (c > 107 && c < 114))
        i = 1;
    else if((c >= 82 && c <= 90) || (c >= 114 && c <= 122))
        i = 2;
    
    NODE*current = phonebook[i];

    //case 1: empty list
    if(phonebook[i]==NULL)
    {
        new->next = phonebook[i];
        phonebook[i] = new;
    }
    //case 2: inserting at the beginning of the list
    else if(strcmp( e.last_name , phonebook[i]->ent.last_name) < 0)
    {
        new->next = phonebook[i];
        phonebook[i] = new;
    }
    //case 3: inserting in front of other nodes based off alphabetical order
    else
    {
        //sort by last name
        while(current->next!=NULL && strcmp(e.last_name , current->next->ent.last_name) > 0)
        {
            current = current->next;
        }

        //sort by first name if last names match
        if(current->next!=NULL && strcmp(e.last_name , current->next->ent.last_name) == 0)
        {
            while(current->next!=NULL && strcmp(e.first_name , current->next->ent.first_name) > 0 && strcmp(e.last_name , current->next->ent.last_name) == 0)
            {
                current = current->next;
            }
                
        }
        //inserting the node in the right spot
        new->next = current->next;
        current->next = new;
    }

    counter++;
    printf("\n \"ENTRY SUCCESSFULLY ADDED\"\n");
    return;

}

void show_all(void)
{
    //checks if list is empty
    if(phonebook[0] == NULL && phonebook[1] == NULL && phonebook[2] == NULL)
        printf("\n \"PHONEBOOK IS EMPTY\"\n");
    else
    {
        int i;
        for (i = 0; i < 3; i++)
        {
            NODE*current = phonebook[i];
             //temporary node and loop to traverse the linked list
            while(current!=NULL)
            {
                Entry e = current->ent;
                //displays name and number for each entry
                printf("\nName: %s %s, Number: %s",e.first_name,e.last_name,e.phone_number);
                //checks flag number
                
                if(e.flag==0)
                {
                    printf(", Birthday: %d/%d\n", e.info.bday[0],e.info.bday[1]);
                }
                else if (e.flag==1)
                {
                    printf(", Office Phone: %s\n",e.info.ophone);
                }
                else if(e.flag==2)
                {
                    printf("\n");
                }
                current = current->next;
            }
        }
    } 
    return;
}

void show_name()
{
    int howMany = 0;
    //checks if list is empty
    if(phonebook[0] == NULL && phonebook[1] == NULL && phonebook[2] == NULL)
    {
        printf("\n \"PHONEBOOK IS EMPTY\"\n");
        return;
    }
    else
    {
        //stores name for comparison
        char lname[50];
        printf ("\nEnter Last Name: ");
        scanf("%s",lname);
        
        char c = lname[0];
        int i;

        if((c >= 65 && c <= 75) || (c >=97 && c <= 107))
            i = 0;
        else if((c > 75 && c < 82) || (c > 107 && c < 114))
            i = 1;
        else if((c >= 82 && c <= 90) || (c >= 114 && c <= 122))
            i = 2;
        
        NODE*current = phonebook[i];

        //temporary node and loop to traverse the linked list
        while(current!=NULL)
        {
            Entry e = current->ent;
            if(strcmp(lname,e.last_name)==0)
            {
                howMany++;
                printf("\nName: %s %s, Number: %s",e.first_name,e.last_name,e.phone_number);
                
                //checks flag number
                if(e.flag==0)
                {
                    printf(", Birthday: %d/%d\n", e.info.bday[0],e.info.bday[1]);
                }
                else if (e.flag==1)
                {
                    printf(", Office Phone: %s\n",e.info.ophone);
                }
                else if(e.flag==2)
                {
                    printf("\n");
                }
            }
            current = current->next;
        }
    }    
    
    if(howMany==0)
        printf("\n \"NO SUCH USER\"\n");
    return;
}

void delete()
{
    //checks if list is empty
    if(phonebook[0] == NULL && phonebook[1] == NULL && phonebook[2] == NULL)
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

    char c = lname[0];
    int i;

    if((c >= 65 && c <= 75) || (c >=97 && c <= 107))
        i = 0;
    else if((c > 75 && c < 82) || (c > 107 && c < 114))
        i = 1;
    else if((c >= 82 && c <= 90) || (c >= 114 && c <= 122))
        i = 2;

    NODE*previous = phonebook[i];
    NODE*current = phonebook[i];

    //temporary nodes and loop to traverse the linked list
    //previous node meant to follow behind current pointer
    
    pthread_mutex_lock(&mutex);

    while(current!=NULL)
    {
        Entry e = current->ent;
        if(strcmp(fname,e.first_name)==0 && strcmp(lname,e.last_name)==0)
        {
            //case 1: removing a node at the beginning of the list or if list size is 1
            if(phonebook[i]==current)
            {
                NODE* oldhead = phonebook[i];
                phonebook[i] = phonebook[i]->next;
                free(oldhead);
            }
            //case 2: removing node between two nodes or at the end
            else
            {
                previous->next = current->next;
                free(current);
            }

            counter--;
            printf("\n \"ENTRY SUCCESSFULLY REMOVED\"\n");

            pthread_mutex_unlock(&mutex);
            return;
        }
        previous = current;
        current = current->next;
    }

    pthread_mutex_unlock(&mutex);

    printf("\n \"NO SUCH USER\"\n");
    return;
}

int check_duplicate(char fname[], char lname[])
{
    //temporary node and loop to traverse the linked list
    int i;
    for (i = 0; i < 3; i++)
    {
        NODE*current = phonebook[i];
        while(current!=NULL)
        {
            Entry e = current->ent;
            if(strcmp(fname,e.first_name)==0 && strcmp(lname,e.last_name)==0)
                return 1;
            current = current->next;
        }
    }
    return 0;
}


void delete_name()
{
    int howMany = 0;
    //checks if list is empty
    if(phonebook[0] == NULL && phonebook[1] == NULL && phonebook[2] == NULL)
    {
        printf("\n \"PHONEBOOK IS EMPTY\"\n");
        return;
    }

    char fname[50];
    printf ("\nEnter First Name: ");
    scanf("%s",fname);

    //temporary nodes and loop to traverse the linked list
    
    pthread_mutex_lock(&mutex);

    int i;
    for (i = 0; i < 3; i++)
    {
        NODE*current = phonebook[i];
        NODE*previous = phonebook[i];

        while(current!=NULL)
        {
            Entry e = current->ent;
            if(strcmp(fname,e.first_name)==0)
            {
                howMany++;
                //same cases as delete function
                if(phonebook[i]==current)
                {
                    NODE* oldhead = phonebook[i];
                    phonebook[i] = phonebook[i]->next;
                    free(oldhead);
                    //assign current to next node to continue scanning
                    current = phonebook[i];
                }
                else
                {
                    NODE* temp = current;
                    previous->next = current->next;
                    //assign current to next node to continue scanning
                    current = current->next;
                    free(temp);
                }

                counter--;
            }
            else
            {
                previous = current;
                current = current->next;
            } 
        }
    }

    pthread_mutex_unlock(&mutex);

    if(howMany == 1)
        printf("\n \"1 ENTRY SUCCESSFULLY REMOVED\"\n");
    else if(howMany == 0)
        printf("\n \"NO SUCH USER\"\n");
    else
        printf("\n \"%d ENTRIES SUCCESSFULLY REMOVED\"\n",howMany);
    return;
}

void deleteall()
{
    int i;
    for (i = 0; i < 3; i++)
        recursiveDelete(phonebook[i]);
}

void recursiveDelete(NODE*n)
{
    if(n!=NULL)
    {
        if(n->next != NULL)
        recursiveDelete(n->next);
        free(n);
        return;
    }
    
}