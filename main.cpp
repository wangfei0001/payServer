#include <iostream>

#include "threadpool.h"

#include "paymentserver.h"

#include "paypal.h"

using namespace std;





int main()
{

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

