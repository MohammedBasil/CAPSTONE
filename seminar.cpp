#include "seminar.h"

bool Seminar::isEnrolled(const ID id)
{
	if (_coordinatorID.Equals(id) || _speakerID.Equals(id))
	{
		return true;
	}

	const vector<ID>& students = _enrolled.getAttendanceList();
	for (size_t i = 0; i < students.size(); i++)
	{
		if (students[i].Equals(id))
		{
			return true;
		}
	}
	return false;
}

Seminar Seminar::readFromFile(ifstream& file)
{
    ResCode code;
    Status status;
    ID coordinatorID;
    ID speakerID;
    Date date;


    code = ResCode::getFromFile(file);                                  // Read code
    file.read((char*)(&status), sizeof(Status));                        // Read status
    coordinatorID = ID::getFromFile(file);                              // Read coordinator
    speakerID = ID::getFromFile(file);                                  // Read speaker

    unsigned int seats;                                                 // Read number of seats
    file.read((char*)(&seats), sizeof(unsigned int));
    vector<ID> attendants;

    unsigned int numAttendants;
    file.read((char*)(&numAttendants), sizeof(unsigned int));           // Read number of attendants
    for (unsigned int i=0; i<numAttendants; i++)
    {
        ID attendantID;                                                 // Read each attendant
        attendantID = ID::getFromFile(file);
        attendants.push_back(attendantID);
    }

    date = Date::getFromFile(file);                                     // Read date

    Seminar seminar(code,coordinatorID, speakerID, seats, date, status);

    seminar._enrolled.setAttendants(attendants);
    seminar._enrolled.setSeats(seats);

    return seminar;
}

void Seminar::writeToFile(ofstream& _file, Seminar element)
{
    _file.write(element._code.code, sizeof(ResCode));                               // Write code
    _file.write(reinterpret_cast<char*>(&element._status), sizeof(Status));         // Write status
    _file.write(element._coordinatorID.id, sizeof(ID));                             // Write coordinator
    _file.write(element._speakerID.id, sizeof(ID));                                 // Write speaker

    unsigned int seats = element._enrolled.getSeats();
    _file.write(reinterpret_cast<char*>(&seats), sizeof (unsigned int));            // Write number of seats (max attendants)
    const vector<ID>& attendants = element._enrolled.getAttendanceList();
    unsigned int numAttendants =attendants.size();
    _file.write(reinterpret_cast<char*>(&numAttendants), sizeof(unsigned int));     // Write number of attendants
    for(unsigned int i=0; i<numAttendants; i++)
    {
        _file.write(attendants[i].id, sizeof(ID));                                  // Write each attendant
    }

    Date::writeToFile(_file, element._date);                                        // Write date

}
