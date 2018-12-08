#include "fdp.h"

FDP FDP::readFromFile(ifstream& file)
{
    ResCode code;
    Status status;
    ResCode degree;
    ID studentID;
    ID tutorID;
    ID cotutorID;

    code = getRCFromFile(file);
    file.read((char*)(&status), sizeof(Status));
    degree = getRCFromFile(file);
    studentID = ID::getFromFile(file);
    tutorID = ID::getFromFile(file);
    cotutorID = ID::getFromFile(file);

    FDP fdp = FDP(code, degree,studentID, tutorID, cotutorID, status);

    return fdp;
}

void FDP::writeToFile(ofstream& _file, FDP element)
{
    _file.write(element._code.full, sizeof(ResCode));
    _file.write(reinterpret_cast<char*>(&element._status), sizeof(Status));
    _file.write(element._degree.full, sizeof(ResCode));
    _file.write(element._studentID.id, sizeof (ID));
    _file.write(element._tutorID.id, sizeof (ID));
    _file.write(element._cotutorID.id, sizeof (ID));
}
