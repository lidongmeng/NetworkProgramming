#ifndef CWORKTHREAD_H
#define CWORKTHREAD_H
#include "cjob.h"
#include "cthread.h"
#include "cthreadpool.h"
#include "CSynchronize.h"
class CJob;
class CThreadPool;
class CWorkThread : public CThread
{
private:
    CThreadPool * m_threadpool;
    CJob * m_job;
    void * m_job_data;
    CCondition job_cond; // wait for the job condition to excute the job
    CMutex m_mutex; // mutex to set the job and pool
public:
    CWorkThread();
    virtual ~CWorkThread();
    virtual void run();

    void setThreadpool(CThreadPool * pool);
    void setJob(CJob * job, void * data);
};

#endif // CWORKTHREAD_H
