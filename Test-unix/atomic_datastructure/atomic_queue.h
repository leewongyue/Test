#ifndef QUEUE_H
# define QUEUE_H

#endif
#include <stdatomic.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct atomic_NODE
{
    void *data;
    struct atomic_NODE *volatile next;
}atomic_NODE;

typedef struct atomic_QUEUE
{
    struct atomic_NODE *volatile front;
    struct atomic_NODE *volatile rear;
    atomic_int count;
}atomic_QUEUE;


void at_enqueue(atomic_QUEUE *queue,void *data);
atomic_QUEUE *at_init_queue(atomic_QUEUE *queue);
void* at_dequeue(atomic_QUEUE *queue);
bool at_CAS(atomic_NODE *addr,atomic_NODE *old_node, atomic_NODE *new_node);
