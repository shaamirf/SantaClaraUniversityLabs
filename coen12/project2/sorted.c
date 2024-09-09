/*
 * File:        sorted.c
 *
 * Author:      Shaamir Faneeband
 * 
 * Date:        4/21/2024
 * 
 * Copyright:	2021, Darren C. Atkinson
 *
 * Description: This file contains the implementation for the 
 *              abstract data type of Sets, given that the set is sorted.
 *          
 */

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include "set.h"

typedef struct set{
    char** sortedList;
    int listLength;
    int numOfElements;
} SET;


SET* createSet(int maxElts){
    SET* s = malloc(sizeof(SET));
    s->sortedList = (char**)malloc(sizeof(char*)*maxElts);
    s->listLength = maxElts;
    s->numOfElements = 0;
    return s;

    //Time Complexity: O(1)
};


static int bnrysearch(SET *sp, char *elt, bool *found){

    int low = 0;
    int high = sp->numOfElements-1;
    int mid = 0;

    while(low<=high)
    {
        mid = (low+high)/2;
        if(strcmp(sp->sortedList[mid],elt)==0)
        {
            *found = true;
            return mid;
        }
        if(strcmp(sp->sortedList[mid],elt)<0)
        {
            low = mid+1;
        }
        else high = mid-1;
    }
    *found = false;
    return low;

    //Time Complexity: O(log n), n = number of elements
}


void destroySet(SET *sp){
    int start = 0;
    int end = sp->numOfElements - 1;

    //same as unsorted.c
    while(start <= end)
    {
        free(sp->sortedList[start++]);
    }

    free(sp->sortedList);
    free(sp);

    return;

    //Time Complexity: O(n)
}


int numElements(SET *sp){
    return sp->numOfElements;

    //Time Complexity: O(1)
};

void addElement(SET * sp, char* elt){

    if(sp->numOfElements >= sp->listLength)
    {
        //Set is full
        return;
    }

    bool found = false;
    int pos = bnrysearch(sp,elt,&found);

    if(found)
    {
        //Word already exists
        return;
    }

    int index = sp->numOfElements;

    while(index > pos)
    {
        sp->sortedList[index] = sp->sortedList[index-1];
        index--;
    }

    sp->sortedList[pos] = strdup(elt);

    sp->numOfElements++;

    return;

    //Time Complexity: O(n) + O(log n)  =  O(n)
}


void removeElement(SET *sp, char *elt){
    bool found = false;
    int pos = bnrysearch(sp,elt,&found);
    int end = sp->numOfElements - 1;

    if(found==false)
    {
        //Word not found
        return;
    }

    free(sp->sortedList[pos]); //free this pointer since this word is no longer needed

    while(pos < end)
    {
        //logic: pointers will now point to the word referenced by the next pointer
        sp->sortedList[pos] = sp->sortedList[pos+1];
        pos++;
    }

    sp->sortedList[end] = NULL; //set final pointer to NULL, DO NOT free since previous pointer is now also pointing to the same word

    sp->numOfElements--;

    return;

    //Time Complexity: O(n) + O(log n)  =  O(n)
}

char *findElement(SET *sp, char *elt)
{
    bool found = false;
    int pos = bnrysearch(sp,elt,&found);
    if(!found)
        return NULL;
    else
        return sp->sortedList[pos];

    //Time Complexity: O(log n)
}

char **getElements(SET *sp)
{
    int index = 0;
    int length = sp->listLength;

    char** arr = (char**)malloc(sizeof(char*)*length);

    while(index < sp->numOfElements)
    {
        arr[index] = strdup(sp->sortedList[index]);
        index++;
    }

    return arr;

    //Time Complexity: O(n)
}