#ifndef CTHREADPOOL_H
#define CTHREADPOOL_H

#include "cjob.h"
#include "cworkthread.h"
#include "CSynchronize.h"
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
class CWorkThread;
class CJob;
class CThreadPool
{
private:
    int m_num;
    vector<CWorkThread*> m_threadList;
    vector<CWorkThread*> m_busyList;
    vector<CWorkThread*> m_idleList;

    // find initial before the constructor
    CMutex m_idle_mutex;
    CMutex m_busy_mutex;
    CCondition m_idle_cond;

public:
    CThreadPool();
    CThreadPool(int num);
    ~CThreadPool(){}

    int getNum()const {return m_num;}
    void setNum(int num) {m_num = num;}

    void run(CJob * job, void * jobdata);

    CWorkThread * getIdleThread();
    void appendToIdleList(CWorkThread * thread);
    void moveToBusyList(CWorkThread * thread);
    void moveToIdleList(CWorkThread * thread);
    int getIdleListSize();
    int getBusyListSize();

    void sync_all();
};

#endif // CTHREADPOOL_H
