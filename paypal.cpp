#include "paypal.h"

#include <stdlib.h>

#include <string.h>

#include <iostream> //can be removed

#include "data/param.h"

#include "data/authorise.h"


extern "C"{
    #include "md5/md5.h"
}

#define PAYPAL_SERVER_URL "https://pilot-payflowpro.paypal.com/transaction"




void *callback(void* obj);

size_t callback_func(void *ptr, size_t size, size_t count, void *stream);

Paypal::Paypal()
{
    this->certificationId = "13fda2433fc2123d8b191d2d011b7fdc";
}


void Paypal::test()
{
    Authorise *auth = new Authorise();

    char buffer[255];

    srand(time(0));
    sprintf(buffer, "%d", rand());

    auth->addParam("amt", "0.01");
    auth->addParam("acct", "5555555555554444");
    auth->addParam("cvv2", "123");
    auth->addParam("expdate", "122013");

    auth->addParam("comment1", buffer);
    auth->addParam("custref", buffer);
    auth->addParam("orderid", buffer);

    auth->addParam("billtocity","Sydney");
    auth->addParam("billtocountry","AU");
    auth->addParam("billtoemail","wangfei001@hotmail.com");
    auth->addParam("billtofirstname","fei");
    auth->addParam("billtolastname","wang");
    auth->addParam("billtostate","NSW");
    auth->addParam("billtostreet","2/23 Barry ST");
    auth->addParam("billtozip","2089");


    auth->addParam("shiptocity","Sydney");
    auth->addParam("shiptocountry","AU");
    auth->addParam("shiptoemail","wangfei001@hotmail.com");
    auth->addParam("shiptofirstname","fei");
    auth->addParam("shiptolastname","wang");
    auth->addParam("shiptostate","NSW");
    auth->addParam("shiptostreet","2/23 Barry ST");
    auth->addParam("shiptozip","2089");

    cout << auth->toString() << endl;
    this->sendRequest(auth->toString());

    delete auth;
}



string Paypal::RandomString(unsigned int len)
{
   srand(time(0));
   string str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
   int pos;
   while(str.size() != len) {
    pos = ((rand() % (str.size() - 1)));
    str.erase (pos, 1);
   }
   return str;
}

size_t callback_func(void *ptr, size_t size, size_t count, void *stream)
{
      /* ptr - your string variable.
      stream - data chuck you received */
    ((std::string*)stream)->append((char*)ptr, size * count);
    return size * count;
}


Response *Paypal::sendRequest(string param)
{

    CURL *curl;
    CURLcode res;
    string readBuffer;

    curl = curl_easy_init();
    if(curl) {
        //get header...
        struct curl_slist *headers = NULL;

        this->getHeader(&headers);

        curl_easy_setopt(curl, CURLOPT_URL, PAYPAL_SERVER_URL);

        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, param.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback_func);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
//        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
        res = curl_easy_perform(curl);

        if(CURLE_OK == res) {

            cout << "->" << param.c_str() << endl;
            cout << "<-" << readBuffer << endl;
        }else{

            cout << curl_easy_strerror(res) << endl;
        }

        curl_easy_cleanup(curl);

        curl_slist_free_all(headers);
    }
    return (Response *)0;
}

/**
  * Md5 encrypt the string
  */
string Paypal::MD5(string str)
{
    md5_t md5;

    unsigned char sig[MD5_SIZE];

    char		buffer[4096];

    memcpy(buffer,str.c_str(),str.size());

    md5_init(&md5);

    md5_process(&md5, buffer, str.size());

    md5_finish(&md5, sig);

    md5_sig_to_string(sig, buffer, sizeof(buffer));

    string returnStr = buffer;

    return returnStr;
}


/**
  * Generate the header
  */
void Paypal::getHeader(struct curl_slist **pheaders)
{
    struct curl_slist *headers = *pheaders;

    char buffer[1000];

    string requestIdStr = this->RandomString(10);

    requestIdStr = this->MD5(requestIdStr);

    headers = curl_slist_append(headers, "Content-Type: text/namevalue");
    headers = curl_slist_append(headers, "X-VPS-Timeout: 60");
    headers = curl_slist_append(headers, "X-VPS-VIT-OS-Name: Linux");
    headers = curl_slist_append(headers, "X-VPS-VIT-OS-Version: RHEL 4");
    headers = curl_slist_append(headers, "X-VPS-VIT-Client-Type: PHP/cURL");
    headers = curl_slist_append(headers, "X-VPS-VIT-Client-Version: 0.01");
    headers = curl_slist_append(headers, "X-VPS-VIT-Client-Architecture: x86");

    sprintf(buffer, "X-VPS-VIT-Client-Certification-Id: %s", this->certificationId.c_str());
    headers = curl_slist_append(headers, buffer);
    headers = curl_slist_append(headers, "X-VPS-VIT-Integration-Product: TheIconic Payment Client");
    headers = curl_slist_append(headers, "X-VPS-VIT-Integration-Version: 0.01");
    sprintf(buffer, "X-VPS-Request-ID: %s", requestIdStr.c_str());
    headers = curl_slist_append(headers, buffer);

}
