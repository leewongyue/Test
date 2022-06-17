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
      NODE *last = queue->rear;
      NODE *next = last->next;

      if(last != queue->rear)
      {
        continue;
      }
      if(next == NULL)
      {
        if(CAS(&(last->next),NULL,newNode))
        {
            CAS(&queue->rear,last,newNode);
            queue->count++;
            return ;
        }
      }
      else
      {
        CAS(&queue->rear,last,next);
      }

    }
    
}

void* dequeue(QUEUE *queue)
{
    void* data;
    
    while (1)
    {
        NODE *ptr = queue->front;
        NODE *next = queue->front->next;
        NODE *last = queue->rear;
        NODE *lastnext = last->next;
        if(ptr != queue->front)
            continue;
        if(last == ptr)
        {
            if(lastnext == NULL)
            {
                return -1;
            }
            else
            {
                CAS(&queue->rear,last,lastnext);
                continue;
            }
        }
        if(next == NULL)
        {
            continue;
        }
        data = next->data;
         if(false == CAS(&queue->front,ptr,next))
        {
            continue;
        }
        ptr->next = NULL;
        free(ptr);
        queue->count--;
        return data;
    }
}
bool CAS(NODE *addr,NODE *old_node, NODE *new_node)
{
    return atomic_compare_exchange_strong((volatile atomic_int *)addr,(int*)(&old_node),(int)new_node);
}
