#ifndef RESOURCE_H
#define RESOURCE_H
#include "commons.h"

enum Status
{
    Created,
    InProgress,
    Completed
};

const char* getStatusString(const Status status);

class Resource
{
    public:

        ResCode getCode() const {return _code; }
        Status getStatus() const {return _status;}
        void setStatus( const Status status ) { _status = status; }
        // Code is set only once when created, so it has no setter

    protected:
        Resource(const ResCode code, const Status status = Status::Created) : _code(code), _status(status) {} // To avoid instantiating base class
        ResCode _code;
        Status  _status;
};


#endif // RESOURCE_H
