
#include "threadpool/threadpool.h"

int test_func(int a,char* arr,int num)
{
    //printf("[JOBQUEUE FUNCTION] : Data Index : {%d} Data : {%s} THREADNUM : %d\n",a,arr,num);
    a+num;
}
int main__()
{
    jobqueue = jq_init_queue(jobqueue);

    for(int i=0;i<2000000;i++)
    {
        JOB *job = malloc(sizeof(JOB));
        JOBARGUMENT *arg = malloc(sizeof(JOBARGUMENT));
        arg->arg1 = i;
        arg->arg2 = "asdf\0";
        job->func = test_func;
        job->argument = arg;
        jq_enqueue(jobqueue,job);
    }
    printf("[END ENQUEUE]\n");

    int status;
    int pool_size = MAX_THREAD_POOL;


    pthread_cond_init(&cond,NULL);
    if(pool_size < 0 || pool_size > MAX_THREAD_POOL)
    {
        printf("pool size error \n");
        exit(0);
    }

    create_threadpool(p_thread,pool_size);

    sleep(10);
    while (1)
    {
        usleep(10);
        //thread pool 이 꽉 차 있다면
        pthread_mutex_lock(&mutex_async);
        sort_active_threads(thread_info);
        pthread_mutex_unlock(&mutex_async);
        if(thread_info[0].thread_state == true)
        {
            printf("threadpool is FULL\n");
            sleep(1);
            continue;
        }
        else
        {

            if(jobqueue->count != 0)
            {
                pthread_mutex_lock(&mutex_async);
                sort_thread_info(thread_info);
                pthread_cond_signal(&cond[0]);
                thread_info[0].thread_state = true;
                pthread_mutex_unlock(&mutex_async);
            }
            else
            {
              sleep(5);
              for(int i=0;i<2000000;i++)
              {
                  JOB *job = malloc(sizeof(JOB));
                  JOBARGUMENT *arg = malloc(sizeof(JOBARGUMENT));
                  arg->arg1 = i;
                  arg->arg2 = "asdf\0";
                  job->func = test_func;
                  job->argument = arg;
                  jq_enqueue(jobqueue,job);
              }
              printf("[ENQUEUE]\n");

              continue;
            }
        }
    }
    pthread_join(p_thread,(void **)status);
}
