#include "student.h"
#include "course.h"

void Student::printCourses(vector <Course>& allCourses)
{
    for (unsigned int i=0; i<allCourses.size(); i++)
    {
        for (unsigned int j=0; j<_slistcourses.size(); j++){
            if (strcmp(_slistcourses[j].full, allCourses[i].getCode().full))
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

    //auto it= find_if(allCourses.begin(), allCourses.end(), [&coursecode](const Course& course) {return strcmp(course.getCode().full, coursecode.full) == 0;});



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

                        //it = find_if(allCourses.begin(), allCourses.end(), [&coursecode](const Course& course) {return strcmp(course.getCode().full, coursecode.full) == 0;});


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

                       /* if (it != allCourses.end())
                        {
                          Course& course = *it;
                          _slistcourses.push_back(course);
                        }*/
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

                        /*it = find_if(_slistcourses.begin(), _slistcourses.end(), [&coursecode](const Course& course) {return strcmp(course.getCode().full, coursecode.full) == 0;});

                        if (it != _slistcourses.end())
                        {
                          _slistcourses.erase(it);
                        }*/
                        break;


                case 3: cout << "\t The courses that student: " << this->getID().id << " is enrolling are" << endl;
                this->printCourses(allCourses);
                break;

                case 4: quit = 1; break;
                default: cout << "Invalid command." << endl; break;
            }
    }
}
