#ifndef CJOB_H
#define CJOB_H
#include "cworkthread.h"
class CWorkThread;
class CJob
{
private:
    CWorkThread * m_workThread;
    int m_id;
public:
    CJob();
    virtual ~CJob();
    virtual void run(void * data) = 0;
    void setJobId(int id){m_id = id;}
    int getJobId()const {return m_id;}
    void setWorkThread(CWorkThread * t) { m_workThread = t;}
    CWorkThread * getWorkThread() const {return m_workThread;}
};

#endif // CJOB_H
