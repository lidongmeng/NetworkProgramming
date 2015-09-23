#ifndef CSYNCHRONIZE_H
#define CSYNCHRONIZE_H
#include <pthread.h>
#include <stdio.h>
class CMutex {
protected:
    pthread_mutex_t m_mutex;
public:
    CMutex() {
        printf("CMutex>>> create mutex\n");
        int status;
        status = pthread_mutex_init(&m_mutex, NULL);
        if (status != 0) {
            printf("CMutex>>> create error\n");
        }
    }

    ~CMutex() {
        destory();
    }

    void lock() {
        int status;
        status = pthread_mutex_lock(&m_mutex);
        if (status != 0) {
            printf("CMutex>>> lock error\n");
        }
    }

    void unlock() {
        int status;
        status = pthread_mutex_unlock(&m_mutex);
        if (status != 0) {
            printf("CMutex>>> unlock error\n");
        }
    }

    bool isLocked() {
        if (pthread_mutex_trylock(&m_mutex) != 0) {
            return true;
        } else {
            unlock();
            return false;
        }
    }

    void destory() {
        int status;
        status = pthread_mutex_destroy(&m_mutex);
        if (status != 0) {
            printf("CMutex>>> create error\n");
        }
    }
};

class CCondition : public CMutex
{
private:
    pthread_cond_t m_cond;
public:
    CCondition() {
        int status;
        printf("CCondition>> constuctor\n");
        status = pthread_cond_init(&m_cond, NULL);
        if (status != 0) {
            printf("CCondition>> create error\n");
        }
    }

    ~CCondition() {
        int status;
        status = pthread_cond_destroy(&m_cond);
        if (status != 0) {
            printf("CCondition>> destory error\n");
        }
    }

    void wait() {
        int status;
        status = pthread_cond_wait(&m_cond, &m_mutex);
        if (status != 0) {
            printf("CCondition>> wait error\n");
        }
    }

    void signal() {
        int status;
        status = pthread_cond_signal(&m_cond);
        if (status != 0) {
            printf("CCondition>> signal error\n");
        }
    }

    void broadcast() {
        int status;
        status = pthread_cond_broadcast(&m_cond);
        if (status != 0) {
            printf("CCondition>> broadcast error\n");
        }
    }
};

#endif // CSYNCHRONIZE_H
