#include "degree.h"

Degree Degree::readFromFile(ifstream& file)
{
    ResCode code;


    code = ResCode::getFromFile(file);                          //Read code

    unsigned int stringsize = 0;

    file.read((char*)(&stringsize), sizeof(unsigned int));      //Read size of name
    string name(stringsize, '\0');
    file.read(&name[0], stringsize);                            //Read name

    Degree degree = Degree(code, name);

    return degree;
}

void Degree::writeToFile(ofstream& _file, Degree element)
{
    _file.write(element._code.code, sizeof(ResCode));                           //Write code

    unsigned int stringsize = element._name.size();                             //Write size of name
    _file.write(reinterpret_cast<char*>(&stringsize), sizeof(unsigned int));
    _file.write(element._name.c_str(), stringsize);                             //Write name
}
