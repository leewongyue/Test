#include <stdatomic.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "atomic_datastructure/atomic_queue.h"

int cnt_thread = 0;
int id = 1;
dwThreadID[10];
int result = 0;
int total = 0;
atomic_QUEUE *queue;
struct threadData{
    int tid;
    char *message;
};

void thread_func(void *thread_data)
{
    (void) thread_data;
    for(int i=0;i<10000;i++){
        enqueue(queue,"data");   
    }
    printf("[p1] : %s\n",dequeue(queue));
}

int main(void)
{
    struct threadData *data = (struct threadData*)malloc(sizeof(struct threadData));   
    HANDLE hthread[10];
    queue = init_queue(queue);

    while(1)
    {
        if(cnt_thread == 10)
        {
            break;
        }
        data->tid = id++;
        hthread[cnt_thread] = CreateThread(NULL,0,thread_func,(LPVOID)data,0,&dwThreadID[cnt_thread]);
        cnt_thread++;
    }
    WaitForMultipleObjects(cnt_thread,hthread,TRUE,INFINITE);
    

    // for (int i = 0; i < cnt_thread; i++)
    // {
    //     GetExitCodeThread(hthread[i],&result);
    //     total+=result;
    //     CloseHandle(hthread[i]);
    // }
}

