
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#endif
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "buffer.h"

#define peek_data(type) \
void *peek_##type(NODE *node) \
{                       \
    type *data = node->data;\
    return data;\
}

#define find_elem(Node_data,cmptype) \
NODE *find_elem_##cmptype(LIST *list,void* data) \
{                           \
    NODE *ptr = list->head->next;    \
    cmptype *cmp = data;\
    while(ptr != list->tail)\
    {\
        Node_data *dat = peek_##Node_data(ptr);\
        if(buffer_cmp(dat->buffer,cmp))\
        {\
            return ptr;\
        }\
    ptr = ptr->next;\
    }\
    return NULL;\
}


typedef struct NODE
{
    struct NODE *next;
    struct NODE *prev;
    void *data;
}NODE;
typedef struct LIST
{
    struct NODE *head;
    struct NODE *tail;
    int count;
}LIST;

LIST *init_list(LIST *list);
NODE *init_node(NODE *node);
void add(LIST *list,void *data);
NODE *find_string(LIST *list,char *data);
void *remove_node(LIST *list,NODE *del_ptr);
void delete_index(LIST *list,int index);
void print_node(LIST *list);
void destroy_list(LIST *list);
int l_is_empty(LIST *list);
