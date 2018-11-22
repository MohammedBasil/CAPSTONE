#ifndef COMMONS_H
#define COMMONS_H


#include <cstring>
#include <vector>


using namespace std;

// TODO Char until it is defined


// TODO add methods (get, set, compare)
struct ID
{
    char id[8]; // Last char is a NULL
    bool Valid() { return strlen(id) == 7; }
    static ID getFromConsole();
};

enum class Role
{
    Administrator,
    Professor,
    Student
};

// all the variables inside the union refer to the same space in memory
// the variables in the struct are contiguous in memory (LLL is letters and NNNN numbers)
union ResCode
{
    char full[8];
    struct comps {
        char LLL[3];
        char NNNN[4];
    };
};

struct Mark
{
    ID studentID;
    float grade;
};

struct Date
{
    unsigned int day;
    unsigned int month;
    unsigned int year;
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

//class Enrolledlist
//{
//    public:
//        Enrolledlist() : _attendants(nullptr), _size(0) {}
//        Enrolledlist( const unsigned int size ) : _attendants(new ID[size]), _size(size) {}
//        ~Enrolledlist() { if (_attendants != nullptr) { delete[] _attendants; }}

//        void addAttendant( const ID attendantID );
//        void removeAttendant( const ID attendantID );
//        const ID* getAttendanceList() const { return _attendants; }
//        unsigned int getSize() const { return _size; }

//    private:
//        ID* _attendants;
//        unsigned int _size;
//};

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

    private:
        vector<ID> _attendants;
        unsigned int _seats;
};

void getText(char* buffer, int size);

void getInt(int* value);

void getInt(unsigned int* value);

#endif // COMMONS_H
