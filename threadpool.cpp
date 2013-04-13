#include <cstdlib>

#include <stdio.h>

#include <errno.h>

#include <error.h>

#include "threadpool.h"

#include "workerthread.h"


ThreadPool::ThreadPool()
{
    m_threads = DEFAULT_THREAD_COUNT;

    m_pthreads = new thread*[DEFAULT_THREAD_COUNT];

    for(int i = 0; i < m_threads; i++){
        thread *pThread = new thread();

        pThread->id = i;

        if(!pThread->init()){

            m_pthreads[i] = pThread;

            printf("create thread: %d %p\n", i, pThread);
        }else{
            m_pthreads[i] = NULL;

            delete pThread;
        }
    }
    workerthread *worker = new workerthread();

    worker->init(this);
}


//void ThreadPool::run()
//{
//    for(int i = 0; i < m_threads; i++){
//        thread *pThread = m_pthreads[i];

//        if(pThread) pThread->start();
//    }
//}


/* Get Spare thread */
thread * ThreadPool::getSpareThread()
{
    thread *returnThread = NULL;

    //get spare thread
    for(int i = 0; i < m_threads; i++){
        thread *pThread = m_pthreads[i];

        if(pThread && pThread->isAvailable()){

            returnThread = pThread;

            break;
        }
    }
    return returnThread;
}


/* Get total amount of threads */
int ThreadPool::getThreadsCount()
{
    return m_threads;
}


ThreadPool::~ThreadPool()
{
    if(m_pthreads){
        delete m_pthreads;
    }
}
