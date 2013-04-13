#include <iostream>

#include <curl/curl.h>

#include <errno.h>

#include <error.h>

#include "thread.h"

#include "paypal.h"


using namespace std;

long m_request_count = 0;


thread::thread()
{
    m_isAvailable = true;

    m_stop = false;

    //pthread_attr_t attr;

    //pthread_attr_init(&attr);
    /* We don't need to join this thread */
    //pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    pthread_mutex_init(&mutex, NULL);

    pthread_cond_init(&cond, NULL);

    socketfd = -1;

    pthread_mutex_lock( &mutex );
    //pthread_attr_destroy(&attr);
}

thread::~thread()
{
    pthread_mutex_destroy(&mutex);

    pthread_cond_destroy(&cond);
}


int thread::init()
{
    if(pthread_create(&m_pthread, NULL, &callback, this) != 0){
        cout << "Create thread error code " << errno << endl;
        return -1;
    }
    return 0;
}

bool thread::isAvailable()
{
    return m_isAvailable;
}


bool thread::start()
{
//    pthread_mutex_lock( &mutex );
    this->m_isAvailable = false;
    pthread_mutex_unlock( &mutex );

//    cout << "signal to thread " << this->id << endl;
    if( pthread_cond_signal(&cond) != 0){

        perror("pthread_cond_signal() error");
        //exit(0);

    }

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

//void thread::setSocket(unsigned int *p_socket)
//{
//    p_socketfd = p_socket;
//}

//work function, thread

void *thread::callback(void *obj)
{
    thread *p = (thread *)obj;

    while(!p->m_stop){
        pthread_mutex_lock( &p->mutex );

//        pthread_cond_wait (&p->cond, &p->mutex);

//        p->m_isAvailable = false;

//        cout << "!thread start>" << endl;

        char buffer[2048];

        cout << "command count: " << m_request_count << endl;

        m_request_count++;
        if (recv(p->socketfd, buffer, sizeof(buffer), 0 ) > 0){
           //printf("Received message: %s\n", buffer);



           //sleep(10);

            //start to parse the xml request;


           sprintf(buffer, "ok");

           send(p->socketfd, buffer, 3, 0);

        }else{
            cout << errno << endl;
            cout << "recv error detected" << endl;
        }


        if(p->socketfd != -1){
            close(p->socketfd);
            p->socketfd = -1;
        }
        p->m_isAvailable = true;
//        pthread_mutex_unlock( &p->mutex );

        usleep(1);
    }

#if 0
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
#endif


    return obj;
}


