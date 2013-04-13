#include "workerthread.h"

#include <iostream>

#include <stdio.h>

#include "thread.h"

#include "rqueue.h"

#include "threadpool.h"


extern rqueue *request_queue;

workerthread::workerthread()
{

}


int workerthread::init(void *pool)
{
    if(pthread_create(&m_pthread, NULL, &callback, pool) != 0){
        //cout << "Create workder thread error code " << errno << endl;
        return -1;
    }
    return 0;
}


void *workerthread::callback(void *obj)
{
    ThreadPool *pool = (ThreadPool *)obj;

//    sleep(10);
    while(true){
        if(request_queue->count() > 0){
            request_node node;
            while(!request_queue->isEmpty()){

                thread *p_thread = pool->getSpareThread();

                if(p_thread){
                    node = request_queue->getAndRemoveRequestNode();

                    cout << "find a spare thread for workder:" << p_thread << " index:" << p_thread->id << endl;

                    p_thread->socketfd = node.socketfd;

                    p_thread->start();

                    //request_queue->popRequestNode();

                    cout << request_queue->count() << " left" << endl;
                }

                break;
            }
        }
        usleep(100);
    }

    return NULL;
}
