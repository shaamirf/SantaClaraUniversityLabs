#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lab9.h"
#include <pthread.h>
#include <unistd.h>

void read_from_binary_file(char file_name[])
{
    FILE*infpb = fopen(file_name,"rb");

    if(infpb!=NULL)
    {
        Entry e;

        pthread_mutex_lock(&mutex);

        while(fread(&e,sizeof(Entry),1,infpb) == 1)
        {
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

        pthread_mutex_unlock(&mutex);

        fclose(infpb);
    }

    return;
}

void save_to_binary_file(char file_name[])
{
    FILE*outfpb = fopen(file_name,"wb");

    pthread_mutex_lock(&mutex);

    int i;
    for (i = 0; i < 3; i++)
    {
        NODE*current = phonebook[i];
        while(current!=NULL)
        {
            Entry e = current->ent;
            fwrite(&e,sizeof(Entry),1,outfpb);
            current = current->next;
        }
    }

    pthread_mutex_unlock(&mutex);

    fclose(outfpb);
    return;
}

void* autosave(void* file)
{
    while(1)
    {
        sleep(15);
        save_to_binary_file((char*)file);
    }
    return NULL;
}