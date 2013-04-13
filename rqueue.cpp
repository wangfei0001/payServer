#include "rqueue.h"



rqueue::rqueue()
{
    pthread_mutex_init(&mutex, NULL);
}

rqueue::~rqueue()
{
    pthread_mutex_destroy(&mutex);
}

void rqueue::lock()
{
    pthread_mutex_lock( &this->mutex );
}

void rqueue::unlock()
{
    pthread_mutex_unlock( &this->mutex );
}

void rqueue::addRequestNode(request_node node)
{
    this->lock();
    this->myqueue.push(node);
    this->unlock();
}

request_node rqueue::getRequestNode()
{
    request_node node;

    this->lock();
    node = this->myqueue.front();
    this->unlock();

    return node;
}

void rqueue::popRequestNode()
{
    this->lock();
    this->myqueue.pop();
    this->unlock();
}


request_node rqueue::getAndRemoveRequestNode()
{
    request_node node;

    this->lock();
    node = this->myqueue.front();
    this->myqueue.pop();
    this->unlock();

    return node;
}

bool rqueue::isEmpty()
{
    return this->myqueue.empty();
}

int rqueue::count()
{
    return this->myqueue.size();
}
