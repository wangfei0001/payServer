#include <curl/curl.h>

#include <iostream>

#include "red.h"

#define REDURL "https://62.254.196.34:18081"

#define REDURLBACKUP "https://62.254.196.34:18082"

ReD::ReD()
{
}

size_t red_callback_func(void *ptr, size_t size, size_t count, void *stream)
{
      /* ptr - your string variable.
      stream - data chuck you received */
    ((std::string*)stream)->append((char*)ptr, size * count);
    return size * count;
}

void *ReD::sendRequest(string param)
{

    CURL *curl;
    CURLcode res;
    string readBuffer;

    curl = curl_easy_init();
    if(curl) {
        //get header...
        struct curl_slist *headers = NULL;

        //this->getHeader(&headers);

        curl_easy_setopt(curl, CURLOPT_URL, REDURL);

        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, param.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, red_callback_func);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_DNS_USE_GLOBAL_CACHE, 0);
        curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);

//        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);

        res = curl_easy_perform(curl);

        if(CURLE_OK == res) {

            cout << "->" << param.c_str() << endl;
            cout << "<-" << readBuffer << endl;
        }else{

            cout << curl_easy_strerror(res) << endl;
        }

        curl_slist_free_all(headers);

        curl_easy_cleanup(curl);
    }

    return (void *)0;
}
