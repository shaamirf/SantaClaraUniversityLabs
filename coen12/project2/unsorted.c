/*
 * File:        unsorted.c
 *
 * Author:      Shaamir Faneeband
 * 
 * Date:        4/21/2024
 * 
 * Copyright:	2021, Darren C. Atkinson
 *
 * Description: This file contains the implementation for the 
 *              abstract data type of Sets, given that the set is unsorted.
 *
 *          
 */

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include "set.h"

typedef struct set{
    char** unsortedList;
    int listLength;
    int numOfElements;
} SET;


SET* createSet(int maxElts){
    SET* s = malloc(sizeof(SET));
    s->unsortedList = (char**)malloc(sizeof(char*)*maxElts);  //creates a dynamic array of char pointers
    s->listLength = maxElts;
    s->numOfElements = 0;
    return s;
    //Time Complexity: O(1)
};


int search(SET *sp, char *elt){

    int index = 0;

    while(index < sp->numOfElements)//only searches up to n
    {
        if(strcmp(sp->unsortedList[index],elt)==0)
            return index;
        index++;
    }
    return -1; //-1 index indicates element not found

    //Time Complexity: O(n), n = number of elements
}


void destroySet(SET *sp){
    int start = 0;
    int end = sp->numOfElements - 1;

    //reverse order of allocating memory
    while(start <= end)
    {
        free(sp->unsortedList[start++]);
    }

    free(sp->unsortedList);
    free(sp);

    return;

    //Time Complexity: O(n), n = number of elements
}


int numElements(SET *sp){
    return sp->numOfElements;

    //Time Complexity: O(1) 
}


void addElement(SET * sp, char* elt){

    if(sp->numOfElements >= sp->listLength) 
    {
        // SET is full
        return;
    }

    if(search(sp,elt)!= -1)
    {
        // word already exists
        return;
    }

    sp->unsortedList[sp->numOfElements] = strdup(elt); //add to the end of the SET

    sp->numOfElements++;

    return;

    //Time Complexity: O(n)
}


void removeElement(SET *sp, char *elt){

    int pos = search(sp,elt); 
    if(pos==-1)
    {
        //element not found
        return;
    }

    free(sp->unsortedList[pos]); //free pointer to avoid memory leak

    if(pos < sp->numOfElements-1)  //corner condition for last element, to avoid segmentation fault
    {
        sp->unsortedList[pos] = strdup(sp->unsortedList[sp->numOfElements-1]); //replace value with value from last index
        free(sp->unsortedList[sp->numOfElements-1]);
    }
    
    sp->numOfElements--;

    return;


    //Time Complexity: O(n)
}


char *findElement(SET *sp, char *elt)
{
    int pos = search(sp,elt);
    if(pos==-1)
        return NULL;
    else
        return sp->unsortedList[pos];

    //Time Complexity: O(n)
}


char **getElements(SET *sp)
{
    int index = 0;
    int length = sp->listLength;

    char** arr = (char**)malloc(sizeof(char*)*length);

    while(index < sp->numOfElements)
    {
        arr[index] = strdup(sp->unsortedList[index]);
        index++;
    }

    return arr;

    //Time Complexity: O(n)
}

