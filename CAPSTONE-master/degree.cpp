#include "degree.h"

Degree Degree::readFromFile(ifstream& file)
{
    ResCode code;


    code = getRCFromFile(file);

    unsigned int stringsize = 0;

    file.read((char*)(&stringsize), sizeof(unsigned int));
    string name(stringsize, '\0');
    file.read(&name[0], stringsize);

    Degree degree = Degree(code, name);

    return degree;
}

void Degree::writeToFile(ofstream& _file, Degree element)
{
    _file.write(element._code.full, sizeof(ResCode));

    unsigned int stringsize = element._name.size();
    _file.write(reinterpret_cast<char*>(&stringsize), sizeof(unsigned int));
    _file.write(element._name.c_str(), stringsize);
}
