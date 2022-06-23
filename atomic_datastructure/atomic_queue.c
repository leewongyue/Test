#include "atomic_queue.h"

QUEUE *init_queue(QUEUE *queue)
{
    queue = malloc(sizeof(QUEUE));
    queue->front = queue->rear = malloc(sizeof(NODE));
    queue->rear->next = NULL;
    queue->count = 0;
    return queue;
}

void enqueue(QUEUE *queue,void *data)
{
    NODE* newNode = (NODE*)malloc(sizeof (NODE));
    newNode->data = data;
    newNode->next = NULL;
    while(1)
    {
        NODE *ptr = queue->rear;
        if(queue->count == 0)
        {
            CAS(&queue->front,NULL,newNode);
            queue->count++;
            return ;
        }
        else
        {
            CAS(&queue->rear->next,NULL,newNode);
        }
        CAS(&queue->rear,ptr,newNode);
        queue->count++;
        return ;
    }

}
void* dequeue(QUEUE *queue)
{
    void* data;
    NODE *ptr ;
    while (1)
    {
        if(queue->count==0)
            return NULL;
        ptr = queue->front;
        data = ptr->data;
        if(CAS(&queue->front,ptr,ptr->next))
        {
            free(ptr);
            queue->count--;
            return data;
        }
    }
}
bool CAS(NODE *addr,NODE *old_node, NODE *new_node)
{
    return atomic_compare_exchange_strong((volatile atomic_int *)addr,(int*)(&old_node),new_node);
}
