/*
Dakota Goldstein Lab 5
huffman.c
CSEN 12
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "pqueue.h"
//#include "pqueue.c"
#include "pack.h"
//#include "pack.c"
#include <ctype.h>
typedef struct node NODE;

// Counts how many of each character
void countLetters(FILE*fp, int counts[257]) 
{
    int s;
    while ((s = getc(fp)) != EOF) counts[s]++;
    fclose(fp);
}
//Function counts the distance from leaf to the root
//Big-O: O(h)/O(logn)
int height(NODE *leaf)
{
    assert(leaf != NULL);
	int count = 0;
    while(leaf->parent != NULL)
    {
        leaf = leaf->parent;
        count++;
    }
   	return count;
}

//Function compartes the data in two nodes
//Big-O: O(1)
int compare(NODE *n1, NODE *n2)
{
    assert(n1 != NULL && n2 != NULL);
	return (n1->count < n2->count) ? -1 : (n1->count > n2->count) ? 1 : 0;


}
NODE *mkNode(int count, NODE *left, NODE *right){
    NODE *np = (NODE*)malloc(sizeof(NODE));
    if (np == NULL) 
    {
        fprintf(stderr, "Memory allocation error\n");
        exit(1);
    }
    assert(np!=NULL);
    np->count = count;
    np->parent= NULL;
    if(left) left->parent=np;
    if(right)right->parent=np;
    return np;

    
}


int main(int argc, char *argv[])
{
	//Opens and reads each char in file assigning use numbers to array
    if (argc != 3) {
        fprintf(stderr, "usage: %s file\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) 
    {
        fprintf(stderr, "Error opening file %s\n", argv[1]);
        exit(1);
    }
    int counts[257];
    for(int h = 0; h < 257; h++) counts[h] = 0;
    countLetters(fp, counts);
    printf("1\n");
    //Creates the priority queue
    PQ *pq = createQueue(compare);
    NODE *leaves[257] = {NULL};
    int i;
    for(i = 0; i < 257; i++) leaves[i] = NULL;
    for(i = 0; i < 257; i++)
    {
        if(counts[i] > 0)
        {
            leaves[i] = mkNode(counts[i],NULL,NULL);
            addEntry(pq,leaves[i]);
        }
    }

    //Add zeroCount Node to last slot
    printf("check1\n");
    NODE *zero = malloc(sizeof(NODE));
    assert(zero != NULL);
    zero->count = 0;
    zero->parent = NULL;
    addEntry(pq, zero);
    leaves[256] = zero;
    printf("check2\n");
    printf("%d\n",numEntries(pq));

    //Combines lowest priority trees to one until huffman tree is left
    while(numEntries(pq) > 1)
    {
        printf("%d",numEntries(pq));
		NODE *one = removeEntry(pq);
		NODE *two = removeEntry(pq);
		NODE *three = mkNode(one->count + two->count,one,two);
        assert(one != NULL && two != NULL && three != NULL);
		addEntry(pq, three);
    }

    printf("check 5\n");
    	//Prints out vaild nodes
    for(i = 0; i < 257; i++)
    {
        if(leaves[i] != NULL)
        {
            int numHops = height(leaves[i]);
            if(isprint(i))
            {
                printf("%c: %d x %d bits = %d bits\n", i, counts[i], numHops, numHops*counts[i]);
            }
            else
            {
                printf("%03o: %d x %d bits = %d bits\n", i, counts[i], numHops, numHops*counts[i]);
            }
        	}
    	}

    	//Packs huffman tree 
    	pack(argv[1], argv[2], leaves);
	return 0;
}