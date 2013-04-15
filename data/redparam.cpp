#include "redparam.h"

RedParam::RedParam()
{
}


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
