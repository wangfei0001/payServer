#ifndef THREADPOOL_H
#define THREADPOOL_H



#include "thread.h"

#define DEFAULT_THREAD_COUNT 1

class ThreadPool
{

protected:

    int m_threads;

    thread **m_pthreads;


public:
    ThreadPool();
    ~ThreadPool();


    thread *getSpareThread();

    int getThreadsCount();

    void run();

};

#endif // THREADPOOL_H
