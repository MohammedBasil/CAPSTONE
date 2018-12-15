#ifndef COMMONS_H
#define COMMONS_H

#include <iostream>
#include <cstring>
#include <vector>
#include <fstream>

using namespace std;

struct ID
{
    char id[8]; // Last char is a NULL
	bool Valid();
	bool IsSIN(); // 7 digits
	bool IsPID(); // 7 characters
	bool Equals(const ID& other) const;
    static ID getFromConsole(bool optional = false);
    static ID getFromFile(ifstream& file);
};

struct ResCode
{
    char code[8]; // Last char is a NULL
	bool Valid(); // format LLLNNNN
	bool Equals(const ResCode& other) const;
	static ResCode getFromConsole();
	static ResCode getFromFile(ifstream& file);
};

enum class Role
{
	Administrator,
	Professor,
	Student,
	Any
};

struct Mark
{
    ID studentID;
    float grade;

    static Mark getFromFile(ifstream& file);
};

struct Date
{
    unsigned int day;
    unsigned int month;
    unsigned int year;

    static Date getFromFile(ifstream& file);
    static void writeToFile(ofstream& _file, Date date);
};

class Marklist
{
    public:
        Marklist() : _marks(nullptr), _size(0) {}
        ~Marklist() { if (_marks != nullptr) { delete[] _marks; }}

        void addMark( const Mark mark );
        void addMark( const ID studentID, const float grade ) { addMark(Mark{studentID, grade}); }
        void removeMark( const ID studentID );
        void modifyMark( const Mark mark ) { modifyMark(mark.studentID, mark.grade); }
        void modifyMark( const ID studentID, const float grade );
        Mark getMark( const ID studentID ) const;
        const Mark* getMarks() const { return _marks; }
        unsigned int getSize() const { return _size; }

    private:
        Mark* _marks;
        unsigned int _size;
};

class Enrolledlist
{
    public:
        Enrolledlist() : _seats(0) {}
        Enrolledlist( const unsigned int size );

        void addAttendant( const ID attendantID );
        void removeAttendant( const ID attendantID );
        const vector<ID>& getAttendanceList() const { return _attendants; }
        unsigned int getSeats() const { return _seats; }
        void setSeats(unsigned int seats);

        void setAttendants(vector<ID>& attendants) { _attendants = attendants; }

    private:
        vector<ID> _attendants;
        unsigned int _seats;
};

void getText(char* buffer, int size);

void getInt(int* value);

void getInt(unsigned int* value);

void getFloat(float* value);

int getMenuChoice(int min, int max);

#endif // COMMONS_H
