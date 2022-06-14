#include <stdio.h>

#include "datastructure/linkedlist.h"
#include "buffer/buffer.h"

int main()
{
    LIST *list =init_list(list);
    int cnt=0;
    while (cnt != 20)
    {
        BUFFER *buff;
        buff = malloc(sizeof(BUFFER));
        buff->buffer = "asjskf";
        buff->count = 0;
        buff->offset = 0;
        insert_last(list,buff);
        cnt++;
    }
    cnt = 0;
    while (cnt != 20)
    {
        NODE *ptr = list->head;
        while (ptr != NULL)
        {
            printf("%p %d\n",ptr->data,cnt);
            ptr = ptr->next;
            cnt++;
        }
    }
}
