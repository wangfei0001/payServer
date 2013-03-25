#include <iostream>

#include "threadpool.h"

#include "paymentserver.h"

using namespace std;





int main()
{


    cout << "Start to create thread pool!" << endl;


    PaymentServer *server = new PaymentServer();


    server->start();


    while(1){
        sleep(4);
    }

    cout << "Goodbye guys." << endl;



    return 0;
}

