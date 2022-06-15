#include "linkedlist.h"

peek_data(BUFFER);
find_elem(BUFFER,char);

NODE *init_node(NODE *node)
{
    node = malloc(sizeof(LIST));
    node->next = NULL;
    node->data = NULL;
    return node;
}
LIST *init_list(LIST *list)
{
    list->head = malloc(sizeof (NODE));
    list->tail = malloc(sizeof (NODE));
    list->head->next = list->tail;
    list->tail->prev = list->head;
    list->count = 0;
    return list;
}

void add(LIST *list,void *data)
{
        NODE *newNode = init_node(newNode);
        newNode->data = data;

        newNode->prev = list->tail->prev;
        newNode->next = list->tail;
        list->tail->prev->next = newNode;
        list->tail->prev = newNode;
        list->count++;
}

void print_node(LIST *list)
{
    int cnt = 0;
    NODE *ptr = list->head->next;
    while (ptr != list->tail)
    {
        BUFFER *buff = (BUFFER *)peek_BUFFER(ptr);
        printf("[address : %p] [buffer : %s] [cnt :%d]\n",ptr->data,buff->buffer,cnt);
        ptr = ptr->next;
        cnt++;
    }
    printf("\n");
}

NODE *find_string(LIST *list,char *data)
{
    return find_elem_char(list,data);
}

void *remove_node(LIST *list,NODE *del_ptr)
{
    del_ptr->prev->next = del_ptr->next;
    del_ptr->next->prev = del_ptr->prev;
    free(del_ptr);
    list->count--;
}
void destroy_list(LIST *list)
{
    NODE *ptr = list->head->next;
    while(ptr != list->tail)
    {
        remove_node(list,ptr);
        ptr = list->head->next;
    }
}

void delete_index(LIST *list,int index)
{
    if(index > list->count)
        return;
    if(l_is_empty(list))
        return;
    int cnt = 0;
    NODE *ptr = list->head->next;
    while(ptr != list->tail)
    {
        if(index == cnt)
        {
            remove_node(list,ptr);
            return;
        }
        ptr = ptr->next;
        cnt++;
    }
}

int l_is_empty(LIST *list)
{
    return list->count == 0;
}
