#include <iostream>

#include <stdio.h>

#include "param.h"

#define PAYPAL_USER "TheIconicTest"

#define PAYPAL_PASSWORD "Rocket1"

#define PAYPAL_MERCHANT "TheIconicTest"

#define PAYPAL_PARTNER "VSA"


Param::Param()
{
    this->addParam("PARTNER", PAYPAL_PARTNER);
    this->addParam("USER", PAYPAL_USER);
    this->addParam("PWD", PAYPAL_PASSWORD);
    this->addParam("VENDOR", PAYPAL_MERCHANT);
}

void Param::addParam(string paramName, string paramvalue)
{
    this->params.push_back(
        paramNode(paramName, paramvalue)
    );
}


string Param::toString()
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



    //returnStr = "AMT=57.25&CURRENCY=AUD&CUSTREF=200279815&ORDERID=200279815&COMMENT1=200279815&COMMENT2=40.00&ACCT=5555555555554444&EXPDATE=0214&CVV2=234&BILLTOFIRSTNAME=Albee&BILLTOLASTNAME=&BILLTOSTREET=Assassinate&BILLTOCITY=Surry Hills&BILLTOZIP=2010&BILLTOCOUNTRY=AU&BILLTOEMAIL=wangfei0001@hotmail.com&SHIPTOFIRSTNAME=Jacky&SHIPTOLASTNAME=wang&SHIPTOSTREET=84 Marry Street (Internal)&SHIPTOCITY=Surry Hills&SHIPTOZIP=2010&SHIPTOCOUNTRY=AU&SHIPTOEMAIL=wangfei0001@hotmail.com&VERBOSITY=HIGH&TRXTYPE=A&PARTNER=VSA&PWD=Rocket1&USER=TheIconicTest&VENDOR=TheIconicTest&TENDER=C";

    return returnStr;
}
