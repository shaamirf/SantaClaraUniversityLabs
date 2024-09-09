/*
 * File:        list.c
 *
 * Author:      Shaamir Faneeband
 * 
 * Date:        6/1/2024
 *
 * Description: This file contains the implementation for the 
 *              abstract data type of a linked list of circular queues.
 *          
 */

# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <assert.h>
# include "list.h"

typedef struct queue{
    void** data;           //array of void pointers
    int count;
    int length;
    int first;             //circular queue
    struct queue* prev;    
    struct queue* next;
}QUEUE;

typedef struct list{
    QUEUE* head;           //using head and tail pointer
    QUEUE* tail;
    int totalCount;        
}LIST;

static bool isFull(QUEUE* q)      //checks to see if the current array is full
{
    if(q->count >= q->length)
        return true;
    return false;

    //Time Complexity: O(1);
}

static void enqEnd(QUEUE *q, void*v){              //adds to end of circular array 
    assert(q->count < q->length);                  
    q->data[(q->count+q->first) % q->length] = v; 
    q->count++;
    //Time Complexity: O(1);
}

static void enqFront(QUEUE *q, void*v){            //adds to beginning of circular array
    assert(q->count < q->length);
    q->first = (q->first + q->length - 1) % q->length;
    q->data[q->first] = v; 
    q->count++;
    //Time Complexity: O(1);
}

static void* deqFront(QUEUE *q){                   //removes from beginning of circular array
    assert(q->count > 0);
    void*v = q->data[q->first];
    q->first = (q->first+1) % q->length;
    q->count--;
    return v;
    //Time Complexity: O(1);
}

static void* deqEnd(QUEUE *q){                     //removes from end of circular array
    assert(q->count > 0);
    void*v = q->data[(q->count + q->first - 1) % q->length];
    q->count--;
    return v;
    //Time Complexity: O(1);
}

static QUEUE* createQueue(int len)
{
    QUEUE*qp = (QUEUE*)malloc(sizeof(QUEUE));
    qp->count = 0;
    qp->length = len;
    qp->data = (void**)malloc(sizeof(void*) * qp->length);
    qp->first = 0;
    qp->next = NULL;
    qp->prev = NULL;

    return qp;
    //Time Complexity: O(1);
}

LIST *createList(){

    LIST* li = (LIST*)malloc(sizeof(LIST));
    assert(li!=NULL);

    li->head = NULL;
    li->tail = NULL;
    li->totalCount = 0;

    return li;

    //Time Complexity: O(1); 
}

void destroyList(LIST *lp)
{
    assert(lp!=NULL);

    while(lp->head != NULL){       //delete from head
        QUEUE* temp = lp->head;
        lp->head = lp->head->next;

        free(temp->data);
        free(temp);
    }

    free(lp);

    //Time Complexity: O(n)   ,    n = number of queues
}


int numItems(LIST *lp){
    assert(lp!=NULL);
    return lp->totalCount;

    //Time Complexity: O(1) 
};

void addFirst(LIST *lp, void *item){
    assert(lp!=NULL && item!=NULL);

    if(lp->head == NULL)                //when list is empty
    {
        lp->head = createQueue(10);
        lp->tail = lp->head;
    }

    if(isFull(lp->head))                //when queue is full
    {
        QUEUE*q = createQueue(lp->head->length * 2);
        q->next = lp->head;
        lp->head->prev = q;
        lp->head = q;
    }

    enqFront(lp->head,item);            //add to beginning
    lp->totalCount++;

    //Time Complexity: O(1) 
}

void addLast(LIST *lp, void *item){
    assert(lp!=NULL && item!=NULL);
    if(lp->tail == NULL)                //when queue is empty
    {
        lp->tail = createQueue(10);
        lp->head = lp->tail;
    }

    if(isFull(lp->tail))                //when queue is full
    {
        QUEUE*q = createQueue(lp->tail->length * 2);
        q->prev = lp->tail;
        lp->tail->next = q;
        lp->tail = q;
    }

    enqEnd(lp->tail,item);              //add to end
    lp->totalCount++;

    //Time Complexity: O(1) 
}

void *removeFirst(LIST *lp){
    assert(lp!=NULL);
    if(lp->head==NULL)                 //when list is empty
        return NULL;

    void*v = deqFront(lp->head);       //remove from beginning

    if(lp->head->count == 0)           //update pointers and deallocate when queue becomes empty
    {
        QUEUE*temp = lp->head;
        lp->head = lp->head->next;
        if(lp->head != NULL)
            lp->head->prev = NULL;
        else
            lp->tail = NULL;
        free(temp->data);
        free(temp);
    }
    
    lp->totalCount--;
    return v;

    //Time Complexity: O(1) 
}

void *removeLast(LIST *lp){
    assert(lp!=NULL);
    if(lp->tail==NULL)                 //when list is empty
        return NULL;

    void*v = deqEnd(lp->tail);         //remove from end
    
    if(lp->tail->count == 0)           //update pointers and deallocate when queue becomes empty
    {
        QUEUE*temp = lp->tail;
        lp->tail = lp->tail->prev;
        if(lp->tail != NULL)
            lp->tail->next = NULL;
        else
            lp->head = NULL;
        free(temp->data);
        free(temp);
        //lp->tail->next = NULL;
    }
    
    lp->totalCount--;
    return v;

    //Time Complexity: O(1) 
}

void *getFirst(LIST *lp){
    assert(lp!=NULL && lp->head != NULL);
    return lp->head->data[lp->head->first];

    //Time Complexity: O(1) 
}

void *getLast(LIST *lp){
    assert(lp!=NULL && lp->tail != NULL);
    return lp->tail->data[ (lp->tail->first + lp->tail->count - 1) % lp->tail->length ];  //use % to adjust for circular queue index

    //Time Complexity: O(1) 
}

void *getItem(LIST *lp, int index){
    assert(lp!=NULL && index < lp->totalCount);

    QUEUE*q = lp->head;
    while(index >= q->count)
    {
        index -= q->count;
        q = q->next;
    }

    return q->data[(q->first + index) % q->length];         //use % to adjust for circular queue index


    //Time Complexity: O(n)   ,    n = number of queues
}

void setItem(LIST *lp, int index, void *item){
    assert(lp!=NULL && index < lp->totalCount);

    QUEUE*q = lp->head;
    while(index >= q->count)
    {
        index -= q->count;
        q = q->next;
    }

    q->data[(q->first + index) % q->length] = item;        //use % to adjust for circular queue index


    //Time Complexity: O(n)   ,   n = number of queues
}

