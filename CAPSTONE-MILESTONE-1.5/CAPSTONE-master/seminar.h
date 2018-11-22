#ifndef SEMINAR_H
#define SEMINAR_H
#include "resource.h"

class Seminar : public Resource
{
    public:
        Seminar (const ResCode code, const ID coordinatorID, const ID speakerID, const unsigned int seats, const Date date, const Status status = Status::Created)
            : Resource(code, status), _coordinatorID(coordinatorID), _speakerID(speakerID), _enrolled(seats), _date(date) {}

        ID getCoordinatorID() const { return _coordinatorID; }
        void setCoordinatorID( const ID coordinatorID ) { _coordinatorID = coordinatorID; }
        ID getSpeakerID() const {return _speakerID; }
        void setSpeakerID( const ID speakerID ) { _speakerID = speakerID; }
        unsigned int getSeats() const { return _enrolled.getSeats(); }
        void setSeats (const unsigned int seats ) { _enrolled.setSeats(seats); }
        Enrolledlist& getEnrolledList() { return _enrolled; }
        Date getDate() const { return _date; }
        void setDate( const Date date ) { _date = date; }

    private:
        ID _coordinatorID;
        ID _speakerID;
        Enrolledlist _enrolled;
        Date _date;
};

#endif // SEMINAR_H
