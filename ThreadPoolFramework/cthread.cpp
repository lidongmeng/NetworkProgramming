#include "cthread.h"

void * CThread::_run_thread(void * arg)
{
    if (arg != NULL)
        ((CThread*) arg)->run();
    return (void*)0;
}

CThread::CThread()
{
    printf("Thread>>thread created\n");
}

CThread::~CThread()
{

    if (pthread_self() == m_thread_id)
    {
        pthread_exit(NULL);
    }
}

void CThread::createThread(bool deteached)
{
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, deteached);
    pthread_create(&m_thread_id, &attr, _run_thread, this); // this as paramater of _run_thread
}

