//
// Created by maria on 04/01/2019.
//

#ifndef PROJETOPARTE2_MERGESORT_H
#define PROJETOPARTE2_MERGESORT_H
#include <stdio.h>
#include <stdlib.h>
#include <windef.h>

#ifndef MERGESORTLINKEDLIST_MERGESORTLINKEDLIST_H
#define MERGESORTLINKEDLIST_MERGESORTLINKEDLIST_H

/* Link list node */
typedef struct list{
    struct Node * first;
    int nchaves;
}LIST;

struct Node
{
    char * data;
    int id;
    struct Node* next;
};

/* function prototypes */
struct Node* Merge(struct Node *a, struct Node *b, int flag);
void FrontBackSplit(struct Node* source,
                    struct Node** frontRef, struct Node** backRef);
void printList(struct Node *node);
void MergeSort(struct Node** list, int flag);
void addElement(struct Node** list, char * new_data, int key);
#endif //MERGESORTLINKEDLIST_MERGESORTLINKEDLIST_H
#endif //PROJETOPARTE2_MERGESORT_H
