#include <iostream>

#include "threadpool.h"

#include "paymentserver.h"

#include "paypal.h"

using namespace std;

#include "rqueue.h"

#include "data/redparam.h"

int main()
{

#if 0

    RedParam r;



    cout << r.toString() << endl;

    return 0;

#endif


#if 0
    rqueue queue;

    request_node node1;
    node1.socketfd = 0;

    request_node node2;
    node2.socketfd = 1;

    request_node node3;
    node3.socketfd = 2;


    queue.addRequestNode(node1);

    queue.addRequestNode(node2);
    queue.addRequestNode(node3);


    while(!queue.isEmpty()){
        request_node node = queue.getAndRemoveRequestNode();

        cout << "->" << node.socketfd << endl;
    }

    cout << queue.count() << " left" << endl;


    return 0;
#endif





#if 0

    Paypal *paypal = new Paypal();

    paypal->test();

#endif


#if 1

    cout << "Start to create thread pool!" << endl;


    PaymentServer *server = new PaymentServer();

    server->start();


    while(1){
        sleep(4);
    }

    cout << "Goodbye guys." << endl;

#endif

    return 0;
}

