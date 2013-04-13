#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H

#include <pthread.h>

class workerthread
{
protected:
    pthread_t m_pthread;

    static void *callback(void *obj);

public:
    workerthread();

    int init(void *pool);

};

#endif // WORKERTHREAD_H
