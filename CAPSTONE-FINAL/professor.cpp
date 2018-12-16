#include "professor.h"

Professor Professor::readFromFile(ifstream& file)
{
    ID id;
    char password[32];
    id = ID::getFromFile(file);  // Read ID
    file.read(password,32);      // Read password

    return Professor(id, password);
}

void Professor::writeToFile(ofstream& _file, const Professor& element)
{
    _file.write(element._id.id, sizeof(ID));                    //Write ID
    _file.write(element._password, sizeof(element._password));  //Write password
}
