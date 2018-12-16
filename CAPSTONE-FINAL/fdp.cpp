#include "fdp.h"

FDP FDP::readFromFile(ifstream& file)
{
    ResCode code;
    Status status;
    ResCode degree;
    ID studentID;
    ID tutorID;
    ID cotutorID;

    code = ResCode::getFromFile(file);              // Read code
    file.read((char*)(&status), sizeof(Status));    // Read status
    degree = ResCode::getFromFile(file);            // Read degree
    studentID = ID::getFromFile(file);              // Read student ID
    tutorID = ID::getFromFile(file);                // Read tutor ID
    cotutorID = ID::getFromFile(file);              // Read cotutor ID

    FDP fdp = FDP(code, degree,studentID, tutorID, cotutorID, status);

    return fdp;
}

void FDP::writeToFile(ofstream& _file, FDP element)
{
    _file.write(element._code.code, sizeof(ResCode));                           // Write code
    _file.write(reinterpret_cast<char*>(&element._status), sizeof(Status));     // Write status
    _file.write(element._degree.code, sizeof(ResCode));                         // Write degree
    _file.write(element._studentID.id, sizeof (ID));                            // Write student ID
    _file.write(element._tutorID.id, sizeof (ID));                              // Write tutor ID
    _file.write(element._cotutorID.id, sizeof (ID));                            // Write cotutor ID
}
