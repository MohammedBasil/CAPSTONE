#include "commons.h"
#include <iostream>
#include <limits>


// Functions to receive input safely from console
void getText(char* buffer, int size)
{

    cin.get(buffer, size);
    cin.clear();                                            //Necessary to avoid issues with the input
    cin.ignore(numeric_limits<streamsize>::max(), '\n');    //Without it infinite loops and other errors appear for a bad input
}

void getInt(int* value)
{

    cin >> *value;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void getInt(unsigned int* value)
{

    cin >> *value;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void getFloat(float* value)
{
	cin >> *value;
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

bool ID::Valid()
{
	return strlen(id) == 7;
}

bool ID::IsSIN()
{
    // Make sure the length is right
	if (Valid())
	{
		for (int i = 0; i < 7; i++)
		{
			if (id[i] < '0' || id[i] > '9')
			{
				// character out of range
				return false;
			}
		}

		// all characters are numbers
		return true;
	}
	return false;
}

bool ID::IsPID()
{
	// make sure the length is right
	if (Valid())
	{
		for (int i = 0; i < 7; i++)
		{
			if (id[i] < 'A' || id[i] > 'Z')
			{
				// character out of range
				return false;
			}
		}

		// all characters are letters
		return true;
	}
	return false;
}

bool ID::Equals(const ID& other) const
{
	return strcmp(id, other.id) == 0;
}

ID ID::getFromConsole(bool optional)
{
	// ask for IDs until we get a valid one
    // If ID is optional (like in the case of the cotutor for an FDP) we can just not assign one
    ID id;
	while (true)
	{
		getText(id.id, sizeof(ID));
        if (optional && id.Equals(ID()))
        {break;}
		if (id.Valid()) { break; }
		cout << "Invalid ID." << endl;
		cout << "Introduce a valid ID: ";
	}
    return id;
}

ID ID::getFromFile(ifstream& file)
{
    ID id;
    file.read(id.id,sizeof(ID));
    return id;
}

bool ResCode::Valid()
{
	// make sure the length is right
	if (strlen(code) == 7)
	{
		// check first 3 characters are letters
		for (int i = 0; i < 3; i++)
		{
			if (code[i] < 'A' || code[i] > 'Z')
			{
				return false;
			}
		}

		// check last 4 characters are numbers
		for (int i = 3; i < 7; i++)
		{
			if (code[i] < '0' || code[i] > '9')
			{
				return false;
			}
		}

		// all characters are valid
		return true;
	}
	return false;
}

bool ResCode::Equals(const ResCode & other) const
{
	return strcmp(code, other.code) == 0;
}

ResCode ResCode::getFromConsole()
{
	ResCode resCode;
	while (true)
	{
		getText(resCode.code, sizeof(ResCode));
		if (resCode.Valid()) { break; }
		cout << "Invalid code." << endl;
		cout << "Introduce a valid code: ";
	}
	return resCode;
}

ResCode ResCode::getFromFile(ifstream& file)
{
    ResCode resCode;
    file.read(resCode.code, sizeof(ResCode));
    return resCode;
}

Mark Mark::getFromFile(ifstream& file)
{
    Mark mark;
    file.read(mark.studentID.id, sizeof(ID));
    file.read((char*)(&mark.grade), sizeof(float));

    return mark;
}

Date Date::getFromFile(ifstream& file)
{
    Date date;
    file.read((char*)(&date.day), sizeof(unsigned int));
    file.read((char*)(&date.month), sizeof(unsigned int));
    file.read((char*)(&date.year), sizeof(unsigned int));

    return date;
}

void Date::writeToFile(ofstream& _file, Date date)
{
    _file.write(reinterpret_cast<char*>(&date.day), sizeof(unsigned int));
    _file.write(reinterpret_cast<char*>(&date.month), sizeof(unsigned int));
    _file.write(reinterpret_cast<char*>(&date.year), sizeof(unsigned int));
}

Enrolledlist::Enrolledlist( const unsigned int size ) : _seats(size)
{
    _attendants.reserve(size);
}

void Enrolledlist::addAttendant( const ID attendantID )
{
    if (_attendants.size() < _seats)
    {
        _attendants.push_back(attendantID);
    }
    else
    {
        cout << "This seminar is full." << endl;
    }
}

void Enrolledlist::removeAttendant(const ID attendantID)
{
	for (size_t i = 0; i < _attendants.size(); i++)
	{
		if (_attendants[i].Equals(attendantID))
		{
			_attendants.erase(_attendants.begin() + i);
			return;
		}
    }
}

void Enrolledlist::setSeats(unsigned int seats)
{
    _seats = seats;
    if ( _attendants.size() > seats )
    {
        _attendants.resize(seats);
        cout << "Several people may have been eliminated from the list." << endl;
    }

}

int getMenuChoice(int min, int max)
{
    // Ask for a number between min and max until a valid one is entered
	int choice = -1;
	while (choice == -1)
	{
		cout << "Select an option (" << min << "-" << max << "): ";
		getInt(&choice);
		if (choice < min || choice > max)
		{
			cout << "Invalid choice. ";
			choice = -1;
		}
	}

	return choice;
}

