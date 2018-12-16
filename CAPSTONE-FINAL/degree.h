#ifndef DEGREE_H
#define DEGREE_H
#include <iostream>
#include <cstring>
#include "commons.h"
#include "resource.h"


using namespace std;

class Degree : public Resource
{
public:
    Degree(const ResCode code, string name) : Resource(code), _name(name) {}
    void setName(const string name){ _name = name; }
    string getName () { return _name; }

    static Degree readFromFile(ifstream& file);
    static void writeToFile(ofstream& _file, Degree element);

private:
    string _name;
};

#endif // DEGREE_H
