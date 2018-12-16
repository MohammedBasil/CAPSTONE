#include "administrator.h"

Administrator Administrator::readFromFile(ifstream& file)
{
    ID id;
    char password[32];
    id = ID::getFromFile(file);  // Read ID
    file.read(password,32);      // Read password

    return Administrator(id, password);
}

void Administrator::writeToFile(ofstream& _file, const Administrator& element)
{
    _file.write(element._id.id, sizeof(ID));                    // Write ID
    _file.write(element._password, sizeof(element._password));  // Write password
}
