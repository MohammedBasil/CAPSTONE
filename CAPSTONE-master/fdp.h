#ifndef FDP_H
#define FDP_H
#include "resource.h"
#include "degree.h"

class FDP : public Resource
{
    public:
        FDP (const ResCode code, const ResCode degree, const ID studentID, const ID tutorID, const ID cotutorID = {0}, const Status status = Status::Created)
            : Resource(code, status), _degree(degree), _studentID(studentID), _tutorID(tutorID), _cotutorID(cotutorID) {}

        ID getStudentID() const {return _studentID; }
        ID getTutorID() const {return _tutorID; }
        ID getCotutorID() const {return _cotutorID; }
        ResCode getDegree() const { return _degree; }
        void setStudentID( const ID studentID) { _studentID = studentID; }
        void setTutorID( const ID tutorID) { _tutorID = tutorID; }
        void setCotutorID( const ID cotutorID) { _cotutorID = cotutorID; }
        void setDegree( const ResCode degree ) { _degree = degree; }

        static FDP readFromFile(ifstream& file);
        static void writeToFile(ofstream& _file, FDP element);

    private:
        ResCode _degree;
        ID _studentID;
        ID _tutorID;
        ID _cotutorID;
};

#endif // FDP_H
