#ifndef COURSE_H
#define COURSE_H
#include "resource.h"
#include "degree.h"

class Student;


class Course : public Resource
{
    public:
        Course(const ResCode code, const string name, const ResCode degree, const ID professor1ID, const ID professor2ID, const unsigned int credits, const Status status = Status::Created)
            : Resource (code, status), _name(name), _degree(degree), _professor1ID(professor1ID), _professor2ID(professor2ID), _credits(credits), _listofmarks() {}

        ResCode getDregree() const {return _degree; }
        void setDegree(const ResCode degree) { _degree = degree; }
        ID getProfessor1ID() const { return _professor1ID; }
        void setProfessor1ID(const ID professor1ID) {_professor1ID = professor1ID; }
        ID getProfessor2ID() const { return _professor2ID; }
        void setProfessor2ID(const ID professor2ID) {_professor2ID = professor2ID; }
        unsigned int getCredits() const { return _credits; }
        void setCredits(const unsigned int credits) { _credits = credits; }
        void setname(const string name){_name=name;}
        string getname () {return _name;}
        void newmark(const Mark m){_listofmarks.push_back(m);}
      //  Marklist& getMarklist() { return _listofmarks; }

    private:
        string _name;
        ResCode _degree;
        ID _professor1ID;
        ID _professor2ID;
        unsigned int _credits;
        vector <Mark> _listofmarks;
        //vector <Student*> _listStudents;


};
#endif // COURSE_H
