#ifndef PARAM_H
#define PARAM_H

#include <string>

#include <vector>



using namespace std;

struct paramNode{
    string Name;
    string Value;

    paramNode(string _name,string _value):Name(_name),Value(_value){};
};

class Param
{



protected:
    vector<paramNode> params;


public:
    Param();

    void addParam(string paramName, string paramvalue);

    string toString();
};

#endif // PARAM_H
