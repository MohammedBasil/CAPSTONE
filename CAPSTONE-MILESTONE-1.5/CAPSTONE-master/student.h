#ifndef STUDENT_H
#define STUDENT_H
#include "universitymember.h"

class Course;

class Student : public UniversityMember
{
  public:
    Student( const ID id, const char* password, const Degree degree )
        : UniversityMember(id, password), _degree(degree) { setRole(); }
    //virtual ~Student() override { UniversityMember::~UniversityMember(); }

    Degree getDegree() const { return _degree; }
    void setDegree(const Degree degree) { _degree = degree; }
  private:
    virtual void setRole() override { _role = Role::Student; }
    Degree _degree;
    vector <Course*> _slistcourses;


};
#endif // STUDENT_H


