#ifndef CTHREADPOOLMANAGER_H
#define CTHREADPOOLMANAGER_H
#include "cthreadpool.h"
#include "cjob.h"

class CThreadPoolManager
{
public:
    CThreadPool * pool;
public:
    CThreadPoolManager();
    CThreadPoolManager(int num);
    ~CThreadPoolManager();
    void run(CJob *job, void * data);
    void sync_all();
};

#endif // CTHREADPOOLMANAGER_H
