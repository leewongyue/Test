#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#endif
#include <stdlib.h>
#include <stdbool.h>

typedef struct NODE
{
    void *data;
    struct NODE *next;
}NODE;

typedef struct LIST
{
    struct NODE *head;
    int count;
}LIST;

LIST *init_list(LIST *list);
void insert_last(LIST *list,void *data);
void delete_elem(LIST *list,void *data);
bool l_is_empty(LIST *list);
void display(LIST *list);