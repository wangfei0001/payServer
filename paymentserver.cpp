#include <iostream>

#include <string.h>

#include <stdio.h>

#include <sys/socket.h> // Needed for the socket functions

#include <arpa/inet.h>

#include <netdb.h>      // Needed for the socket functions

#include <errno.h>

#include <fstream>

#include <libxml/parser.h>


#include "paymentserver.h"

using namespace std;

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

    //pool->run();
    //check socket connection

//    struct sockaddr_in clientaddr;
//    unsigned int clientaddrlen = 0;

//    while (1){
//           int connectfd = accept(socketfd, (struct sockaddr *) &clientaddr, &clientaddrlen);
//           char buffer[2048];

//           printf("A client has connected %d\n", connectfd);
//           if (recv(connectfd, buffer, sizeof(buffer), 0 ) > 0){
//               printf("Received message: %s\n", buffer);

//           }
//           close(connectfd);
//       }

    cout << "hello" << endl;


    ifstream myfile("request.xml");

    char *memblock;

    cout << "opened?" << myfile.is_open() << endl;

    myfile.seekg (0, ios::beg);
    long begin = myfile.tellg();
    myfile.seekg (0, ios::end);
    long end = myfile.tellg();

    long size = end - begin;

    memblock = new char[size];
    cout << "file length=" <<  size << endl;
    myfile.seekg (0, ios::beg);
    myfile.read (memblock, size);

    this->parseRequests(memblock, size);

    delete memblock;

    myfile.close();



    sleep(5000000);

    close(socketfd);
}

static void
print_element_names(xmlNode * a_node)
{
    xmlNode *cur_node = NULL;
    xmlChar *value = NULL;

    for (cur_node = a_node; cur_node; cur_node = cur_node->next) {
        if (cur_node->type == XML_ELEMENT_NODE) {
            printf("node type: Element, name: [%s]\n", cur_node->name);
        }

        if (cur_node->type == XML_TEXT_NODE) {
            value = xmlNodeGetContent(cur_node);
            printf("node type: Element, value: [%s]\n", (char*)value);
            xmlFreeFunc(value);
        }


        print_element_names(cur_node->children);
    }
}

int PaymentServer::parseRequests(char *xml, long size)
{
    cout << xml << endl;

    xmlDoc *doc;

    doc = xmlReadMemory(xml,size,"",NULL,0);
    if (doc == NULL){
          cout << "error: could not parse file" << endl;
          return -1;
    }
    print_element_names(xmlDocGetRootElement(doc));

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
    serv_addr.sin_port = htons(6667);
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
