#ifndef DEGREE_H
#define DEGREE_H
#include <iostream>
#include <cstring>
#include "commons.h"


using namespace std;

class Degree
{
public:
    Degree(){_name="";}
    void setname(const string name){_name=name;}
private:
    string _name;

};

#endif // DEGREE_H
