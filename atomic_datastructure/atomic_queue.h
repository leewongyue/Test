#ifndef QUEUE_H
# define QUEUE_H

#endif
#include <stdatomic.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct NODE
{
    void *data;
    struct NODE *volatile next;
}NODE;

typedef struct QUEUE
{
    struct NODE *front;
    struct NODE *rear;
    int count;
}QUEUE;


void enqueue(QUEUE *queue,void *data);
QUEUE *init_queue(QUEUE *queue);
void* dequeue(QUEUE *queue);
bool CAS(NODE *addr,NODE *old_node, NODE *new_node);
