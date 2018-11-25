#ifndef STUDENT_H
#define STUDENT_H
#include "universitymember.h"
#include "course.h"

class Student : public UniversityMember
{
  public:
    Student():UniversityMember(){Degree d; _degree=d; setRole();}
    Student( const ID id, const char* password, const Degree degree )
        : UniversityMember(id, password), _degree(degree) { setRole(); }
    //virtual ~Student() override { UniversityMember::~UniversityMember(); }

    Degree getDegree() const { return _degree; }
    void printCourses();
    void setDegree(const Degree degree) { _degree = degree; }
    void manageCourses(vector <Course> allCourses);


  private:
    virtual void setRole() override { _role = Role::Student; }
    Degree _degree;
    vector <Course> _slistcourses;


};
#endif // STUDENT_H


