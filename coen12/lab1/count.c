/*
File Name: count.c
Author: Shaamir Faneeband
Date: 04/03/2024
Program Desc: Reads a text file and counts number of words 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

# define MAX_WORD_LENGTH 30 //maximum word length in input file

int main (int argc, char *argv[])
{
    int count;    //counts number of words
    char word[MAX_WORD_LENGTH];    //stores each scanned word temporarily in this variable
    
    //checks if text file is included in command line
    if(argc < 2)   
    {
        printf("missing arguments\n");
        return 1;
    }
    else
    {
        FILE*infp = fopen(argv[1],"r");     //opens file for reading
        if(infp!=NULL)
        {
            while(fscanf(infp,"%s",word)!=EOF)    //while scanner 
                count++;     //increase word count
            fclose(infp);
        }
        else
        {
            fprintf(stderr,"file does not exist");
            return 1;
        }
    }

    printf("%d",count);
    return 0;
}