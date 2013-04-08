#include <iostream>

#include <curl/curl.h>

#include "thread.h"

#include "paypal.h"


using namespace std;

void *callback(void* obj);

thread::thread()
{
    m_isAvailable = false;

    m_stop = false;

    //pthread_attr_t attr;

    //pthread_attr_init(&attr);
    /* We don't need to join this thread */
    //pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    pthread_create(&m_pthread, NULL, &callback, this);
    //pthread_attr_destroy(&attr);


}

thread::~thread()
{

}

bool thread::isAvailable()
{

    return m_isAvailable;
}


bool thread::start()
{


    return true;
}


bool thread::stop()
{


    return true;
}


bool thread::pause()
{
    return true;
}


//work function, thread

void *callback(void *obj)
{
    thread *p = (thread *)obj;

    cout << "thread start>" << endl;

    int i = 0;
    cout << "flag status:" << p->m_stop << endl;
    while(!p->m_stop){
        Paypal *paypal = new Paypal();


        cout << "start to grab->" << i++ << endl;


        //paypal->test();

        delete paypal;

        cout << "end!" << endl;

        sleep(1);
    }
    cout << "thread end" << endl;

    return obj;
}


