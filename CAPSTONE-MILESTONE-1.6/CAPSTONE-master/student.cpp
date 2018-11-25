#include "student.h"
#include "course.h"

void Student::printCourses()
{
    for (unsigned int i=0; i<_slistcourses.size(); i++){
        cout << "\t\t\t" << " Code: " << _slistcourses[i].getCode().full << "\t Name " << _slistcourses[i].getname() << endl;
    }
}


void Student::manageCourses(vector <Course> allCourses)
{
    ResCode coursecode;
    bool quit=0;
    unsigned int r;
    bool check;

    while (quit==0){
    check=0;
    cout << "Choose an action to perform:" << endl;
    cout << "1.- Enroll Course" << endl;
    cout << "2.- Delete Course" << endl;
    cout << "3.- List Courses" << endl;
    cout << "4.- Quit" << endl;
   int sel;
    getInt(&sel);

    //auto it= find_if(allCourses.begin(), allCourses.end(), [&coursecode](const Course& course) {return strcmp(course.getCode().full, coursecode.full) == 0;});



            switch(sel)
            {
                case 1: cout << " Please enter the ID of the subject to enroll: " << endl << endl;
                        cout << "Courses:" << endl;
                        for (size_t i=0; i<allCourses.size(); i++)
                        {
                            cout << "\tCourse ID: " << allCourses[i].getCode().full << endl;
                            cout << "\tCourse Name: " << allCourses[i].getname() << endl;
                            // Degree
                            cout << "\tNumber of credits: " << allCourses[i].getCredits() << endl << endl;

                        }
                        cout << "Enter code of the Course to enroll:" << endl;

                        getText(coursecode.full, sizeof(coursecode.full));

                        //it = find_if(allCourses.begin(), allCourses.end(), [&coursecode](const Course& course) {return strcmp(course.getCode().full, coursecode.full) == 0;});


                        for (unsigned int i=0; i<allCourses.size(); i++)
                        {
                            if (strcmp(coursecode.full,allCourses[i].getCode().full)==0){
                                r=i;
                                check=0;
                                 break;
                            } else{

                                check=1;
                            }

                        }

                   if (allCourses[r].getDregree().getname() == this->getDegree().getname()){
                        if (check==1) {
                            cout << " No course with this id" << endl;
                        } else {
                            _slistcourses.push_back(allCourses[r]);
                            Mark mark;
                            mark.studentID=this->getID();
                            mark.grade=0.0;
                            allCourses[r].newmark(mark);
                        }

                       /* if (it != allCourses.end())
                        {
                          Course& course = *it;
                          _slistcourses.push_back(course);
                        }*/
                        cout << "\t The courses that student: " << this->getID().id << " is enrolling are" << endl;
                                        this->printCourses();
                   } else {cout << endl << "You cannot enroll this subject since the subject you selected is not available for your degree " << endl << endl;}

                break;


                case 2: cout << " Please enter the ID of the subject to delete: " << endl << endl;
                        cout << "Courses:" << endl;
                        this->printCourses();
                        cout << "Enter code of the Course to delete:" << endl;

                        getText(coursecode.full, sizeof(coursecode.full));

                        for (unsigned int i=0; i<_slistcourses.size(); i++)
                        {
                            if (coursecode.full==_slistcourses[i].getCode().full){
                                r=i;
                            } else{
                                if (i==_slistcourses.size())   {
                                check=1;
                            }}
                        break;
                        }

                        if (check==1) {
                            cout << " No course with this id" << endl;
                        } else {

                            _slistcourses.erase(_slistcourses.begin()+r);
                        }

                        /*it = find_if(_slistcourses.begin(), _slistcourses.end(), [&coursecode](const Course& course) {return strcmp(course.getCode().full, coursecode.full) == 0;});

                        if (it != _slistcourses.end())
                        {
                          _slistcourses.erase(it);
                        }*/
                        break;


                case 3: cout << "\t The courses that student: " << this->getID().id << " is enrolling are" << endl;
                this->printCourses();
                break;

                case 4: quit = 1; break;
                default: cout << "Invalid command." << endl; break;
            }
    }
}
