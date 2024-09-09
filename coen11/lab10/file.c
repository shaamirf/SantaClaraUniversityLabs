#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lab10.h"
#include <pthread.h>
#include <unistd.h>

void read_from_file(char file_name[], int key)
{
    FILE*infp = fopen(file_name,"r");
    Entry e;
    if(infp!=NULL)
    {
        char str[150];
        while(fgets(str,sizeof(str),infp)!=NULL)
        //while(fscanf(infp,"%s\t%s\t%s\t%d\t",e.first_name,e.last_name,e.phone_number,&e.flag) != EOF )
        {
            int i;
            for(i=0;i<strlen(str);i++)
            {
                str[i] = str[i] ^ key;
            }

            strcpy(e.first_name,strtok(str,"\t"));

            strcpy(e.last_name,strtok(NULL,"\t"));
            
            strcpy(e.phone_number,strtok(NULL,"\t"));

            e.flag = atoi(strtok(NULL,"\t"));

            if(e.flag==0)
            {
                e.info.bday[0] = atoi(strtok(NULL,"\t"));
                e.info.bday[1] = atoi(strtok(NULL,"\t"));
            }
            else if (e.flag==1)
            {
                strcpy(e.info.ophone,strtok(NULL,"\t"));
            }

            insert(e);
        }
        fclose(infp);
    }
    return;

}
void save_to_file(char file_name[], int key)
{
    FILE*outfp = fopen(file_name,"w");

    int i;
    for (i = 0; i < 3; i++)
    {
        NODE*current = phonebook[i];
        while(current!=NULL)
        {
            char str[150];
            Entry e = current->ent;

            if(e.flag==0)
            {
                sprintf(str, "%s\t%s\t%s\t%d\t%d\t%d",e.first_name,e.last_name,e.phone_number,e.flag,e.info.bday[0],e.info.bday[1]);
            }
            else if (e.flag==1)
            {
                sprintf(str, "%s\t%s\t%s\t%d\t%s",e.first_name,e.last_name,e.phone_number,e.flag,e.info.ophone);
            }
            else if(e.flag==2)
            {
                sprintf(str, "%s\t%s\t%s\t%d",e.first_name,e.last_name,e.phone_number,e.flag);
            }
            int i;
            for(i=0;i<strlen(str);i++)
            {
                str[i] = str[i] ^ key;
            }
            fprintf(outfp,"%s\n",str);


            current = current->next;
        }
    }

    fclose(outfp);
    return;
}