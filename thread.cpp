#include <iostream>


#include "thread.h"


using namespace std;

void *callback(void* obj);

thread::thread()
{
    m_isAvailable = false;

    m_stop = false;

    pthread_create(&m_pthread, 0, &callback, this);
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

    cout << "thread start" << endl;

    while(!p->m_stop){



    }
    cout << "thread end" << endl;

    return obj;
}
