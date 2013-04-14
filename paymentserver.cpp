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

    //lisging socket
    socketfd = this->createListeningSocket();
    if(!socketfd){
        //thread exception, error handle

    }


    //check socket connection

    struct sockaddr_in clientaddr;
    unsigned int clientaddrlen = 0;

    long count2 = 0;

    while (1){
       unsigned int connectfd = accept(socketfd, (struct sockaddr *) &clientaddr, &clientaddrlen);
       if(connectfd == -1){
           cout << "accept error " << endl;
           //error handle function!
           exit(-1);
       }else{
//           printf("A client has connected %d\n", connectfd);

           thread *p_thread = pool->getSpareThread();

           if(p_thread){
//               cout << "find a spare thread:" << p_thread << " index:" << p_thread->id << endl;

               p_thread->start(connectfd);

           }else{
               request_node rnode;
               rnode.socketfd = connectfd;
               request_queue->addRequestNode(rnode);

               cout << "no spare thread is available now. have " << request_queue->count() << " nodes Threads:" << DEFAULT_THREAD_COUNT << endl;

           }
       }

//       close(connectfd);
       usleep(1);
   }





    close(socketfd);
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
