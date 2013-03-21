#ifndef THREAD_H
#define THREAD_H


#include <pthread.h>


class thread
{
protected:
    bool m_isAvailable;

    pthread_t m_pthread;

public:
    thread();

    ~thread();

    bool m_stop;

    bool isAvailable();

    bool start();

    bool stop();

    bool pause();
};

#endif // THREAD_H
