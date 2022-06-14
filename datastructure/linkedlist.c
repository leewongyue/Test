#include "linkedlist.h"

LIST *init_list(LIST *list)
{
    list = malloc(sizeof(LIST));
    list->head = NULL;
    list->count = 0;
    return list;
}

void insert_last(LIST *list,void *data)
{
    if(!list)
        return;
    NODE *temp;
    NODE *newNode = (NODE*)malloc(sizeof(NODE));
    newNode->data = data;
    newNode->next = NULL;

    if(l_is_empty(list))
    {
        list->head = newNode;
        list->count++;
        return;
    }
    temp = list->head;
    while(temp->data != NULL)
    {
        temp = temp->data;
    }
    temp->data = newNode;
    list->count++;
}

void delete_elem(LIST *list,void *data)
{
    if(l_is_empty(list))
        return;
    NODE *ptr = list->head;
    while (ptr->data != data)
    {
        ptr = ptr->next;
    }
    ptr->next = list->head;
    list->count--;
    free(data);
}

bool l_is_empty(LIST *list)
{
    return list->count == 0;
}