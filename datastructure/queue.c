#include "queue.h"

QUEUE *init_queue(QUEUE *queue)
{
    queue = malloc(sizeof(QUEUE));
    queue->front = queue->rear = NULL;
    queue->count = 0;
    return queue;
}

bool is_empty(QUEUE *queue)
{
    return queue->count == 0;
}

void enqueue(QUEUE *queue,void *data)
{
    if(!queue)
        return ;
    NODE* newNode = (NODE*)malloc(sizeof (NODE));
    newNode->data = data;
    newNode->next = NULL;

    if(is_empty(queue))
    {
        queue->front = newNode;
    }
    else
    {
        queue->rear->next = newNode;
    }
    queue->rear=newNode;
    queue->count++;
}

void* dequeue(QUEUE *queue)
{
    void* data;
    NODE *ptr;
    if(is_empty(queue))
    {
        return NULL;
    }
    ptr = queue->front;
    data = ptr->data;
    queue->front = ptr->next;
    free(ptr);
    queue->count--;

    return data;
}