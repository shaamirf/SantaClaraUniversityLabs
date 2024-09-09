/*
 * File:        huffman.c
 *
 * Author:      Shaamir Faneeband
 * 
 * Date:        5/31/2024
 *
 * Description: This file contains a driver program that compresses a text file using huffman coding.
 *          
 */

# include <stdio.h>
# include <ctype.h>
# include <errno.h>
# include <stdlib.h>
# include <sys/stat.h>
# include "pack.h"
# include "pqueue.h"
# include <assert.h>

NODE* mknode(int count, NODE*left_node, NODE* right_node)
{
    NODE* newNode = (NODE*)malloc(sizeof(NODE));      // Malloc for a new_node pointer
    assert(newNode!=NULL);
    newNode->count =count;                            // Sum of the two children
    newNode->parent=NULL;                             // new node has no parent yet

    if(left_node != NULL)
        left_node->parent = newNode;
    if(right_node != NULL)
        right_node->parent = newNode;
    return newNode;
    //Time Complexity: O(1);
}

static int cmp(NODE*t1, NODE*t2)
{
    return (t1->count < t2->count) ? -1 : (t1->count > t2->count);    //compares count of nodes
    //Time Complexity: O(1);
}

int* makeIntArray(char* inputFile){

    int* intArray = (int*)malloc(sizeof(int)*257);
    assert(intArray!=NULL);

    int i,index;
    for(i=0;i<257;i++)
        intArray[i] = 0;                 //initialize array of ints with zeros
    
    FILE*fp = fopen(inputFile, "r");
    while((index=getc(fp)) != EOF)
    {
        intArray[index]++;               //stores count of each character's occurrence
    }

    fclose(fp);
    return intArray;
    //Time Complexity: O(c), c = number of characters from text file;
}

NODE** makeLeafNodeArray(int*intArray, PQ*pq){

    NODE**leafNodeArray = (NODE**)malloc(sizeof(NODE*)*257);
    assert(leafNodeArray!=NULL);

    int i,index;
    for(i=0;i<257;i++)
    {
        if(intArray[i] > 0)
        {
            leafNodeArray[i] = mknode(intArray[i],NULL,NULL);      //create leaf nodes with no children, assign to array of nodes and add to queue
            addEntry(pq,leafNodeArray[i]);
        }
        else
            leafNodeArray[i] = NULL;                               //set remaining spots to NULL
    }

    leafNodeArray[256] = mknode(intArray[256],NULL,NULL);          //create node for EOF and add to queue
    addEntry(pq,leafNodeArray[256]);

    return leafNodeArray;
    //Time Complexity: O(1);   always 257 iterations
}

int depth(NODE*n){
    if(n->parent == NULL)              //uses recursion to calculate number of bytes needed
        return 0;
    return 1 + depth(n->parent);
    //Time Complexity: O(h), h = height of binary tree;
}

int main(int argc, char *argv[]){
    if (argc != 3) {
        fprintf(stderr, "usage: %s file\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int*intArray = makeIntArray(argv[1]);
    PQ* pq = createQueue(cmp);
    NODE**leafNodeArray = makeLeafNodeArray(intArray, pq);

    while(numEntries(pq)>1)            //main huffman coding process, creates a binary tree
    {
        NODE*l = removeEntry(pq);
        NODE*r = removeEntry(pq);
        NODE*new_node = mknode(l->count + r->count,l,r);
        addEntry(pq,new_node);
    }   //Time Complexity: O(n log n);

    int c;
    for(c=0;c<257;c++)                 //prints out a list of characters and number many bytes needed for each
    {
        if(leafNodeArray[c] != NULL)
        {
            if(!isprint(c))
                printf("%03o: ",c);
            else
                printf("%c: ",c);
            int d = depth(leafNodeArray[c]);
            printf("%d x %d bits = %d bits\n",intArray[c],d,intArray[c]*d);
        }
    } //Time Complexity: O(1);    always 257 iterations

    pack(argv[1],argv[2],leafNodeArray);     //calculates total bytes needed
}