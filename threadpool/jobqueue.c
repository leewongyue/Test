#include <stdatomic.h>
#include <stdbool.h>
#include <stdlib.h>

#include "jobqueue.h"
JOBQUEUE *jq_init_queue(JOBQUEUE *queue)
{
    queue = malloc(sizeof(JOBQUEUE)*10);
    queue->front = queue->rear = malloc(sizeof(JOBQUEUE));
    queue->rear->next = NULL;
    queue->count = 0;
    return queue;
}

void jq_enqueue(JOBQUEUE *queue,void *data)
{
    JOBQUEUE_NODE* newNode = (JOBQUEUE_NODE*)malloc(sizeof (JOBQUEUE_NODE));
    newNode->data = data;
    newNode->next = NULL;
    while(1)
    {
        JOBQUEUE_NODE *last = queue->rear;
        JOBQUEUE_NODE *next = last->next;
        if(last != queue->rear)
            continue;
        if(next == NULL)
        {
            if(jq_CAS(&(last->next),NULL,newNode))
            {
                jq_CAS(&queue->rear,last,newNode);
                queue->count++;
                return;
            }
        }
        else
            jq_CAS(&queue->rear,last,next);
    }
}

void* jq_dequeue(JOBQUEUE *queue)
{
    void* data;

    while (1)
    {
        JOBQUEUE_NODE *ptr;
        if(queue->count==0)
            return NULL;
        ptr = queue->front;
        data = ptr->data;
        if(jq_CAS(&queue->front,ptr,ptr->next))
        {
            free(ptr);
            queue->count--;
            return data;
        }
    }
}
bool jq_CAS(JOBQUEUE_NODE *addr,JOBQUEUE_NODE *old_node, JOBQUEUE_NODE *new_node)
{
    return atomic_compare_exchange_strong((volatile atomic_int *)addr,(int*)(&old_node),new_node);
}
