#include "seminar.h"

Seminar Seminar::readFromFile(ifstream& file)
{
    ResCode code;
    Status status;
    ID coordinatorID;
    ID speakerID;
    Date date;


    code = getRCFromFile(file);
    file.read((char*)(&status), sizeof(Status));
    coordinatorID = ID::getFromFile(file);
    speakerID = ID::getFromFile(file);

    unsigned int seats;
    file.read((char*)(&seats), sizeof(unsigned int));
    vector<ID> attendants;

    unsigned int numAttendants;
    file.read((char*)(&numAttendants), sizeof(unsigned int));
    for (unsigned int i=0; i<numAttendants; i++)
    {
        ID attendantID;
        attendantID = ID::getFromFile(file);
        attendants.push_back(attendantID);
    }

    date = Date::getFromFile(file);

    Seminar seminar(code,coordinatorID, speakerID, seats, date, status);

    seminar._enrolled.setAttendants(attendants);
    seminar._enrolled.setSeats(seats);

    return seminar;
}

void Seminar::writeToFile(ofstream& _file, Seminar element)
{
    _file.write(element._code.full, sizeof(ResCode));
    _file.write(reinterpret_cast<char*>(&element._status), sizeof(Status));
    _file.write(element._coordinatorID.id, sizeof(ID));
    _file.write(element._speakerID.id, sizeof(ID));

    unsigned int seats = element._enrolled.getSeats();
    _file.write(reinterpret_cast<char*>(&seats), sizeof (unsigned int));
    const vector<ID>& attendants = element._enrolled.getAttendanceList();
    unsigned int numAttendants =attendants.size();
    _file.write(reinterpret_cast<char*>(&numAttendants), sizeof(unsigned int));
    for(unsigned int i=0; i<numAttendants; i++)
    {
        _file.write(attendants[i].id, sizeof(ID));
    }

    Date::writeToFile(_file, element._date);

}
