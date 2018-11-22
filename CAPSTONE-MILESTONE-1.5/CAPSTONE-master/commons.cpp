#include "commons.h"
#include <iostream>
#include <limits>

void getText(char* buffer, int size)
{

    cin.get(buffer, size);
    cin.clear();                                            //Necessary to avoid issues with the input
    cin.ignore(numeric_limits<streamsize>::max(), '\n');    //Without it infinite loops and other errors appear
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

ID ID::getFromConsole()
{
    ID id;
    getText(id.id, sizeof(ID));
    return id;
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

// TODO
//void Enrolledlist::removeAttendant( const ID attendantID )
//{
//    for(int i=0; i<_attendants.size(); i++)
//    {
//        if (_attendants[i] == attendantID)
//    }
//}

void Enrolledlist::setSeats(unsigned int seats)
{
    _seats = seats;
    if ( _attendants.size() > seats )
    {
        _attendants.resize(seats);
        cout << "Several people may have been eliminated from the list." << endl;
    }

}
