#include "cthreadpoolmanager.h"

CThreadPoolManager::CThreadPoolManager()
{
    pool = new CThreadPool();
}


CThreadPoolManager::CThreadPoolManager(int num)
{
    printf("CThreadPoolManager>> constructor\n");
    pool = new CThreadPool(num);
}

void CThreadPoolManager::run(CJob *job, void *data)
{
    if (job != NULL)
        pool->run(job, data);
}

void CThreadPoolManager::sync_all()
{
    pool->sync_all();
}
