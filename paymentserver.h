#ifndef PAYMENTSERVER_H
#define PAYMENTSERVER_H

#include "threadpool.h"

#include "data/authorise.h"

class PaymentServer
{
protected:

    ThreadPool *pool;

    int socketfd;

    int createListeningSocket();

    int parseRequests(char *xml, long size, Authorise *auth);

public:
    PaymentServer();

    ~PaymentServer();



    void start();

};

#endif // PAYMENTSERVER_H
