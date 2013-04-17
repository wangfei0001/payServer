#ifndef THREAD_H
#define THREAD_H


#include <pthread.h>

#include "data/authorise.h"

#include "data/redparam.h"


class thread
{
protected:
    bool m_isAvailable;

    pthread_t m_pthread;

    pthread_t m_pRedThread;

    pthread_mutex_t mutex;

    pthread_cond_t cond;



    //paypal thread call back function
    static void *callback(void *obj);

    //red Thread call back function
    static void *red_callback(void *obj);


    //parse and re-organize the requests
    int parseRequests(char *xml, long size, Authorise *auth, RedParam *red);

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

};

#endif // THREAD_H
