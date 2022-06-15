#include "datastructure/linkedlist.h"

int main()
{
  LIST *list = malloc(sizeof (LIST));
    list = init_list(list);
    int cnt=0;
    while (cnt != 20)
    {
        BUFFER *buff;
        buff = malloc(sizeof(BUFFER));
        buff->buffer = malloc(sizeof (char)*6);
        buff->buffer = "abcde\0";
        buff->count = cnt;
        buff->offset = 0;
        add(list,buff);
        cnt++;
    }
    BUFFER  *buffer1;
    buffer1 = malloc(sizeof(BUFFER));
    buffer1->buffer = malloc(sizeof (char)*6);
    buffer1->buffer = "a\0";
    buffer1->count = cnt;
    buffer1->offset = 0;
    add(list, buffer1);

    print_node(list);
    char *arr = "a\0";
    remove_node(list,find_string(list,arr));
    print_node(list);
    delete_index(list ,4);
    print_node(list);
    destroy_list(list);
}
