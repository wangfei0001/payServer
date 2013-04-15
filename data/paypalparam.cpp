#include "paypalparam.h"

#define PAYPAL_USER "TheIconicTest"

#define PAYPAL_PASSWORD "Rocket1"

#define PAYPAL_MERCHANT "TheIconicTest"

#define PAYPAL_PARTNER "VSA"

PaypalParam::PaypalParam()
{
    this->addParam("PARTNER", PAYPAL_PARTNER);
    this->addParam("USER", PAYPAL_USER);
    this->addParam("PWD", PAYPAL_PASSWORD);
    this->addParam("VENDOR", PAYPAL_MERCHANT);
}


string PaypalParam::toString()
{
    string returnStr = "";

    for(unsigned int i = 0; i < this->params.size(); i++){
        if(params[i].Value.find_first_of("&") != string::npos || params[i].Value.find_first_of("=") != string::npos){
            char buffer[255];
            sprintf(buffer, "%d", params[i].Value.size());
            returnStr += params[i].Name + "[" + buffer + "]=";
        }else{
            returnStr += params[i].Name + "=";
        }
        returnStr += params[i].Value;

        if(i != params.size()-1) returnStr += "&";
    }

    return returnStr;
}
