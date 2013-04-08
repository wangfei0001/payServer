#ifndef PAYPAL_H
#define PAYPAL_H

#include <string>

#include <curl/curl.h>

#include "data/response.h"

#include "data/authorise.h"

using namespace std;

class Paypal
{
public:
    Paypal();

    void test();


protected:
    Response *sendRequest(string param);

    string certificationId;

    string RandomString(unsigned int len);

    string MD5(string str);

    void getHeader(struct curl_slist **pheaders);
};

#endif // PAYPAL_H
