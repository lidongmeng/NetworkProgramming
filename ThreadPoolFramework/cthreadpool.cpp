#include "cthreadpool.h"
#include <stdio.h>
CThreadPool::CThreadPool()
{
    m_busyList.clear();
    m_idleList.clear();
    m_num = 10;
    for (int i = 0; i < 10; ++i)
    {
        CWorkThread * t = new CWorkThread();
        t->setThreadpool(this);
        appendToIdleList(t);
        t->createThread(false);
    }
}

CThreadPool::CThreadPool(int num)
{
    printf("ThreadPool>> constructor\n");
    m_busyList.clear();
    m_idleList.clear();
    m_num = num;
    printf("ThreadPool>> create %d idle thread\n", num);
    for (int i = 0; i < num; ++i)
    {
        CWorkThread * t = new CWorkThread();
        t->setThreadpool(this);
        appendToIdleList(t);
        t->createThread(false);
        printf("ThreadPool>> thread id: %d\n", t->getThreadId());
    }
}

CWorkThread * CThreadPool::getIdleThread()
{
    while (m_idleList.empty())
    {
        printf("CThreadPool>>> no idle thread\n");
        m_idle_cond.wait();
    }
    printf("CThreadPool>> has idle thread\n");
    m_idle_mutex.lock();
    if (m_idleList.size() > 0)
    {
        CWorkThread * t = m_idleList.front();
        m_idle_mutex.unlock();
        return t;
    }
    m_idle_mutex.unlock();
    return NULL;
}

void CThreadPool::appendToIdleList(CWorkThread *thread)
{
    m_idle_mutex.lock();
    m_idleList.push_back(thread);
    m_threadList.push_back(thread);
    m_idle_mutex.unlock();
}

void CThreadPool::moveToBusyList(CWorkThread *thread)
{
    m_busy_mutex.lock();
    m_busyList.push_back(thread);
    m_busy_mutex.unlock();

    m_idle_mutex.lock();
    vector<CWorkThread*>::iterator pos = find(m_idleList.begin(), m_idleList.end(), thread);
    if (pos != m_idleList.end())
    {
        m_idleList.erase(pos);
    }
    m_idle_mutex.unlock();
}

void CThreadPool::moveToIdleList(CWorkThread *thread)
{
    m_idle_mutex.lock();
    m_idleList.push_back(thread);
    m_idle_mutex.unlock();

    m_busy_mutex.lock();
    vector<CWorkThread*>::iterator pos = find(m_busyList.begin(), m_busyList.end(), thread);
    if (pos != m_busyList.end())
    {
        m_busyList.erase(pos);
    }
    m_busy_mutex.unlock();
    // when to broadcast is proper
    m_idle_cond.broadcast();
}

void CThreadPool::run(CJob *job, void *jobdata)
{
    CWorkThread * t = getIdleThread();
    printf("ThreadPool>>> get an idle thread %d to run job %d\n", t->getThreadId(), job->getJobId());
    if (t != NULL)
    {
        moveToBusyList(t);
        t->setThreadpool(this);
        job->setWorkThread(t);
        t->setJob(job,jobdata);
    }
}

int CThreadPool::getIdleListSize()
{
    m_idle_mutex.lock();
    int result = m_idleList.size();
    m_idle_mutex.unlock();
    return result;
}
int CThreadPool::getBusyListSize()
{
    m_busy_mutex.lock();
    int result = m_busyList.size();
    m_busy_mutex.unlock();
    return result;
}

void CThreadPool::sync_all()
{
    while (1)
    {
        if (m_idleList.size() < m_num)
            m_idle_cond.wait();
        else
            break;
    }
}
