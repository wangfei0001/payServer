#ifndef THREAD_H
#define THREAD_H


#include <pthread.h>

#include "data/authorise.h"


class thread
{
protected:
    bool m_isAvailable;

    pthread_t m_pthread;

    pthread_mutex_t mutex;

    pthread_cond_t cond;



    static void *callback(void *obj);

    int parseRequests(char *xml, long size, Authorise *auth);

public:


    thread();

    ~thread();

    int init();

    unsigned int socketfd;

    int id;

    bool m_stop;

    bool isAvailable();

    bool start(int socketfd);

    bool stop();

    bool pause();

    void process();

    void setAvailable(bool available);

//    void setSocket(unsigned int *p_socket);


};

#endif // THREAD_H
