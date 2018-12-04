#include "administrator.h"

Administrator Administrator::readFromFile(ifstream& file)
{
    ID id;
    char password[32];
    id = ID::getFromFile(file);
    file.read(password,32);

    return Administrator(id, password);
}

void Administrator::writeToFile(ofstream& _file, Administrator element)
{
    _file.write(element._id.id, sizeof(ID));
    _file.write(element._password, sizeof(element._password));
}
