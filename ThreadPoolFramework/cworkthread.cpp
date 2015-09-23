#include "cworkthread.h"

CWorkThread::CWorkThread()
{
    printf("CWorkThread>> constructor\n");
}

CWorkThread::~CWorkThread()
{
    if (m_job != NULL)
    {
        delete m_job;
    }
    if (m_threadpool != NULL)
    {
        delete m_threadpool;
    }
}

void CWorkThread::run()
{
    while (1)
    {
        while (m_job == NULL)
            job_cond.wait();
        m_job->run(m_job_data);
        m_job->setWorkThread(NULL);
        m_job = NULL;
        // changed to the idle thread
        printf("CWorkThread>>> over\n");
        m_threadpool->moveToIdleList(this);
    }
}

void CWorkThread::setJob(CJob *job, void *data)
{
    m_mutex.lock();
    m_job = job;
    m_job_data = data;
    job->setWorkThread(this);
    m_mutex.unlock();
    job_cond.broadcast();
}

void CWorkThread::setThreadpool(CThreadPool *pool)
{
    m_mutex.lock();
    m_threadpool = pool;
    m_mutex.unlock();
}
