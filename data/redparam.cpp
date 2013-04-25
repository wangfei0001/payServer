#include "redparam.h"

#define DIV_NUM 'ICONIC'

#define S_KEY_ID "161"

#define EBT_NAME "000243000001"

#define EBT_SERVICE "N"

#define USER_ID "ICONIC"

#define ACT_CD "OA"

#define REQ_TYPE_CD "M"

#define CURR_CD "AUD"

#define EBWEBSITE "www.theiconic.com.au"

#define SHIP_TYPE_CD "S"

RedParam::RedParam()
{
    //fill the default parameters

   // this->addParam("DIV_NUM", DIV_NUM);
    this->addParam("S_KEY_ID", S_KEY_ID);
    this->addParam("EBT_NAME", EBT_NAME);
    this->addParam("EBT_SERVICE", EBT_SERVICE);
    this->addParam("ACT_CD", ACT_CD);
    this->addParam("REQ_TYPE_CD", REQ_TYPE_CD);
    this->addParam("USER_ID", USER_ID);
    this->addParam("CURR_CD", CURR_CD);
    this->addParam("ebWEBSITE", EBWEBSITE);
    this->addParam("SHIP_TYPE_CD", SHIP_TYPE_CD);

}

/*
ORD_ID
AMT
MOP_TYPE_CD
ACCT_NUM
CARD_EXP_DT
CUST_ID
            'CUST_FNAME'            =>              $billingAddress->getFirstName(),
             CUST_MNAME
            'CUST_LNAME'            =>              $billingAddress->getLastName(),
            'CUST_BIRTH_DT'         =>              $customer->getBirthday(),
            'CUST_EMAIL'            =>              $customer->getEmail(),
            'CUST_ADDR1'            =>              $billingAddress->getAddress1(),
            'CUST_ADDR2'            =>              $billingAddress->getAddress2(),
            'CUST_CITY'             =>              $billingAddress->getCity(),
            'CUST_POSTAL_CD'        =>              $billingAddress->getPostcode(),
            'CUST_STPR_CD'          =>              $billingRegionCode,
            'CUST_CNTRY_CD'         =>              $billingCountryName,
            'CUST_HOME_PHONE'       =>              $billingPhoneNumber,
            'CUST_IP_ADDR'          =>              $order->getIp(),
            'EBT_PREVCUST'          =>              $customer->getIsGuest()?'N':'Y',
            'SHIP_FNAME'            =>              $shippingAddress->getFirstName(),
            'SHIP_LNAME'            =>              $shippingAddress->getLastName(),
            'SHIP_ADDR1'            =>              $shippingAddress->getAddress1(),
            'SHIP_ADDR2'            =>              $shippingAddress->getAddress2(),
            'SHIP_CITY'             =>              $shippingAddress->getCity(),
            'SHIP_POSTAL_CD'        =>              $shippingAddress->getPostcode(),
            'SHIP_STPR_CD'          =>              $regionCode,
            'SHIP_HOME_PHONE'       =>              $phoneNumber,
            'SHIP_CNTRY_CD'         =>              $countryName,

*/

string RedParam::toString()
{
    string retuStr = "";

    retuStr = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>";
    retuStr += "<SOAP-ENV:Envelope xmlns:SOAP-ENV=\"http://schemas.xmlsoap.org/soap/envelope/\" xmlns:SOAP-ENC=\"http://schemas.xmlsoap.org/soap/encoding/\"";
    retuStr += "xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"";
    retuStr += "xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\"";
    retuStr += "xmlns:ns=\"urn:lpsoap\">";
    retuStr += "<SOAP-ENV:Body SOAPENV:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\">";
    retuStr += "<ns:lpcall>";
    retuStr += "<ReqArray>";

    for(unsigned int i = 0; i < this->params.size(); i++){
        retuStr += "<item>";
        retuStr += "<key>" + params[i].Name + "</key>";
        retuStr += "<val>" + params[i].Value + "</val>";
        retuStr += "</item>";
    }


    retuStr += "</ReqArray>";
    retuStr += "</ns:lpcall>";
    retuStr += "</SOAP-ENV:Body>";
    retuStr += "</SOAP-ENV:Envelope>";

    return retuStr;
}
