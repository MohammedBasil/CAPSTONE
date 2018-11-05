#ifndef UNIVERSITYMEMBER_H
#define UNIVERSITYMEMBER_H

#include <cstring>
#include "commons.h"

class UniversityMember
{
  public:
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

class Student : public UniversityMember
{
  public:
    Student( const ID id, const char* password, const Degree degree )
        : UniversityMember(id, password), _degree(degree) { setRole(); }
    //virtual ~Student() override { UniversityMember::~UniversityMember(); }

    Degree getDegree() const { return _degree; }
    void setDegree( const Degree degree ) { _degree = degree; }
  private:
    virtual void setRole() override { _role = Role::Student; }
    Degree _degree;

};

class Professor : public UniversityMember
{
  public:
    Professor( const ID id, const char* password)
        : UniversityMember(id, password) { setRole(); }
    //virtual ~Professor() override { UniversityMember::~UniversityMember(); }

  private:
    virtual void setRole() override { _role = Role::Professor; }
};

class Administrator : public UniversityMember
{
  public:
    Administrator( const ID id, const char* password)
        : UniversityMember(id, password) { setRole(); }
    //virtual ~Administrator() override { UniversityMember::~UniversityMember(); }

  private:
    virtual void setRole() override { _role = Role::Administrator; }
};

#endif // UNIVERSITYMEMBER_H
