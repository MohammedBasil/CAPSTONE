#ifndef RESOURCE_H
#define RESOURCE_H

#include "commons.h"

enum Status
{
    Created,
    InProgress,
    Completed
};

class Resource
{
    public:

        // Destructor??
        ResCode getCode() const {return _code; }
        Status getStatus() const {return _status;}
        void setStatus( const Status status ) { _status = status; }
        // Code is set only once when created, so it has no setter

    protected:
        Resource(const ResCode code, const Status status = Status::Created) : _code(code), _status(status) {} // To avoid instantiating base class
        ResCode _code;
        Status _status;
};

class Course : public Resource
{
    public:
        Course(const ResCode code, const Degree degree, const ID professor1ID, const ID professor2ID, const unsigned int credits, const Status status = Status::Created)
            : Resource (code, status), _degree(degree), _professor1ID(professor1ID), _professor2ID(professor2ID), _credits(credits), _listofmarks() {}

        Degree getDregree() const {return _degree; }
        void setDegree(const Degree degree) { _degree = degree; }
        ID getProfessor1ID() const { return _professor1ID; }
        void setProfessor1ID(const ID professor1ID) {_professor1ID = professor1ID; }
        ID getProfessor2ID() const { return _professor2ID; }
        void setProfessor2ID(const ID professor2ID) {_professor2ID = professor2ID; }
        unsigned int getCredits() const { return _credits; }
        void setCredits(const unsigned int credits) { _credits = credits; }
        Marklist& getMarklist() { return _listofmarks; }

    private:
        Degree _degree;
        ID _professor1ID;
        ID _professor2ID;
        unsigned int _credits;
        Marklist _listofmarks;
};

class FDP : public Resource
{
    public:
        FDP (const ResCode code, const Degree degree, const ID studentID, const ID tutorID, const ID cotutorID = {0}, const Status status = Status::Created)
            : Resource(code, status), _degree(degree), _studentID(studentID), _tutorID(tutorID), _cotutorID(cotutorID) {}

        ID getStudentID() const {return _studentID; }
        ID getTutorID() const {return _tutorID; }
        ID getCotutorID() const {return _cotutorID; }
        Degree getDegree() const { return _degree; }
        void setStudentID( const ID studentID) { _studentID = studentID; }
        void setTutorID( const ID tutorID) { _tutorID = tutorID; }
        void setCotutorID( const ID cotutorID) { _cotutorID = cotutorID; }
        void setDegree( const Degree degree ) { _degree = degree; }

    private:
        Degree _degree;
        ID _studentID;
        ID _tutorID;
        ID _cotutorID;
};

class Seminar : public Resource
{
    public:
        Seminar (const ResCode code, const ID coordinatorID, const ID speakerID, const unsigned int seats, const Date date, const Status status = Status::Created)
            : Resource(code, status), _coordinatorID(coordinatorID), _speakerID(speakerID), _enrolled(seats), _date(date) {}

        ID getCoordinatorID() const { return _coordinatorID; }
        void setCoordinatorID( const ID coordinatorID ) { _coordinatorID = coordinatorID; }
        ID getSpeakerID() const {return _speakerID; }
        void setSpeakerID( const ID speakerID ) { _speakerID = speakerID; }
        unsigned int getSeats() const { return _enrolled.getSize(); }
        void setSeats (const unsigned int seats );
        Enrolledlist& getEnrolledList() { return _enrolled; }
        Date getDate() const { return _date; }
        void setDate( const Date date ) { _date = date; }

    private:
        ID _coordinatorID;
        ID _speakerID;
        Enrolledlist _enrolled;
        Date _date;
};


#endif // RESOURCE_H
