#ifndef PAYMENTSERVER_H
#define PAYMENTSERVER_H

#include "threadpool.h"

class PaymentServer
{
protected:

    ThreadPool *pool;

    int socketfd;

    int createListeningSocket();



public:
    PaymentServer();

    ~PaymentServer();



    void start();

};

#endif // PAYMENTSERVER_H
