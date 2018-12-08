#include "professor.h"

Professor Professor::readFromFile(ifstream& file)
{
    ID id;
    char password[32];
    id = ID::getFromFile(file);
    file.read(password,32);

    return Professor(id, password);
}

void Professor::writeToFile(ofstream& _file, Professor element)
{
    _file.write(element._id.id, sizeof(ID));
    _file.write(element._password, sizeof(element._password));
}
