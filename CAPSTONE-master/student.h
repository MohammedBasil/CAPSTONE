#ifndef STUDENT_H
#define STUDENT_H
#include "universitymember.h"
#include "course.h"
#include "seminar.h"
#include "fdp.h"

class Student : public UniversityMember
{
  public:
    //Student():UniversityMember(){Degree d; _degree=d; setRole();}
    Student( const ID id, const char* password, const ResCode degree )
        : UniversityMember(id, password), _degree(degree) { setRole(); }
    //virtual ~Student() override { UniversityMember::~UniversityMember(); }

    ResCode getDegree() const { return _degree; }
    void setDegree(const ResCode degree) { _degree = degree; }

    void printCourses(vector<Course>& allCourses);
    void manageCourses(vector<Course>& allCourses);

   // void printFDPs(vector <FDP>& allFDPs);
 //   void manageFDPs(vector <FDP>& allFDPs);

    void setCourses(vector<ResCode>& listcourses) { _slistcourses = listcourses; }

    static Student readFromFile(ifstream& file);
    static void writeToFile(ofstream& _file, Student element);


  private:
    virtual void setRole() override { _role = Role::Student; }
    ResCode _degree;
    vector <ResCode> _slistcourses;
//    vector <ResCode> _slistfdps;



};
#endif // STUDENT_H


