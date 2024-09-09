#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lab8.h"

void read_from_file(char file_name[])
{
    FILE*infp = fopen(file_name,"r");
    Entry e;
    if(infp!=NULL)
    {
        while(fscanf(infp,"%s\t%s\t%s\t%d\t",e.first_name,e.last_name,e.phone_number,&e.flag) != EOF )
        {
            if(e.flag==0)
            {
                fscanf(infp,"%d\t%d", &e.info.bday[0],&e.info.bday[1]);
            }
            else if (e.flag==1)
            {
                fscanf(infp,"%s",e.info.ophone);
            }

            insert(e);
        }
        fclose(infp);
    }
    return;

}
void save_to_file(char file_name[])
{
    FILE*outfp = fopen(file_name,"w");

    int i;
    for (i = 0; i < 3; i++)
    {
        NODE*current = phonebook[i];
        while(current!=NULL)
        {
            Entry e = current->ent;
            fprintf(outfp, "%s\t%s\t%s\t%d\t",e.first_name,e.last_name,e.phone_number,e.flag);
            if(e.flag==0)
                {
                    fprintf(outfp, "%d\t%d\n", e.info.bday[0],e.info.bday[1]);
                }
                else if (e.flag==1)
                {
                    fprintf(outfp, "%s\n",e.info.ophone);
                }
                else if(e.flag==2)
                {
                    fprintf(outfp,"\n");
                }
            current = current->next;
        }
    }

    fclose(outfp);
    return;
}