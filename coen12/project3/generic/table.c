/*
 * File:        table.c
 *
 * Author:      Shaamir Faneeband
 * 
 * Date:        4/24/2024
 * 
 * Copyright:	2021, Darren C. Atkinson
 *
 * Description: This file contains the implementation for the 
 *              abstract data type of Sets using a hash table.
 *          
 */

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <assert.h>
# include "set.h"

typedef struct set{
    int count;
    int length;
    void**data;
    char*flag;
    int (*compare)();
    unsigned (*hash)();
}SET;


SET *createSet(int maxElts, int (*compare)(),  unsigned (*hash)())
{
    SET* s = malloc(sizeof(SET));
    assert(s != NULL);
    s->data= (void**)malloc(sizeof(char*)*maxElts);  //creates a dynamic array of void pointers
    assert(s->data != NULL);
    s->flag= (char*)malloc(sizeof(char)*maxElts); //parallel array of flags
    assert(s->flag != NULL);
    int i;
        for(i = 0 ; i<maxElts ; i++)
            s->flag[i] = 'E';
    s->length = maxElts;
    s->count = 0;

    s->compare = compare;
    s->hash = hash;

    return s;
    //Time Complexity: O(1)
}

void destroySet(SET *sp)
{
    assert(sp != NULL);

    int start = 0;
    int end = sp->length - 1;

    //reverse order of allocating memory
    
    while(start <= end)
    {
        if(sp->flag[start]=='F')
            (sp->data[start]) = NULL;
        start++;
    }

    free(sp->data);
    free(sp->flag);
    free(sp);

    return;

    //Time Complexity: O(m), m = size of hash table
}

int numElements(SET *sp)
{
    assert(sp != NULL);
    return sp->count;
    //Time Complexity: O(1) 
}

unsigned search(SET *sp, void *elt, bool* found)
{
    assert(sp != NULL && elt != NULL && found != NULL);
    unsigned index = (*sp->hash)(elt)%sp->length;


    // this will determine whether to insert in a new empty slot
    // variable will hold the index of the most recent "deleted" slot that the function comes across
    unsigned deletedSpot = -1; //-1 to indicate no previously "deleted" slots

    int steps = 0;

    while(steps < sp->length)//in the event that there is no empty spot, circle back to starting position and end
    {
        //search ends at empty spot
        if(sp->flag[index] == 'E')
        {
            *found = false;
            if(deletedSpot == -1)
                return index; //if no deleted slots found then return index of empty slot
            return deletedSpot;
        }
        else if(sp->flag[index] == 'D')
        {
            deletedSpot = index; //saves index of deleted element
        }
        else if(sp->flag[index] == 'F' && (*sp->compare)(sp->data[index],elt) == 0)
        {
            //returns index for removing element OR indicates that element already exists
            *found = true;
            return index;
        }
        steps++;
        index = (index + 1) % sp->length;
    }
    *found = false;
    return deletedSpot;
    //Time Complexity: O(1) - ideal   ,   O(n) - worst case,  n = number of strings

}

void addElement(SET *sp, void *elt)
{
    assert(sp != NULL & elt != NULL);
    bool found = false;
    int index = search(sp,elt,&found);

    if(found) //element already exists
    {
        return;
    }

    sp->data[index] = elt;
    sp->flag[index] = 'F'; //update flag to "filled"
    sp->count++;

    return;
    //Time Complexity: O(1) - ideal   ,   O(n) - worst case

}
void removeElement(SET *sp, void *elt)
{
    assert(sp != NULL & elt != NULL);
    bool found = false;
    int index = search(sp,elt,&found);

    if(!found) //element not found, wrong input
    {
        return;
    }

    sp->data[index] = NULL;
    sp->flag[index] = 'D'; //update flag to "deleted"
    sp->count--;

    return;
    //Time Complexity: O(1) - ideal   ,   O(n) - worst case
}

void *findElement(SET *sp, void *elt)
{
    assert(sp != NULL && elt != NULL);
    bool found = false;
    unsigned index = search(sp,elt,&found);
    if(!found)
        return NULL;
    else
        return sp->data[index];
    //Time Complexity: O(1) - ideal   ,   O(n) - worst case
}

void **getElements(SET *sp)
{
    assert(sp != NULL);

    void**elts = (void**)malloc(sizeof(void*)*sp->count);
    int i = 0;
    int j = 0;

    //no blank spaces in new array, size of elts = count of sp->data
    assert(elts != NULL);
    while(i < sp->length)
    {
        if(sp->flag[i]=='F')
        {
            elts[j++] = sp->data[i];
        }
        i++;
    }
    return elts;
    //Time Complexity: O(m), m = size of hash table
}