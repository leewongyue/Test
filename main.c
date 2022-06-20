#include <stdio.h>
#include "atomic_datastructure/atomic_queue.h"
int main()
{
  QUEUE *queue;
  queue = init_queue(queue);

  for(int i=0; i<10;i++){
    char*arr = malloc(sizeof(char)*5);
    arr = "asdf\0";
    enqueue(queue,(void*)arr);
  }
  printf("QUEUE SIZE : %d\n",queue->count);
  for(int i=0;i<10;i++){
    printf("%s\n",(char*)dequeue(queue));
  }

}
