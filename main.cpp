#include <iostream>

#include "threadpool.h"

#include "paymentserver.h"

using namespace std;





int main()
{


    cout << "Start to create thread pool!" << endl;


    PaymentServer *server = new PaymentServer();


    server->start();


    cout << "Goodbye guys." << endl;

    return 0;
}

