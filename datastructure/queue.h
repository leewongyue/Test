#ifndef QUEUE_H
# define QUEUE_H

#endif

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct NODE
{
    void *data;
    struct NODE *next;
}NODE;

typedef struct QUEUE
{
    struct NODE *front;
    struct NODE *rear;
    int count;
}QUEUE;


void enqueue(QUEUE *queue,void *data);
QUEUE *init_queue(QUEUE *queue);
bool is_empty(QUEUE *queue);
void* dequeue(QUEUE *queue);
