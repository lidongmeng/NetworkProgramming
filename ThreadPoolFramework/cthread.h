#ifndef CTHREAD_H
#define CTHREAD_H
#include <pthread.h>
#include <stdio.h>
class CThread
{
protected:
    pthread_t m_thread_id;
public:
    CThread();
    virtual ~CThread();

    int getThreadId()const {return m_thread_id;}
    void createThread(bool deteached);
    virtual void run() = 0;
private:
   static void * _run_thread(void * arg);
};

#endif // CTHREAD_H
