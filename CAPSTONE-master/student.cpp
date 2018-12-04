#include "student.h"
#include "course.h"

void Student::printCourses(vector <Course>& allCourses)
{
    for (unsigned int i=0; i<allCourses.size(); i++)
    {
        for (unsigned int j=0; j<_slistcourses.size(); j++){
            if (strcmp(_slistcourses[j].full, allCourses[i].getCode().full)==0)
            {
                cout << "\t\t\t" << " Code: " << allCourses[i].getCode().full << "\t Name " << allCourses[i].getname() << endl;
            }
        }
    }

}


void Student::manageCourses(vector <Course>& allCourses)
{
    ResCode coursecode;
    bool quit=0;


    while (quit==0){
        int r =-1;
        cout << "Choose an action to perform:" << endl;
        cout << "1.- Enroll Course" << endl;
        cout << "2.- Delete Course" << endl;
        cout << "3.- List Courses" << endl;
        cout << "4.- Quit" << endl;
        int sel;
        getInt(&sel);

            switch(sel)
            {
                case 1: cout << " Please enter the ID of the subject to enroll: " << endl << endl;
                        cout << "Courses:" << endl;
                        for (size_t i=0; i<allCourses.size(); i++)
                        {                 
                            if (strcmp(allCourses[i].getDregree().full,this->getDegree().full)==0)
                            {
                                cout << "\tCourse ID: " << allCourses[i].getCode().full << endl;
                                cout << "\tCourse Name: " << allCourses[i].getname() << endl;
                                // Degree
                                cout << "\tNumber of credits: " << allCourses[i].getCredits() << endl << endl;
                            }
                        }
                        cout << "Enter code of the Course to enroll:" << endl;

                        getText(coursecode.full, sizeof(coursecode.full));


                        for (unsigned int i=0; i<allCourses.size(); i++)
                        {
                            if (strcmp(allCourses[i].getDregree().full,this->getDegree().full)==0)
                            {
                                if (strcmp(coursecode.full,allCourses[i].getCode().full)==0){
                                    r=(int)i;
                                    break;
                                }
                            }
                        }


                        if (r==-1) {
                            cout << " No course with this id" << endl;
                        } else {
                            _slistcourses.push_back(allCourses[r].getCode());
                            Mark mark;
                            mark.studentID=this->getID();
                            mark.grade=0.0;
                            allCourses[r].newmark(mark);
                        }

                        cout << "\t The courses that student: " << this->getID().id << " is enrolling are" << endl;
                        this->printCourses(allCourses);

                break;


                case 2: cout << " Please enter the ID of the subject to delete: " << endl << endl;
                        cout << "Courses:" << endl;
                        this->printCourses(allCourses);
                        cout << "Enter code of the Course to delete:" << endl;

                        getText(coursecode.full, sizeof(coursecode.full));

                        for (unsigned int i=0; i<_slistcourses.size(); i++)
                        {
                            if (coursecode.full==_slistcourses[i].full){
                                r=i;
                            }
                         }

                        if (r==-1) {
                            cout << " No course with this id" << endl;
                        } else {

                            _slistcourses.erase(_slistcourses.begin()+r);
                        }

                        break;


                case 3: cout << "\t The courses that student: " << this->getID().id << " is enrolling are" << endl;
                this->printCourses(allCourses);
                break;

                case 4: quit = 1; break;
                default: cout << "Invalid command." << endl; break;
            }
    }
}

Student Student::readFromFile(ifstream& file)
{
    ID id;
    char password[32];
    ResCode degree;

    id = ID::getFromFile(file);
    file.read(password,32);
    degree = getRCFromFile(file);

    Student student = Student(id, password, degree);

    unsigned int numCourses;
    file.read((char*)(&numCourses), sizeof(unsigned int));
    vector<ResCode> courses;

    for (unsigned int i=0; i<numCourses; i++)
    {
        ResCode code = getRCFromFile(file);
        courses.push_back(code);
    }

    student.setCourses(courses);

    return student;
}

void Student::writeToFile(ofstream& _file, Student element)
{
    _file.write(element._id.id, sizeof(ID));
    _file.write(element._password, sizeof(element._password));
    _file.write(element._degree.full, sizeof(ResCode));
    unsigned int numCourses = element._slistcourses.size();
    _file.write(reinterpret_cast<char*>(&numCourses), sizeof(unsigned int));

    for (unsigned int i=0; i<numCourses; i++)
    {
        _file.write(element._slistcourses[i].full, sizeof(ResCode));
    }
}

