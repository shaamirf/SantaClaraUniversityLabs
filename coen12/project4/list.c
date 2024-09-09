/*
 * File:        list.c
 *
 * Author:      Shaamir Faneeband
 * 
 * Date:        5/16/2024
 *
 * Description: This file contains the implementation for the 
 *              abstract data type of Linked Lists.
 *          
 */

# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <assert.h>
# include "set.h"

typedef struct node{
    void* data;
    struct node* prev;
    struct node* next;
}NODE;

typedef struct list{
    int count;
    NODE* head;
    int (*compare)();
}LIST;

void *removeFirst(LIST *lp);

LIST *createList(int (*compare)()){

    LIST* li = (LIST*)malloc(sizeof(LIST));
    assert(li!=NULL);

    li->count = 0;
    li->compare = compare;

    li->head = (NODE*)malloc(sizeof(NODE));
    assert(li->head!=NULL);

    li->head->next = li->head;  //circluar, doubly linked list with dummy node
    li->head->prev = li->head;
    li->head->data = NULL;

    return li;

    //Time Complexity: O(1) 
}

void destroyList(LIST *lp)
{
    assert(lp!=NULL);

    while(lp->head->next != lp->head){   //delete from head
        void*temp = removeFirst(lp);
    }

    free(lp->head);
    free(lp);

    //Time Complexity: O(n)   ,    n = length of linked list
}


int numItems(LIST *lp){
    assert(lp!=NULL);
    return lp->count;

    //Time Complexity: O(1) 
};

void addFirst(LIST *lp, void *item){
    assert(lp!=NULL && item!=NULL);
    
    NODE*t = (NODE*)malloc(sizeof(NODE)); 
    t->data = item;
    t->prev = lp->head;
    t->next = lp->head->next;
    t->next->prev = t;
    lp->head->next = t;

    lp->count++;

    //Time Complexity: O(1) 
}

void addLast(LIST *lp, void *item){
    assert(lp!=NULL && item!=NULL);
    NODE*t = (NODE*)malloc(sizeof(NODE));
    t->data = item;
    t->prev = lp->head->prev;
    t->next = lp->head;
    t->prev->next = t;
    lp->head->prev = t;

    lp->count++;

    //Time Complexity: O(1) 
}

void *removeFirst(LIST *lp){
    assert(lp!=NULL);
    if(lp->head->next == lp->head) return NULL;

    NODE*t = lp->head->next;
    void*v = t->data;

    t->next->prev = lp->head;
    t->prev->next = t->next;

    free(t);

    lp->count--;

    return v;

    //Time Complexity: O(1) 
}

void *removeLast(LIST *lp){
    assert(lp!=NULL);
    if(lp->head->next == lp->head) return NULL;

    NODE*t = lp->head->prev;
    void*v = t->data;

    t->prev->next = lp->head;
    t->next->prev = t->prev;

    free(t);

    lp->count--;

    return v;

    //Time Complexity: O(1) 
}

void *getFirst(LIST *lp){
    assert(lp!=NULL);
    return lp->head->next->data;

    //Time Complexity: O(1) 
}

void *getLast(LIST *lp){
    assert(lp!=NULL);
    return lp->head->prev->data;

    //Time Complexity: O(1) 
}

void removeItem(LIST *lp, void *item){
    assert(lp!=NULL && lp->compare!=NULL && item!=NULL);

    NODE*t = lp->head->next;

    while(t!=lp->head)
    {
        if(lp->compare(t->data,item) == 0)
        {
            t->next->prev = t->prev;
            t->prev->next = t->next;
            free(t);
            lp->count--;
            return;
        }
        t = t->next;
    }
    return;

    //Time Complexity: O(n)   ,    n = length of linked list
}

void *findItem(LIST *lp, void *item){
    assert(lp!=NULL && lp->compare!=NULL && item!=NULL);

    NODE*t = lp->head->next;

    while(t!=lp->head)
    {
        if(lp->compare(t->data,item) == 0)  return t->data;
        t = t->next;
    }

    return NULL;

    //Time Complexity: O(n)   ,    n = length of linked list
}

void *getItems(LIST *lp){
    assert(lp!=NULL);
    void**arr = malloc(sizeof(void*)*lp->count);
    int index = 0;

    NODE*t = lp->head->next;
    while(t!=lp->head)
    {
        arr[index++] = t->data;
        t = t->next;
    }
    return arr;

    //Time Complexity: O(n)   ,    n = length of linked list
}