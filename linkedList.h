#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node_data
{
    char data[100];
    struct node_data *next;
};

typedef struct node_data Node;


typedef struct
{
    Node *head;
    int length;
} LinkedList;


LinkedList *createList();

Node *createNode(char *data);

void insert(LinkedList *list, char *data);
#endif