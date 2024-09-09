#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lab7.h"

void read_from_file()
{
    FILE*infp = fopen("output.txt","r");
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
void save_to_file()
{
    FILE*outfp = fopen("output.txt","w");

    NODE*current = head;
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

    fclose(outfp);
    return;
}