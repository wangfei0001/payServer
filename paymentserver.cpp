#include <iostream>

#include <string.h>

#include <stdio.h>

#include <sys/socket.h> // Needed for the socket functions

#include <arpa/inet.h>

#include <netdb.h>      // Needed for the socket functions

#include <errno.h>

#include <fstream>

#include <libxml/parser.h>

#include "workerthread.h"

#include "paymentserver.h"

#include "rqueue.h"


using namespace std;

rqueue *request_queue = new rqueue();

PaymentServer::PaymentServer()
{
    pool = new ThreadPool();

    cout << "We have created " << pool->getThreadsCount() << " threads!" << endl;
}


PaymentServer::~PaymentServer()
{

    delete pool;

    cout << "Delete threads pool!" << endl;
}



void PaymentServer::start()
{
    //lisging socket
    socketfd = this->createListeningSocket();
    if(!socketfd){
        //thread exception, error handle

    }

    workerthread *worker = new workerthread();

    worker->init(pool);


    //check socket connection

    struct sockaddr_in clientaddr;
    unsigned int clientaddrlen = 0;

    long count2 = 0;

    while (1){
       unsigned int connectfd = accept(socketfd, (struct sockaddr *) &clientaddr, &clientaddrlen);
       if(connectfd == -1){
           cout << "accept error " << endl;
           //error handle function!
       }else{
//           printf("A client has connected %d\n", connectfd);

           thread *p_thread = pool->getSpareThread();

           if(p_thread){
//               cout << "find a spare thread:" << p_thread << " index:" << p_thread->id << endl;

               p_thread->socketfd = connectfd;

               p_thread->start();

           }else{
               cout << "no spare thread is available now. maxinum threads: " << DEFAULT_THREAD_COUNT << endl;

               request_node rnode;
               rnode.socketfd = connectfd;
               request_queue->addRequestNode(rnode);

               cout << "have " << request_queue->count() << " nodes" << endl;
           }
       }

//       close(connectfd);
       usleep(1);
   }


#if 0
    Authorise *auth = new Authorise;


    ifstream myfile("request.xml");

    char *memblock;

    cout << "opened?" << myfile.is_open() << endl;

    myfile.seekg (0, ios::beg);
    long begin = myfile.tellg();
    myfile.seekg (0, ios::end);
    long end = myfile.tellg();

    long size = end - begin;

    memblock = new char[size];
//    cout << "file length=" <<  size << endl;
    myfile.seekg (0, ios::beg);
    myfile.read (memblock, size);

    this->parseRequests(memblock, size, auth);

    delete memblock;

    myfile.close();




    delete auth;


    sleep(5000000);

#endif


    close(socketfd);
}



/**
  * Parse xml request, generate the paypal request and red request
  */
int PaymentServer::parseRequests(char *xml, long size, Authorise *auth)
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

        while(cur_node){
            if (cur_node->type == XML_ELEMENT_NODE) {
                xmlChar *value = NULL;

                if(xmlStrcmp(cur_node->name, (const xmlChar *)"shipping") &&
                        xmlStrcmp(cur_node->name, (const xmlChar *)"billing") &&
                        xmlStrcmp(cur_node->name, (const xmlChar *)"payment")
                        ){

                        value = xmlNodeGetContent(cur_node);
                        auth->addParam((const char *)cur_node->name, (const char *)value);
                        xmlFreeFunc(value);
                }else{
                    xmlNode *sub_node = cur_node->xmlChildrenNode;
                    while(sub_node){
                        if (cur_node->type == XML_ELEMENT_NODE) {

                            string paramName = (char *)sub_node->name;

                            if(!xmlStrcmp(cur_node->name, (const xmlChar *)"shipping"))
                                paramName = "billto" + paramName;
                            else if(!xmlStrcmp(cur_node->name, (const xmlChar *)"billing"))
                                paramName = "shipto" + paramName;

                            value = xmlNodeGetContent(sub_node);
                            auth->addParam(paramName, (const char *)value);
                            xmlFreeFunc(value);

                        }
                        sub_node = sub_node->next;
                    }
                }
            }
            cur_node = cur_node->next;
        }
    }else{
        return -1;
    }

    cout << "------------------------" << endl;

    return 0;
}

int PaymentServer::createListeningSocket()
{
    int socketfd ; // The socket descripter
    //struct addrinfo host_info;       // The struct that getaddrinfo() fills up with data.
    struct addrinfo host_info_list; // Pointer to the

    memset(&host_info_list, 0, sizeof host_info_list);

    host_info_list.ai_family = AF_INET;     // IP version not specified. Can be both.
    host_info_list.ai_socktype = SOCK_STREAM; //
    host_info_list.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
    host_info_list.ai_protocol = 0;

    cout << "start listening" << endl;

    socketfd = socket(host_info_list.ai_family, host_info_list.ai_socktype,
    host_info_list.ai_protocol);
    if (socketfd == -1){
        std::cout << "create listening socket error code:" << strerror(errno) << endl;
        return 0;
    }

    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof serv_addr);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(6666);
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(socketfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0){
        std::cout << "ERROR on binding" << endl;
        return 0;
    }
    if(listen(socketfd, 64) < 0){
        cout << "listen error" << endl;
        return 0;
    }

    cout << "@@@@@Start to listen the clients' requests!@@@@@" << endl;

    return socketfd;
}
