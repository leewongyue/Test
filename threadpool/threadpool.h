#ifndef THREADPOOL_H
    #define THREADPOOL_H
#endif


#include <pthread.h>
#include "../log/log.h"
#include "jobqueue.h"

#define MAX_THREAD_POOL 10

typedef struct THREAD_INFO
{
    bool thread_state;
    int thread_index;
}THREAD_INFO;

pthread_t p_thread;
JOBQUEUE *jobqueue;
THREAD_INFO thread_info[MAX_THREAD_POOL];
static pthread_cond_t async_cond = PTHREAD_COND_INITIALIZER;
static pthread_cond_t cond[MAX_THREAD_POOL];
static pthread_mutex_t mutex_lock = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t mutex_async = PTHREAD_MUTEX_INITIALIZER;

void init_threadinfo(THREAD_INFO *thread_info);
void swap_thread_info(THREAD_INFO* a,THREAD_INFO* b);
void sort_active_threads(THREAD_INFO *thread_info);
int find_by_threadid(THREAD_INFO *info,int threadid);
int numof_activ_threads(THREAD_INFO*thread_info);
void *consume_thread(void *data);
void *monitor_thread(void *data);
void init_threadpool(pthread_t pthread);
void create_threadpool(pthread_t thread,int pool_size);
void consume_job(THREAD_INFO *info,int threadindex);
void print_active_threads(THREAD_INFO *info);
void sort_by_threadnum(THREAD_INFO *thread_info);
void sort_active_threads(THREAD_INFO *thread_info);
int find_lowindex(THREAD_INFO *info,int start);
