#include "param.h"




Param::Param()
{

}

void Param::addParam(string paramName, string paramvalue)
{
    this->params.push_back(
        paramNode(paramName, paramvalue)
    );
}



