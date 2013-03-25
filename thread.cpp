#include <iostream>

#include <curl/curl.h>

#include "thread.h"


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

//        CURL *curl;
//        CURLcode res;
//        struct curl_slist *headers=NULL; // init to NULL is important
//        headers = curl_slist_append(headers, "Accept: application/json");

        cout << "start to grab->" << i++ << endl;
//        curl = curl_easy_init();
//        if(curl) {
//            //curl_easy_setopt(curl, CURLOPT_URL, "http://web.com/api/json/123");

////            curl_easy_setopt(curl, CURLOPT_URL, "http://web.com/pages/123.html");//this returns entire webpage
////            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
////            //curl_easy_setopt(curl, CURLOPT_RETURNTRANSFER, true);
////            res = curl_easy_perform(curl);

////            if(CURLE_OK == res) {
////                char *ct;
////                // ask for the content-type
////                res = curl_easy_getinfo(curl, CURLINFO_CONTENT_TYPE, &ct);
////                if((CURLE_OK == res) && ct)
////                    printf("We received Content-Type: %s\n", ct);
////            }
//        }else{
//            cout << "curl error" << endl;
//        }
//        // always cleanup
//        curl_easy_cleanup(curl);
        cout << "end!" << endl;
        //break;
        sleep(1);
    }
    cout << "thread end" << endl;

    return obj;
}
