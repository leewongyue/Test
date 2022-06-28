
#ifndef JOBQUEUE_H
# define JOBQUEUE_H

#endif
#include <stdatomic.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct JOBARGUMENT
{
    void *arg1;
    void *arg2;
    void *arg3;
    void *arg4;
}JOBARGUMENT;

typedef struct JOB
{
    struct JOBARGUMENT *argument;
    int (*func)(void *arg1,void *arg2 ,int num);
}JOB;

typedef struct JOBQUEUE_NODE
{
    JOB *data;
    struct JOBQUEUE_NODE *volatile next;
}JOBQUEUE_NODE;

typedef struct JOBQUEUE
{
    struct JOBQUEUE_NODE *volatile front;
    struct JOBQUEUE_NODE *volatile rear;
    atomic_int count;
}JOBQUEUE;


void jq_enqueue(JOBQUEUE *queue,void *data);
JOBQUEUE *jq_init_queue(JOBQUEUE *queue);
void* jq_dequeue(JOBQUEUE *queue);
bool jq_CAS(JOBQUEUE_NODE *addr,JOBQUEUE_NODE *old_node, JOBQUEUE_NODE *new_node);
