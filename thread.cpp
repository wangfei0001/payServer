#include <iostream>

#include <curl/curl.h>

#include <libxml/parser.h>

#include <errno.h>

#include <string.h>

#include <error.h>

#include "thread.h"

#include "paypal.h"

#include "rqueue.h"


using namespace std;

long m_request_count = 0;


extern rqueue *request_queue;

thread::thread()
{
    m_isAvailable = true;

    m_stop = false;

    //pthread_attr_t attr;

    //pthread_attr_init(&attr);
    /* We don't need to join this thread */
    //pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    //pthread_mutex_init(&mutex, NULL);

    //pthread_cond_init(&cond, NULL);


    mutex = PTHREAD_MUTEX_INITIALIZER;

    cond = PTHREAD_COND_INITIALIZER;


    socketfd = -1;

//    pthread_mutex_lock( &mutex );
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
    bool available;

    pthread_mutex_lock( &mutex );

    available = m_isAvailable;

    pthread_mutex_unlock( &mutex );

    return available;
}

void thread::setAvailable(bool available)
{
    m_isAvailable = available;
}

bool thread::start(int socketfd)
{

    pthread_mutex_lock( &mutex );

    m_isAvailable = false;

    this->socketfd = socketfd;

    if( pthread_cond_signal(&cond) != 0){

        perror("pthread_cond_signal() error");
        //exit(0);
    }

    pthread_mutex_unlock( &mutex );

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


void thread::process()
{
    char buffer[2048];

    cout << "command count: " << ++m_request_count << endl;

    int length = recv(socketfd, buffer, sizeof(buffer), 0 );
    if (length > 0){
       //printf("Received message: %s\n", buffer);

        //start to parse the xml request;

        Authorise *auth = new Authorise;

        this->parseRequests(buffer, length, auth);


        Paypal paypal;

        paypal.sendRequest(auth->toString());



        delete auth;


       sprintf(buffer, "ok");

       send(socketfd, buffer, 3, 0);

    }else{
        cout << errno << endl;
        cout << "recv error detected" << endl;
    }


    if(socketfd != -1){
        close(socketfd);
        socketfd = -1;
    }
    m_isAvailable = true;
}


/**
  * Parse xml request, generate the paypal request and red request
  */
int thread::parseRequests(char *xml, long size, Authorise *auth)
{
    cout << xml << endl;

    xmlDoc *doc = xmlReadMemory(xml,size,"",NULL,0);
    if (doc == NULL){
          cout << "error: could not parse file" << endl;
          return -1;
    }

    cout << "------------------------" << endl;

    xmlNode *cur_node = xmlDocGetRootElement(doc);
    if(cur_node == NULL){
        cout << "error: could not get root element" << endl;
        return -1;
    }

    if(!xmlStrcmp(cur_node->name, (const xmlChar *)"root")){    //get root node
        cur_node = cur_node->xmlChildrenNode;

        string expyear, expmonth;

        while(cur_node){
            if (cur_node->type == XML_ELEMENT_NODE) {
                xmlChar *value = NULL;

                if(xmlStrcmp(cur_node->name, (const xmlChar *)"shipping") &&
                        xmlStrcmp(cur_node->name, (const xmlChar *)"billing") &&
                        xmlStrcmp(cur_node->name, (const xmlChar *)"payment")
                        ){
                        value = xmlNodeGetContent(cur_node);
                        char *fieldName = NULL;

                        if(!xmlStrcmp(cur_node->name, (const xmlChar *)"amount")){
                            fieldName = "amt";
                        }else{
                            fieldName = (char *)cur_node->name;
                        }

                        if(fieldName) auth->addParam((const char *)fieldName, (const char *)value);
                        xmlFreeFunc(value);
                }else{
                    xmlNode *sub_node = cur_node->xmlChildrenNode;
                    while(sub_node){
                        if (cur_node->type == XML_ELEMENT_NODE) {
                            char *fieldName = NULL;

                            string paramName = (char *)sub_node->name;

                            value = xmlNodeGetContent(sub_node);

                            if(!xmlStrcmp(cur_node->name, (const xmlChar *)"shipping")){
                                paramName = "billto" + paramName;
                                fieldName = (char *)paramName.c_str();
                            }else if(!xmlStrcmp(cur_node->name, (const xmlChar *)"billing")){
                                paramName = "shipto" + paramName;
                                fieldName = (char *)paramName.c_str();
                            }else if(!xmlStrcmp(cur_node->name, (const xmlChar *)"payment")){
                                if(!xmlStrcmp(sub_node->name, (const xmlChar *)"expyear")){
                                    expyear = (char *)value;
                                    fieldName = NULL;
                                }else if(!xmlStrcmp(sub_node->name, (const xmlChar *)"expmonth")){
                                     expmonth = (char *)value;
                                     fieldName = NULL;
                                }else{
                                     fieldName = (char *)sub_node->name;
                                }
                            }


                            if(fieldName)  auth->addParam(paramName, (const char *)value);
                            xmlFreeFunc(value);

                        }
                        sub_node = sub_node->next;
                    }
                }
            }
            cur_node = cur_node->next;
        }
        char expdate[32];
        sprintf(expdate, "%s%s", expmonth.c_str(), expyear.c_str());
        auth->addParam("expdate", expdate);
    }else{
        return -1;
    }

    return 0;
}

//work function, thread

void *thread::callback(void *obj)
{
    thread *p = (thread *)obj;

    while(!p->m_stop){
        pthread_mutex_lock( &p->mutex );

        while(p->socketfd == -1){
            pthread_cond_wait (&p->cond, &p->mutex);
        }

        pthread_mutex_unlock( &p->mutex );

//        cout << "!thread start>" << endl;

        p->process();


//        while(!request_queue->isEmpty()){
//            request_node node = request_queue->getAndRemoveRequestNode();

//            pthread_mutex_lock( &p->mutex );

//            p->setAvailable(false);

//            p->socketfd = node.socketfd;

//            pthread_mutex_unlock( &p->mutex );

//            p->process();

//            cout << request_queue->count() << " left" << endl;

//            break;
//        }


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


