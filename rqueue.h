#ifndef RQUEUE_H
#define RQUEUE_H


#include <queue>

#include <pthread.h>

using namespace std;


struct request_node{
    unsigned int socketfd;
};

class rqueue
{
protected:
    queue<request_node> myqueue;

    pthread_mutex_t mutex;

    void lock();

    void unlock();

public:
    rqueue();

    ~rqueue();

    void addRequestNode(request_node node);

    request_node getAndRemoveRequestNode();

    request_node getRequestNode();

    void popRequestNode();

    bool isEmpty();

    int count();
};

#endif // RQUEUE_H
