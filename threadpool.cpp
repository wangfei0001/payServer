#include <cstdlib>



#include "threadpool.h"


void *callback(void* obj);

ThreadPool::ThreadPool()
{
    m_threads = DEFAULT_THREAD_COUNT;

    m_pthreads = new thread*[100];

    for(int i = 0; i < m_threads; i++){
        thread *pThread = new thread();

        m_pthreads[i] = pThread;

    }
}


void ThreadPool::run()
{

    for(int i = 0; i < m_threads; i++){
        thread *pThread = m_pthreads[i];

        pThread->start();
    }
}


/* Get Spare thread */
thread * ThreadPool::getSpareThread()
{
    thread *returnThread = NULL;

    //get spare thread
    for(int i = 0; i < m_threads; i++){
        thread *pThread = m_pthreads[i];

        if(pThread->isAvailable()){

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
