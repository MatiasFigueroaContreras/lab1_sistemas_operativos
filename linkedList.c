#include "linkedList.h"

LinkedList *createList()
{
    LinkedList *list = malloc(sizeof(LinkedList));
    list->length = 0;
    list->head = NULL;
    return list;
}

Node *createNode(char *data)
{
    Node *new_node = malloc(sizeof(Node));
    strcpy(new_node->data, data);
    new_node->next = NULL;
    return new_node;
}

void insert(LinkedList *list, char *data)
{
    Node *new_node = createNode(data);
    Node *temp = list->head;
    list->head = new_node;
    new_node->next = temp;
    list->length++;
}
