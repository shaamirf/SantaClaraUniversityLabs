/*
 * File:        pqueue.c
 *
 * Author:      Shaamir Faneeband
 * 
 * Date:        5/31/2024
 *
 * Description: This file contains the implementation for the 
 *              abstract data type of a priority queue using a min-heap.
 *          
 */

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <assert.h>
# include "pqueue.h"

typedef struct pqueue{
    int count; // number of entries in array
    int length; // length of allocated array 
    void **data; // allocated array of entries 
    int (*compare)(); // comparison function
}PQ;

PQ *createQueue(int (*compare)()){
    PQ*pq = (PQ*)malloc(sizeof(PQ));
    assert(pq!=NULL);

    pq->count = 0;
    pq->length = 10;
    pq->data = (void**)malloc(sizeof(void*) * pq->length);
    assert(pq->data!=NULL);

    pq->compare = compare;

    return pq;
    //Time Complexity: O(1);
}

void destroyQueue(PQ *pq){
    assert(pq != NULL);

    free(pq->data);
    free(pq);

    return;
    //Time Complexity: O(1);
}  

int numEntries(PQ *pq)
{
    assert(pq != NULL);
    return pq->count;
    //Time Complexity: O(1);
}

void addEntry(PQ *pq, void *entry)
{
    assert(pq != NULL && entry != NULL);
    if(pq->count>=pq->length)
    {
        pq->length *= 2;
        void**newData = realloc(pq->data,sizeof(void*)*pq->length);
        assert(newData != NULL);
        pq->data = newData;
    }

    pq->data[pq->count] = entry;
    pq->count++;

    void**arr = pq->data;
    int i = pq->count - 1;
    void*temp = arr[i];

    while(i>0 && pq->compare(temp,arr[(i-1)/2]) < 0)
    {
        arr[i] = arr[(i-1)/2];
        i = (i-1)/2;
    }

    arr[i] = temp;

    return;
    //Time Complexity: O(n) if realloc is called, otherwise O(log n);
}

void *removeEntry(PQ *pq)
{
    assert(pq != NULL);

    void**arr = pq->data;
    void*temp = arr[0];

    arr[0] = arr[pq->count-1];
    arr[pq->count-1] = temp;
    pq->count--;



    int n = pq->count;

    int i = 0;
    int j = i*2 + 1;

    while(j < n)
    {
        if(j + 1 < n && pq->compare(arr[j+1],arr[j])<0)
            j++;
        if(pq->compare(arr[i],arr[j])>0)
        {
            void*temp2 = arr[i];
            arr[i] = arr[j];
            arr[j] = temp2;

            i = j;
            j = i*2 + 1;
        }
        else
            break;
    }

    return arr[n];
    //Time Complexity: O(log n);
}