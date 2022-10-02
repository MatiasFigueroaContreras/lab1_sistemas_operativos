#include "linkedList.h"

/*
    Descripcion: crea una lista enlazada.
    Parametros:
        Ninguno
    Retorno:
        -Puntero a la lista enlazada creada.
*/
LinkedList *createList()
{
    LinkedList *list = malloc(sizeof(LinkedList));
    list->length = 0;
    list->head = NULL;
    return list;
}

/*
    Descripcion: crea un nodo con la informacion entregada.
    Parametros:
        -data: informacion a ser puesta en el nodo.
    Retorno:
        -Puntero al nodo creado.
*/
Node *createNode(char *data)
{
    Node *new_node = malloc(sizeof(Node));
    strcpy(new_node->data, data);
    new_node->next = NULL;
    return new_node;
}

/*
    Descripcion: permite insertar nueva informacion a una lista enlazada.
    Parametros:
        -list: lista enlazada en donde se insertara la informacion.
        -data: informacion a ser puesta en la lista enlazada.
    Retorno:
        No tiene.
*/
void insert(LinkedList *list, char *data)
{
    Node *new_node = createNode(data);
    Node *temp = list->head;
    list->head = new_node;
    new_node->next = temp;
    list->length++;
}
