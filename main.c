#include <stdio.h>

#include "datastructure/queue.h"
#include "buffer/buffer.h"

int main()
{
    QUEUE *queue = init_queue(queue);
    int cnt=0;
    while (cnt != 20)
    {
        BUFFER *buff;
        buff = malloc(sizeof(BUFFER));
        buff->buffer = "buffer";
        buff->count = 0;
        buff->offset = 0;
        enqueue(queue,buff);
        cnt++;
    }
    cnt = 0;
    while (cnt != 20)
    {
       BUFFER *buff = (BUFFER*)dequeue(queue);
       printf("%s \n",buff->buffer);
       cnt++;
    }
}