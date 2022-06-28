#include "threadpool.h"


void init_threadinfo(THREAD_INFO *thread_info)
{
    for(int i=0;i<MAX_THREAD_POOL;i++)
    {
        thread_info[i].thread_index = i;
        thread_info[i].thread_state =false;
        printf("[THREADINFO] : thread_index : %d thread_state : %d\n",thread_info[i].thread_index,thread_info[i].thread_state);
    }
    printf("THREADINFO INIT COMPLETED\n");
}
void swap_thread_info(THREAD_INFO* a,THREAD_INFO* b)
{
    THREAD_INFO temp = *a;
    *a = *b;
    *b = temp;
}
int find_lowindex(THREAD_INFO *info,int start)
{
    int cnt = 0;
    int lowindex = start;
    while (cnt != MAX_THREAD_POOL)
    {
        if(info[cnt].thread_index < info[lowindex].thread_index)
        {
            lowindex = cnt;
        }
        cnt++;
    }
    return lowindex;
}
void sort_by_threadnum(THREAD_INFO *thread_info)
{
    int cnt = 0;
    while (cnt != MAX_THREAD_POOL)
    {
        int lowindex = find_lowindex(thread_info,cnt);
        swap_thread_info(&thread_info[cnt],&thread_info[lowindex]);
    }

}
void sort_active_threads(THREAD_INFO *thread_info)
{
    int cnt=0;
    int max_thread_pool = MAX_THREAD_POOL-1;
    while (cnt != MAX_THREAD_POOL)
    {
        if(cnt == max_thread_pool)
            return;
        if(thread_info[cnt].thread_state == true)
        {
            while (max_thread_pool != 0)
            {
                if(thread_info[max_thread_pool].thread_state == false)
                {
                    swap_thread_info(&thread_info[cnt],&thread_info[max_thread_pool]);
                    break;
                }
                max_thread_pool--;
            }
        }
        else
        {
            return;
        }
        cnt++;
    }
}
int find_by_threadid(THREAD_INFO *info,int threadid)
{
    int cnt = 0;
   do
    {
        if(info[cnt].thread_index == threadid)
        {
            return cnt;
        }
        cnt++;
    } while (1);
}
int numof_active_threads(THREAD_INFO*thread_info)
{
    int cnt = 0;
    int result = 0;
    while (cnt != MAX_THREAD_POOL)
    {
        if(thread_info[cnt].thread_state == true)
        {
            result++;
        }
        cnt++;
    }
    return result;
}
void print_active_threads(THREAD_INFO *info)
{
     int cnt = 0;
    int result = 0;
    sort_by_threadnum(info);
    while (cnt != MAX_THREAD_POOL)
    {
        printf("[MONITOR] : { [THREAD NUM] : %d [STATE] : %s }\n",info[cnt].thread_index,info[cnt].thread_state ? "RUN" : "TERMINATED");
        cnt++;
    }
}

void consume_job(THREAD_INFO *info,int threadindex)
{
    pthread_mutex_lock(&mutex_lock);
    threadindex = find_by_threadid(thread_info,info->thread_index);
    info[threadindex].thread_state = true;
    JOB *job =(JOB*) jq_dequeue(jobqueue);
    pthread_mutex_unlock(&mutex_lock);
    if(job == NULL)
    {
        return;
    }
    job->func(job->argument->arg1,job->argument->arg2,info->thread_index);
    free(job);
}
void *consume_thread(void *data)
{
    THREAD_INFO *info = (THREAD_INFO*)data;
    pthread_mutex_lock(&mutex_async);
    pthread_cond_signal(&async_cond);
    pthread_mutex_unlock(&mutex_async);
    printf("[CONSUME FUNCTION ] START THREAD [THREAD NUM] : %d \n",info->thread_index);
    while(1)
    {
        usleep(100);
        int threadindex;

        pthread_mutex_lock(&mutex_lock);
        threadindex = find_by_threadid(thread_info,info->thread_index);
        thread_info[threadindex].thread_state = false;
        pthread_cond_wait(&cond[threadindex],&mutex_lock);
        pthread_mutex_unlock(&mutex_lock);

        consume_job(info,threadindex);
        if(jobqueue->count == 0)
        {
            pthread_mutex_lock(&mutex_lock);
            threadindex = find_by_threadid(thread_info,info->thread_index);
            thread_info[threadindex].thread_state = false;
            pthread_cond_wait(&cond[info->thread_index],&mutex_lock);
            pthread_mutex_unlock(&mutex_lock);
        }
    }
}
void *monitor_thread(void *data)
{
    printf("========================================\n");
    printf("moniter thread start\n");
    int activated_threads = 0;
    while(1)
    {
        printf("========================================\n");
        printf("***********MONITOR THREAD***************\n");
        pthread_mutex_lock(&mutex_lock);
        activated_threads = numof_active_threads(thread_info);
        //print_active_threads(thread_info);
        printf("MONITOR : [ACTIVATED THREADS] : %d\n",activated_threads);
        printf("========================================\n");
        pthread_mutex_unlock(&mutex_lock);
        sleep(2);
    }
}

void create_threadpool(pthread_t thread,int pool_size)
{
    for(int i=0; i<pool_size;i++)
    {
        pthread_mutex_lock(&mutex_async);
        thread_info[i].thread_state = true;
        thread_info[i].thread_index = i;
        if(pthread_create(&thread,NULL,consume_thread,((void*)&thread_info[i])) < 0)
        {
            DEBUG_LOG_ERRNO("THREAD CREATE FAILED",-1);
        }
        pthread_cond_wait(&async_cond, &mutex_async);
        pthread_mutex_unlock(&mutex_async);
    }
    pthread_create(&p_thread,NULL,monitor_thread,(void*)NULL);
}
