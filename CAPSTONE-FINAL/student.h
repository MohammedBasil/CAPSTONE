#ifndef STUDENT_H
#define STUDENT_H

#include "universitymember.h"

class Student : public UniversityMember
{
  public:
    Student( const ID id, const char* password, const ResCode degree )
        : UniversityMember(id, password), _degree(degree) { setRole(); }

    ResCode getDegree() const { return _degree; }
    void setDegree(const ResCode degree) { _degree = degree; }

    static Student readFromFile(ifstream& file);
    static void writeToFile(ofstream& _file, const Student& element);


  private:
    virtual void setRole() override { _role = Role::Student; }
    ResCode _degree;

};
#endif // STUDENT_H


