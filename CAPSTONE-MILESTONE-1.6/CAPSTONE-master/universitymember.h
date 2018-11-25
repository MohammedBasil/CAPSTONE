#ifndef UNIVERSITYMEMBER_H
#define UNIVERSITYMEMBER_H
#include <iostream>
#include "commons.h"
#include "degree.h"
#include"vector"


using namespace std;

class UniversityMember
{
  public:
    UniversityMember(){
        ID id;
        for (unsigned int i=0; i<strlen(id.id); i++){
            id.id[0]='0';
        }
        _id=id;
        for (unsigned int i=0; i<strlen(_password); i++){
            _password[0]='0';
        }

    }
    UniversityMember( const ID id, const char* password )
        : _id(id) { strcpy(_password, password); }
    //virtual ~UniversityMember() {}

    ID getID() const { return _id; }
    Role getRole() const { return _role; }
    const char* getPassword() const { return _password; }
    void setPassword( const char* password ) { strcpy(_password, password); }
    // ID and role have no setters since they are set once when the user is created and cannot be changed
  protected:
    // Purely virtual so that universitymember cannot be instatiated
    // The role can only be set in the corresponding derived class (e.g.: there can't be a student with administrator rights)
    virtual void setRole() = 0;

    ID _id;
    Role _role;
    char _password[32];


};


#endif // UNIVERSITYMEMBER_H

