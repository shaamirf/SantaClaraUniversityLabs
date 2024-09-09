/*
 * File:	pack.h
 *
 * Copyright:	2021, Darren C. Atkinson
 */

# ifndef PACK_H
# define PACK_H

typedef struct node {
    struct node *parent;
    int count;
}NODE;

void pack(char *infile, char *outfile, struct node *leaves[257]);

# endif /* PACK_H */
