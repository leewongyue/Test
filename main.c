#include <stdio.h>
#include "atomic_datastructure/atomic_queue.h"
int main()
{
  QUEUE *queue ;
  queue = malloc(sizeof(QUEUE));
  queue->count = 0;
  queue->front = queue->rear =malloc(sizeof(NODE));

  for(int i=0; i<10;i++){
    char*arr = malloc(sizeof(char)*5);
    arr = "asdf";
    enqueue(queue,arr);
    printf("[enqueue cnt ] : %d [enqueue data ] : %s\n",i,arr);
  }
  printf("QUEUE SIZE : %d\n",queue->count);
  for(int i=0;i<11;i++){
    char *arr = dequeue(queue);
    printf("[dequeue cnt ] : %d ",i);
    printf("[dequeue ] : %s \n",arr);
  }

}
