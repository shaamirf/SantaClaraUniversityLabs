/*
 * File:        set.c
 *
 * Author:      Shaamir Faneeband
 * 
 * Date:        5/16/2024
 *
 * Description: This file contains the implementation for the 
 *              abstract data type of Sets using a hash table with chaining.
 *          
 */

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <assert.h>
# include "set.h"
# include "list.h"
# include "list.c"

typedef struct set{
    int count;
    int length;
    LIST** lists;
    int (*compare)();
    unsigned (*hash)();
}SET;


SET *createSet(int maxElts, int (*compare)(),  unsigned (*hash)())
{
    SET* s = malloc(sizeof(SET));
    assert(s != NULL);
    s->lists= malloc(sizeof(LIST*)*maxElts/20);  //creates a dynamic array of void pointers
    assert(s->lists != NULL);

    s->length = maxElts/20;
    s->count = 0;

    s->compare = compare;
    s->hash = hash;

    int i;
    for(i = 0;i<s->length;i++)
    {
        s->lists[i] = createList(s->compare);
        assert(s->lists[i] != NULL);
    }

    return s;
    //Time Complexity: O(m), m = size of hash table. 
    //O(m) to initialize all spaces
}

void destroySet(SET *sp)
{
    assert(sp != NULL);

    int start = 0;
    int end = sp->length - 1;

    //reverse order of allocating memory
    
    while(start <= end)
    {
        destroyList(sp->lists[start]);
        start++;
    }

    free(sp->lists);
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

void addElement(SET *sp, void *elt)
{
    assert(sp != NULL & elt != NULL);
    unsigned index = (*sp->hash)(elt)%sp->length;

    if(findItem(sp->lists[index],elt) != NULL)   //element already exiss
        return;

    addFirst(sp->lists[index],elt);
    sp->count++;

    return;

    //Time Complexity: O(1) - ideal   ,   O(n) - worst case,    n = length of linked list
}

void removeElement(SET *sp, void *elt)
{
    assert(sp != NULL & elt != NULL);
    unsigned index = (*sp->hash)(elt)%sp->length;

    if(findItem(sp->lists[index],elt) == NULL)   //element does not exist
        return;

    removeItem(sp->lists[index],elt);
    sp->count--;

    return;
    //Time Complexity: O(1) - ideal   ,   O(n) - worst case,     n = length of linked list
}

void *findElement(SET *sp, void *elt)
{
    assert(sp != NULL && elt != NULL);
    unsigned index = (*sp->hash)(elt)%sp->length;

    assert(sp->lists[index] != NULL);
    return findItem(sp->lists[index],elt);

    //Time Complexity: O(1) - ideal   ,   O(n) - worst case,     n = length of linked list
}

void *getElements(SET *sp)
{
    assert(sp != NULL);
    void**twoDimArray = malloc(sizeof(void*)*sp->count);
    int index;

    int i = 0;
    int j;

    for(j=0;j<sp->length;j++)
    {
        void**elts = getItems(sp->lists[j]);
        memcpy(&twoDimArray[i],elts,sizeof(void*)*numItems(sp->lists[j]));
        i+= numItems(sp->lists[j]);
    }

    return twoDimArray;

    //Time Complexity: O(m * n)  ,   m = size of hash table,    n = length of linked list
}