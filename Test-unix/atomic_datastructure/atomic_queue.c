#include "atomic_queue.h"


atomic_QUEUE *at_init_queue(atomic_QUEUE *queue)
{
    queue = malloc(sizeof(atomic_QUEUE)*10);
    queue->front = queue->rear = malloc(sizeof(atomic_NODE));
    queue->rear->next = NULL;
    queue->count = 0;
    return queue;
}

/*
 *  atomic_NODE *ptr = queue->rear;
        if(queue->count == 0)
        {
            at_CAS(&queue->front,ptr,newNode);
            at_CAS(&queue->rear,ptr,newNode);
            queue->count++;
//            atomic_compare_exchange_strong(&queue->count,queue->count,queue->count++);
            return ;
        }
        else
        {
            at_CAS(&queue->rear->next,NULL,newNode);
            at_CAS(&queue->rear,ptr,newNode);
            queue->count++;
            return ;
        }

 *
 */
void at_enqueue(atomic_QUEUE *queue,void *data)
{
    atomic_NODE* newNode = (atomic_NODE*)malloc(sizeof (atomic_NODE));
    newNode->data = data;
    newNode->next = NULL;
    while(1)
    {
        atomic_NODE *last = queue->rear;
        atomic_NODE *next = last->next;
        if(last != queue->rear)
            continue;
        if(next == NULL)
        {
            if(at_CAS(&(last->next),NULL,newNode))
            {
                at_CAS(&queue->rear,last,newNode);
                queue->count++;
                return;
            }
        }
        else
            at_CAS(&queue->rear,last,next);
    }

}
/*
 *  if(queue->count==0)
            return NULL;
        ptr = queue->front;
        data = ptr->data;
        if(at_CAS(&queue->front,ptr,ptr->next))
        {
            free(ptr);
            queue->count--;
            return data;
        }
 */
/*
 *   atomic_NODE *first = queue->front;
        atomic_NODE *next = first->next;
        atomic_NODE *last = queue->rear;
        atomic_NODE *lastnext = last->next;
        if (first != queue->front)
            continue;
        if (last == first) {
            if (lastnext == NULL) {
                return NULL;
            }
            else
            {
                at_CAS(&queue->rear, last, lastnext);
                continue;
            }
        }
        if (NULL == next)
            continue;
        data = next->data;
        if (false == at_CAS(&queue->front, first, next))
            continue;
//        first->next = NULL;
        free(first);
        return data;
 */
void* at_dequeue(atomic_QUEUE *queue)
{
    void* data;

    while (1)
    {
        atomic_NODE *ptr;
        if(queue->count==0)
            return NULL;
        ptr = queue->front;
        data = ptr->data;
        if(at_CAS(&queue->front,ptr,ptr->next))
        {
            free(ptr);
            queue->count--;
            return data;
        }
    }
}
bool at_CAS(atomic_NODE *addr,atomic_NODE *old_node, atomic_NODE *new_node)
{
    return atomic_compare_exchange_strong((volatile atomic_int *)addr,(int*)(&old_node),new_node);
}