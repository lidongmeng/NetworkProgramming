#include "cthread.h"
#include "cjob.h"
#include "cthreadpoolmanager.h"
#include "CSynchronize.h"
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <stdlib.h>
class AJob : public CJob
{
public:
    void run(void * data)
    {
        for (int i = 1; i <= 20; ++i)
        {
            printf("A");
        }
        printf("\n");
    }
};

class BJob : public CJob
{
public:
    void run(void * data)
    {
        for (int i = 1; i <= 20; ++i)
        {

            printf("B");
        }
        printf("\n");
    }
};

void * func(void * arg)
{
    for (int i = 1; i <= 20; ++i)
    {

        printf("B");
    }
    printf("\n");
};

int main(int argc, char ** argv)
{
    int cnt = atoi(argv[1]);
    printf("main\n");
    clock_t start, end;
    double duration;
    start = clock();
    CThreadPoolManager * manager = new CThreadPoolManager(3);
    printf("Start the job\n");
    for (int i = 0; i < cnt; ++i)
    {
        CJob * job;
        if (i%2 == 0)
            job = new AJob();
        else
            job = new BJob();
        job->setJobId(i);
        printf("main>>> idle list size: %d, busy list size: %d\n", manager->pool->getIdleListSize(), manager->pool->getBusyListSize());
        manager->run(job, NULL);
    }
    manager->sync_all();
    end = clock();
    duration = (double)(end - start) / CLOCKS_PER_SEC;
    printf("%f seonds\n", duration);

    start = clock();
    for (int i = 0; i < cnt; ++i)
    {
        pthread_t id;
        pthread_create(&id, NULL, func, NULL);
        pthread_join(id, NULL);
    }
    end = clock();
    printf("%f seonds\n", duration);
    duration = (double)(end - start) / CLOCKS_PER_SEC;
    printf("%f seonds\n", duration);
    return 0;
}
