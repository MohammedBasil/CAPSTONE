#include "resourcemanager.h"
#include <iostream>
#include <algorithm>
#include <cstring>
#include "filereader.h"
#include "filewriter.h"
#include "student.h"
#include "usermanager.h"

ResourceManager::ResourceManager(VirtualCampus& campus)
	: _campus(campus)
{
    _RCgenerator = { { 'A', 'A', 'A', '0', '0', '0', '0', 0 } }; // Predetermined initial ResCode generator value

    FileReader RCReader("rescode.bin");     // If resources already exist, the new initial value for the ResCode generator is loaded from file
    RCReader.readCode(_RCgenerator.code);

    FileReader degreeReader("degrees.bin");         // Load existing degrees
    degreeReader.readall<Degree>(_degreeList);

    FileReader courseReader("courses.bin");         // Load existing courses
    courseReader.readall<Course>(_courselist);

    FileReader FDPReader("FDPs.bin");               // Load existing  FDPs
    FDPReader.readall<FDP>(_FDPlist);

    FileReader seminarReader("seminars.bin");       // Load existing  seminars
    seminarReader.readall<Seminar>(_seminarlist);
}

ResourceManager::~ResourceManager()
{
    FileWriter RCWriter("rescode.bin");     // Save last ResCode generator
    RCWriter.writeCode(_RCgenerator.code);
}


void ResourceManager::createResource()
{
           cout << "Select type of resource to create:" << endl;
           cout << "1.- Course" << endl;
           cout << "2.- Final Degree Project (FDP)" << endl;
           cout << "3.- Seminar" << endl;
           cout << "4.- Degree" << endl;

		   int choice = getMenuChoice(1, 4);
           switch(choice)
           {
                case 1: createCourse(); break;
                case 2: createFDP(); break;
                case 3: createSeminar(); break;
                case 4: createDegree(); break;
           }
}

void ResourceManager::createDegree()
{
    char name[255];
    cout << "Introduce name of degree" << endl;
    getText(name, sizeof(name));

    ResCode code = createResCode();
    Degree degree(code, name);
    _degreeList.push_back(degree);

    cout << "Created degree with resource code " << code.code << endl;

    FileWriter degreeWriter("degrees.bin");         // Write to file
    degreeWriter.writeall<Degree>(_degreeList);
}

void ResourceManager::createCourse()
{
    char name[255];
    cout << "Introduce the name of the course" << endl;
    getText(name, sizeof(name));

    cout << "Introduce the code of the degree of the course" << endl;
	ResCode degreecode = getExistingDegreeFromConsole();
	if (!degreecode.Valid()) { cout << "Course creation failed." << endl; return; }

    cout << "Introduce ID of first professor" << endl;
	ID prof1 = getExistingUserFromConsole(Role::Professor);
	if (!prof1.Valid()) { cout << "Course creation failed." << endl; return; }

    cout << "Introduce ID of second professor" << endl;
	ID prof2 = getExistingUserFromConsole(Role::Professor);
	if (!prof2.Valid()) { cout << "Course creation failed." << endl; return; }

    unsigned int credits;
    cout << "Number of credits:" << endl;
    getInt(&credits);

    ResCode code = createResCode();
    Course course(code, name, degreecode, prof1, prof2, credits);
    _courselist.push_back(course);
    cout << "Created course with resource code " << code.code << endl;

    saveCourses();  // Write to file
}

void ResourceManager::createFDP()
{
    cout << "Introduce the code of the degree of the FDP" << endl;
    ResCode degreecode = getExistingDegreeFromConsole();
    if (!degreecode.Valid()) { cout << "FDP creation failed." << endl; return; }

    cout << "Introduce ID of student (optional)" << endl;
    ID student = getExistingUserFromConsole(Role::Student, true);
    if (!student.Valid()) { cout << "No student assigned." << endl; }

    cout << "Introduce ID of tutor" << endl;
    ID tutor = getExistingUserFromConsole(Role::Professor);
    if (!tutor.Valid()) { cout << "FDP creation failed." << endl; return; }

    cout << "Introduce ID of cotutor (optional)" << endl;
    ID cotutor = getExistingUserFromConsole(Role::Professor, true);
    if (!cotutor.Valid()) { cout << "No cotutor assigned." << endl;}

    ResCode code = createResCode();
    FDP fdp(code, degreecode, student, tutor, cotutor);
    _FDPlist.push_back(fdp);
    cout << "Created Final Degree Project with resource code " << code.code << endl;

    saveFDPs(); // Write to file
}

void ResourceManager::createSeminar()
{
    cout << "Introduce ID of coordinator" << endl;
    ID coord = getExistingUserFromConsole(Role::Professor);
    if (!coord.Valid()) { cout << "Seminar creation failed." << endl; return; }

    cout << "Introduce ID of speaker" << endl;
    ID speaker = getExistingUserFromConsole(Role::Professor);
    if (!speaker.Valid()) { cout << "Seminar creation failed." << endl; return; }

    cout << "Number of seats:" << endl;
    unsigned int seats;
    getInt(&seats);
    Date date;
    cout << "Enter date:" << endl;
    cout << "Year: ";
    getInt(&date.year);

    bool correctdate = 0;
    while (correctdate==0)
    {
        cout << "Month: ";
        getInt(&date.month);

        if (date.month>0 && date.month<=12) {correctdate=1;}
        else { cout << "Error. please enter a valid date." << endl; }
    }

    correctdate = 0;
    while (correctdate==0)
    {
        cout << "Day: ";
        getInt(&date.day);

        if (date.day>0 && date.day<=31) {correctdate=1;}
        else { cout << "Error. please enter a valid date." << endl; }
    }

    ResCode code = createResCode();
    Seminar seminar(code, coord, speaker, seats, date);
    _seminarlist.push_back(seminar);
    cout << "Created seminar with resource code " << code.code << endl;

    saveSeminars(); // Write to file
}


void ResourceManager::editResource(const UniversityMember* user)
{
    cout << "Enter code of the resource to edit:" << endl;
	ResCode code = ResCode::getFromConsole();

    // Try to find the resource
	Course* course = getCourse(code);
	FDP* fdp = getFDP(code);
	Seminar* seminar = getSeminar(code);

    // Full access for admins
	bool isAdmin = (user->getRole() == Role::Administrator);

	if (course != nullptr)
	{
        if (!isAdmin && !course->isEnrolled(user->getID())) // Is not an admin or a professor associated to the course
		{
			cout << "No permission to edit this course" << endl;
			return;
		}
		editCourse(code);
	}
	else if (fdp != nullptr)
	{
		if ( !isAdmin)
		{
			if (!fdp->getTutorID().Equals(user->getID()) &&
                !fdp->getCotutorID().Equals(user->getID()) )    // Is not the tutor or cotutor of the FDP
			{
                cout << "No permission to edit this FDP" << endl;
				return;
			}
		}
		editFDP(code);
	}
	else if (seminar != nullptr)
	{
        if (!isAdmin && !seminar->isEnrolled(user->getID()))    // Is not an admin or a professor associated to the seminar
		{
			cout << "No permission to edit this seminar" << endl;
			return;
		}
		editSeminar(code);
	}
	else
	{
		cout << "No resource with that code exists." << endl;
	}

}

void ResourceManager::editMarks(const UniversityMember* user)
{
	cout << "Enter code of the course to edit:" << endl;
	ResCode code = ResCode::getFromConsole();

    Course* course = getCourse(code);   // Try to find the course
	if (course == nullptr)
	{
		cout << "No course with that code exists." << endl;
	}

    if (!course->isEnrolled(user->getID())) // If it is not a professor of this course
	{
		cout << "No permission to edit this course" << endl;
		return;
	}

    // List students enrolled in course and their grade
	cout << "Current marks of this course:" << endl;
	const vector<Mark>& marks = course->getMarks();
	for (size_t i = 0; i < marks.size(); i++)
	{
		cout << (i + 1) << ".- Student " << marks[i].studentID.id << ": " << marks[i].grade << endl;
	}

    // Select the student whose grade you want to edit
    int choice = getMenuChoice(1, marks.size()) - 1;
	cout << "Selected entry: " << marks[choice].studentID.id << ": " << marks[choice].grade << endl;

	cout << "Enter new grade for this mark: " << endl;
	float newgrade = marks[choice].grade;
	getFloat(&newgrade);

	course->modifyMark(marks[choice].studentID, newgrade);
	cout << "Mark modified." << endl << endl;

    saveCourses();  // Save to file
}

void ResourceManager::editCourse(const ResCode &code)
{
	Course* course = getCourse(code);
    if (course != nullptr)
    {
	  bool quit = false;
      while (!quit)
      {
          cout << "Select attribute to edit:" << endl;
          cout << "1.- ID of professor 1" << endl;
          cout << "2.- ID of professor 2" << endl;
          cout << "3.- Number of credits" << endl;
          cout << "4.- Status" << endl;
          cout << "5.- Stop editing" << endl;

		  int choice = getMenuChoice(1, 5);
          switch(choice)
          {
            case 1:
                    {
                      cout << "Enter ID of first professor" << endl;
                      ID prof1 = getExistingUserFromConsole(Role::Professor);
                      if (!prof1.Valid()) { cout << "Course edition failed." << endl; return; }
                      course->setProfessor1ID(prof1);
                      break;
                    }
            case 2:
                    {
                      cout << "Enter ID of second professor" << endl;
                      ID prof2 = getExistingUserFromConsole(Role::Professor);
                      if (!prof2.Valid()) { cout << "Course edition failed." << endl; return; }
                      course->setProfessor2ID(prof2);
                      break;
                     }
            case 3:
                     {
                      cout << "Enter new number of credits:" << endl;
                      unsigned int credits;
                      getInt(&credits);
                      course->setCredits(credits);
                      break;
                     }
            case 4:
                    {
                      cout << "Select status:" << endl;
                      cout << "1.- Created" << endl;
                      cout << "2.- In progress" << endl;
                      cout << "3.- Completed" << endl;

					  int stat = getMenuChoice(1, 3);
					  switch (stat)
                      {
                          case 1: course->setStatus(Created); break;
                          case 2: course->setStatus(InProgress); break;
                          case 3: course->setStatus(Completed); break;
                      }

                    }
                    break;
            case 5: quit = true; break;

          }

      }

      cout << "Course edited." <<endl;
    }
    else
    {
        cout << "No course with that code exists." <<endl;
    }

    saveCourses();  // Write to file

}

void ResourceManager::editFDP(const ResCode &code)
{
    FDP* fdp = getFDP(code);    // Try to find the FDP
	if (fdp != nullptr)
    {
      bool quit = false;
      while (!quit)
      {
          cout << "Select attribute to edit:" << endl;
          cout << "1.- ID of student" << endl;
          cout << "2.- ID of tutor" << endl;
          cout << "3.- ID of cotutor" << endl;
          cout << "4.- Status" << endl;
          cout << "5.- Stop editing" << endl;

		  int choice = getMenuChoice(1, 5);
		  switch (choice)
          {
            case 1:
                    {
                      cout << "Enter ID of student" << endl;
                      ID student = getExistingUserFromConsole(Role::Student, true);
                      if (!student.Valid()) { cout << "No student assigned." << endl; }
                      fdp->setStudentID(student);
                      break;
                    }
            case 2:
                    {
                      cout << "Enter ID of tutor" << endl;
                      ID tutor = getExistingUserFromConsole(Role::Professor);
                      if (!tutor.Valid()) { cout << "FDP edition failed." << endl; return; }
                      fdp->setTutorID(tutor);
                      break;
                    }
            case 3:
                    {
                      cout << "Enter ID of cotutor" << endl;
                      ID cotutor = getExistingUserFromConsole(Role::Professor, true);
                      if (!cotutor.Valid()) { cout << "No cotutor assigned." << endl; }
                      fdp->setCotutorID(cotutor);
                      break;
                    }
            case 4:
                    {
                      cout << "Select status:" << endl;
                      cout << "1.- Created" << endl;
                      cout << "2.- In progress" << endl;
                      cout << "3.- Completed" << endl;

					  int stat = getMenuChoice(1, 3);
					  switch (stat)
                      {
                          case 1: fdp->setStatus(Created); break;
                          case 2: fdp->setStatus(InProgress); break;
                          case 3: fdp->setStatus(Completed); break;
                      }

                    }
                    break;
            case 5: quit = true; break;

          }

       }


      cout << "Final Degree Project edited." <<endl;
    }
    else
    {
        cout << "No Final Degree Project with that code exists." <<endl;
    }

    saveFDPs();  // Write to file
}

void ResourceManager::editSeminar(const ResCode &code)
{
    Seminar* seminar = getSeminar(code);    // Try to find the seminar
	if (seminar != nullptr)
    {
      bool quit = false;
      while (!quit)
      {
          cout << "Select attribute to edit:" << endl;
          cout << "1.- ID coordinator" << endl;
          cout << "2.- ID of speaker" << endl;
          cout << "3.- Number of seats" << endl;
          cout << "4.- Date" << endl;
          cout << "5.- Status" << endl;
          cout << "6.- Stop editing" << endl;

		  int choice = getMenuChoice(1, 6);
          switch(choice)
          {
            case 1:
                    {
                      cout << "Enter ID of coordinator" << endl;
                      ID coord = getExistingUserFromConsole(Role::Professor);
                      if (!coord.Valid()) { cout << "Seminar edition failed." << endl; return; }
                      seminar->setCoordinatorID(coord);
                      break;
                    }
            case 2:
                    {
                      cout << "Enter ID of speaker" << endl;
                      ID speaker = getExistingUserFromConsole(Role::Professor);
                      if (!speaker.Valid()) { cout << "Seminar edition failed." << endl; return; }
                      seminar->setSpeakerID(speaker);
                      break;
                    }
            case 3:
                    {
                      cout << "Enter new number of seats:" << endl;
                      unsigned int numseats;
                      getInt(&numseats);
                      seminar->setSeats(numseats);
                      break;
                    }
            case 4:
                   {
                      Date newdate;
                      cout << "Enter new date:" << endl;
                      cout << "Year: ";
                      getInt(&newdate.year);

                      bool correctdate = 0;
                      while (correctdate==0)
                      {
                          cout << "Month: ";
                          getInt(&newdate.month);

                          if (newdate.month>0 && newdate.month<=12) {correctdate=1;}
                          else { cout << "Error. please enter a valid date." << endl; }
                      }

                      correctdate = 0;
                      while (correctdate==0)
                      {
                          cout << "Day: ";
                          getInt(&newdate.day);

                          if (newdate.day>0 && newdate.day<=31) {correctdate=1;}
                          else { cout << "Error. please enter a valid date." << endl; }
                      }

                      seminar->setDate(newdate);
                   }
                    break;
            case 5:
                    {
                      cout << "Select status:" << endl;
                      cout << "1.- Created" << endl;
                      cout << "2.- In progress" << endl;
                      cout << "3.- Completed" << endl;

					  int stat = getMenuChoice(1, 3);
					  switch (stat)
                      {
                          case 1: seminar->setStatus(Created); break;
                          case 2: seminar->setStatus(InProgress); break;
                          case 3: seminar->setStatus(Completed); break;
                      }

                    }
                    break;
            case 6: quit = true; break;

          }

       }

      cout << "Seminar edited." <<endl;
    }
    else
    {
        cout << "No seminar with that code exists." <<endl;
    }

    saveSeminars(); // Save to file
}


void ResourceManager::deleteResource()
{
    cout << "Select type of resource to delete:" <<endl;
    cout << "1.- Course" << endl;
    cout << "2.- Final Degree Project (FDP)" << endl;
    cout << "3.- Seminar" << endl;
    
	int choice = getMenuChoice(1, 3);

    cout << "Enter code of the resource to delete:" << endl;
	ResCode code = ResCode::getFromConsole();

	switch (choice)
    {
         case 1:
                {
                    bool found = false;
                    for(auto it=_courselist.begin(); it!=_courselist.end(); it++)
                    {
                        if (it->getCode().Equals(code))
                        {
                            _courselist.erase(it);
                            cout << "Course deleted." << endl;

                            saveCourses(); // Save to file
                            found = true;
                            break;
                        }
                    }
                    if (!found)
                    {
                        cout << "No course with that code exists." << endl;
                    }
                break;
                }


         case 2:
                {
                    bool found = false;
                    for (auto it=_FDPlist.begin(); it!=_FDPlist.end(); it++)
                    {
                        if(it->getCode().Equals(code))
                        {
                            _FDPlist.erase(it);
                            cout << "Final Degree Project deleted." << endl;

                            saveFDPs(); // Save to file
                            found = true;
                            break;
                        }
                    }

                    if(!found)
                    {
                        cout << "No Final Degree Project with that code exists." << endl;
                    }
                break;
                }


         case 3:
                {
                    bool found = false;
                    for (auto it=_seminarlist.begin(); it!=_seminarlist.end(); it++)
                    {
                        if(it->getCode().Equals(code))
                        {
                            _seminarlist.erase(it);
                            cout << "Seminar deleted." << endl;

                            saveSeminars(); // Save to file
                            found = true;
                            break;
                        }
                    }

                    if (!found)
                    {
                        cout << "No seminar with that code exists." << endl;
                    }
                break;
                }

    }
}


void ResourceManager::showResources(const UniversityMember* user)
{
	cout << endl;
    cout << "List of resources:" << endl;
    showCourses(user);
    showFDPs(user);
    showSeminars(user);
}

void ResourceManager::showCourses(const UniversityMember* user)
{
	vector<Course*> enrolled = getEnrolledCourses(user);

	cout << endl;
    cout << "Courses:" << endl;
    for (size_t i=0; i< enrolled.size(); i++)
    {
		Course* course = enrolled[i];

        cout << "\tCourse ID: " << course->getCode().code << endl;
        cout << "\tCourse Name: " << course->getName().c_str() << endl;
        cout << "\tDegree: " << course->getDegree().code << endl;
        cout << "\tNumber of credits: " << course->getCredits() << endl;
        cout << "\tStatus: " << getStatusString(course->getStatus()) << endl;
        cout << "\tID of professors: " << course->getProfessor1ID().id << ", " << course->getProfessor2ID().id << endl;
        cout << endl;
    }
}

void ResourceManager::showFDPs(const UniversityMember* user)
{
	vector<FDP*> enrolled = getEnrolledFDPs(user);

	cout << endl;
    cout << "Final Degree Projects:" << endl;
	for (size_t i = 0; i < enrolled.size(); i++)
	{
		FDP* fdp = enrolled[i];

        cout << "\tFinal Degree Project ID: " << fdp->getCode().code << endl;
        cout << "\tDegree: " << fdp->getDegree().code << endl;
        cout << "\tStatus: " << getStatusString(fdp->getStatus()) << endl;
        cout << "\tTutor: " << fdp->getTutorID().id << endl;
        cout << "\tCo-tutor: " << fdp->getCotutorID().id << endl;
        cout << "\tStudent: " << fdp->getStudentID().id << endl;
        cout << endl;
    }
}

void ResourceManager::showSeminars(const UniversityMember* user)
{
	vector<Seminar*> enrolled = getEnrolledSeminars(user);

	cout << endl;
    cout << "Seminars:" << endl;
	for (size_t i = 0; i < enrolled.size(); i++)
	{
		Seminar* seminar = enrolled[i];

        cout << "\tSeminar ID: " << seminar->getCode().code << endl;
        cout << "\tStatus: " << getStatusString(seminar->getStatus()) << endl;
		const Date date = seminar->getDate();
        cout << "\tDate: " << date.day << "/" << date.month << "/" << date.year << endl;
        cout << "\tNumber of seats: " << seminar->getSeats() << endl;
        cout << "\tSpeaker: " << seminar->getSpeakerID().id << endl;
        cout << "\tCoordinator: " << seminar->getCoordinatorID().id << endl;
		cout << endl;
    }
}


Degree* ResourceManager::getDegree(const ResCode& code)
{
	for (size_t i = 0; i < _degreeList.size(); i++)
	{
		if (_degreeList[i].getCode().Equals(code))
		{
			return &_degreeList[i];
		}
	}
	return nullptr;
}

Course* ResourceManager::getCourse(const ResCode& code)
{
	for (size_t i = 0; i < _courselist.size(); i++)
	{
		if (_courselist[i].getCode().Equals(code))
		{
			return &_courselist[i];
		}
	}
	return nullptr;
}

FDP* ResourceManager::getFDP(const ResCode& code)
{
	for (size_t i = 0; i < _FDPlist.size(); i++)
	{
		if (_FDPlist[i].getCode().Equals(code))
		{
			return &_FDPlist[i];
		}
	}
	return nullptr;
}

Seminar* ResourceManager::getSeminar(const ResCode& code)
{
	for (size_t i = 0; i < _seminarlist.size(); i++)
	{
		if (_seminarlist[i].getCode().Equals(code))
		{
			return &_seminarlist[i];
		}
	}
	return nullptr;
}


vector<Course*> ResourceManager::getEnrolledCourses(const UniversityMember* user)
{
	bool isAdmin = (user->getRole() == Role::Administrator);

	vector<Course*> courses;
    // Gets all courses in which user is enrolled or all if it's an admin
	for (size_t i = 0; i < _courselist.size(); i++)
	{
		Course& course = _courselist[i];
        if (isAdmin || course.isEnrolled(user->getID()))
		{
			courses.push_back(&course);
		}
	}
	return courses;
}

vector<FDP*> ResourceManager::getEnrolledFDPs(const UniversityMember* user)
{
	vector<FDP*> fdps;
	for (size_t i = 0; i < _FDPlist.size(); i++)
	{
		FDP& fdp = _FDPlist[i];

		switch (user->getRole())
		{
			case Role::Student:
                if (fdp.getStudentID().Equals(user->getID()))  // If student is enrolled
				{
					fdps.push_back(&fdp);
				}
				break;
			case Role::Professor:
                if (fdp.getTutorID().Equals(user->getID()) || fdp.getCotutorID().Equals(user->getID())) // If professor is tutor or cututor
				{
					fdps.push_back(&fdp);
				}
				break;
			case Role::Administrator:
                fdps.push_back(&fdp);   // If admin, all FDPs
			default:
				break;
		}
	}
	return fdps;
}

vector<Seminar*> ResourceManager::getEnrolledSeminars(const UniversityMember* user)
{
	bool isAdmin = (user->getRole() == Role::Administrator);

    // Gets all seminars in which user is enrolled or all if it's an admin
	vector<Seminar*> seminars;
	for (size_t i = 0; i < _seminarlist.size(); i++)
	{
		Seminar& seminar = _seminarlist[i];
		if (isAdmin || seminar.isEnrolled(user->getID()))
		{
			seminars.push_back(&seminar);
		}
	}
	return seminars;
}


void ResourceManager::enrollCourse(const Student* student)
{
	cout << endl;
    Degree* degree = getDegree(student->getDegree());   // Get degree of the student
	if (degree != nullptr)
	{
		cout << "Degree: [" << degree->getCode().code << "] " << degree->getName().c_str() << endl;
	}

    // Show courses belonging to student's degree
	cout << "Available courses:" << endl;
	for (size_t i = 0; i < _courselist.size(); i++)
	{
		Course& course = _courselist[i];
		if (course.getDegree().Equals(student->getDegree()) )
		{
			cout << "\tCourse Code: " << course.getCode().code << endl;
			cout << "\tCourse Name: " << course.getName().c_str() << endl;
			cout << "\tNumber of credits: " << course.getCredits() << endl << endl;
		}
	}

	cout << "Enter code of the course to enroll:" << endl;
	ResCode code = ResCode::getFromConsole();

    Course* course = getCourse(code);   // Find course requested
	if (course == nullptr)
	{
		cout << " No course with this id" << endl;
		return;
	}

    if (!course->getDegree().Equals(student->getDegree()))  // In case the student asks for a course from another degree
	{
		cout << " This course is not from this degree" << endl;
		return;
	}

    // Add an empty mark in this course for this student
	Mark mark;
	mark.studentID = student->getID();
	mark.grade = 0.0;
	course->addMark(mark);


	cout << "Enrolled succesfully" << endl;
    saveCourses();  // Save to file
}

void ResourceManager::disenrollCourse(const Student* student)
{
    vector<Course*> courses = getEnrolledCourses(student);  // Gets courses of the student
    if (courses.size() == 0)
    {
        cout << "You are not enrolled in any courses" << endl;
        return;
    }

    // Shows courses in which the student is enrolled
    this->showCourses(student);
	cout << "Enter code of the Course to disenroll:" << endl;
	ResCode code = ResCode::getFromConsole();

    Course* course = getCourse(code);   // Find course to disenroll

	if (course == nullptr)
	{
		cout << " No course with this id" << endl;
		return;
	}

	if (!course->isEnrolled(student->getID()))
	{
		cout << "you are not enrolled in this course" << endl;
		return;
	}

    // Remove student from the course marks
	course->deleteMark(student->getID());
    cout << "Disenrolled succesfully" << endl;
    saveCourses();  // Save to file
}


void ResourceManager::enrollFDP(const Student* student)
{
	cout << endl;

    // Check the student is not already enrolled in a FDP
	if (getEnrolledFDPs(student).size() > 0)
	{
		cout << "This student is already enrolled into a Final Degree Project" << endl;
		cout << "Only one Final Degree Project per student is allowed" << endl;
		return;
	}

	Degree* degree = getDegree(student->getDegree());
	if (degree != nullptr)
	{
		cout << "Degree: [" << degree->getCode().code << "] " << degree->getName().c_str() << endl;
	}

    // Show FDPs in degree of student
	cout << "Available Final Degree Projects:" << endl;
	for (size_t i = 0; i < _FDPlist.size(); i++)
	{
		FDP& fdp = _FDPlist[i];
		if (fdp.getDegree().Equals(student->getDegree()))
		{
			cout << "\tFDP Code: " << fdp.getCode().code << endl;
			cout << "\tTutor: " << fdp.getTutorID().id << endl;
			if (fdp.getCotutorID().Valid())
			{
				cout << "\tCotutor: " << fdp.getCotutorID().id << endl;
			}
		}
	}

	cout << "Enter code of the FDP to enroll:" << endl;
	ResCode code = ResCode::getFromConsole();

	FDP* fdp = getFDP(code);
	if (fdp == nullptr)
	{
		cout << " No FDP with this id" << endl;
		return;
	}

	if (!fdp->getDegree().Equals(student->getDegree()))
	{
		cout << " This FDP is not from this degree" << endl;
		return;
	}

    // Add this student to the FDP
	fdp->setStudentID(student->getID());

	cout << "Enrolled succesfully" << endl;
    saveFDPs(); // Save to file
}

void ResourceManager::disenrollFDP(const Student* student)
{
    // Show FDP of student
    this->showFDPs(student);
	
	vector<FDP*> fdps = getEnrolledFDPs(student);
	if (fdps.size() > 0)
	{
		FDP* fdp = fdps[0];
        // Remove student from the FDP setting an invalid ID
		fdp->setStudentID(ID());
		cout << "Disenrolled student from this FDP" << endl;
        saveFDPs(); // Save to file
	}
    else
    {
        cout << "You are not enrolled in any FDP" << endl;
    }
}


void ResourceManager::enrollSeminar(const Student* student)
{
	cout << endl;
	cout << "Available seminars:" << endl;
    // Show seminars with free seats
	for (size_t i = 0; i < _seminarlist.size(); i++)
	{
		Seminar& seminar = _seminarlist[i];
		if (seminar.getFreeSeats() > 0)
		{
			cout << "\tSeminar Code: " << seminar.getCode().code << endl;
			cout << "\tSeminar Coordinator: " << seminar.getCoordinatorID().id << endl;
			cout << "\tSeminar Speaker: " << seminar.getSpeakerID().id << endl;
			const Date date = seminar.getDate();
			cout << "\tSeminar Date: " << date.year << "/" << date.month << "/" << date.day << endl;
			cout << "\tAvailable Seats: " << seminar.getFreeSeats() << "/" << seminar.getSeats();
			cout << endl;
		}
	}

	cout << "Enter code of the seminar to enroll:" << endl;
	ResCode code = ResCode::getFromConsole();

	Seminar* seminar = getSeminar(code);
	if (seminar == nullptr)
	{
		cout << " No seminar with this id" << endl;
		return;
	}

	if (seminar->getFreeSeats() <= 0)
	{
		cout << " This seminar does not have free seats" << endl;
		return;
	}

    // Add student to seminar attendants list
	seminar->getEnrolledList().addAttendant(student->getID());

	cout << "Enrolled succesfully" << endl;
    saveSeminars(); // Save to file
}

void ResourceManager::disenrollSeminar(const Student* student)
{
    vector<Seminar*> seminars = getEnrolledSeminars(student);
    if (seminars.size() == 0)
    {
        cout << "You are not enrolled in any seminars" << endl;
        return;
    }

    // Show seminars the student has enrolled
    this->showSeminars(student);
	cout << "Enter code of the Seminar to disenroll:" << endl;
	ResCode code = ResCode::getFromConsole();

	Seminar* seminar = getSeminar(code);

	if (seminar == nullptr)
	{
		cout << " No seminar with this id" << endl;
		return;
	}

	if (!seminar->isEnrolled(student->getID()))
	{
		cout << "you are not enrolled in this seminar" << endl;
		return;
	}

    // Remove student from the seminar
	seminar->getEnrolledList().removeAttendant(student->getID());
    cout << "Disenrolled succesfully" << endl;
    saveSeminars(); // Save to file
}


bool ResourceManager::userExists(const ID& id, Role role)
{
	switch (role)
	{
		case Role::Administrator: 
			return _campus.getUserManager()->getAdmin(id) != nullptr;
			break;
		case Role::Professor: 
			return _campus.getUserManager()->getProfessor(id) != nullptr;
			break;
		case Role::Student: 
			return _campus.getUserManager()->getStudent(id) != nullptr;
			break;
		case Role::Any:
			return _campus.getUserManager()->getUser(id) != nullptr;
			break;
	}

	return false;
}

ID ResourceManager::getExistingUserFromConsole(Role role, bool optional)
{
	int tries = 3;
	ID id;
	do
	{
        id = ID::getFromConsole(optional);
        if(optional && id.Equals(ID()))
        {return id;}

        if (userExists(id, role))
		{ return id; } 
		else
		{
			cout << "The user does not exist. Try again:" << endl;
		}
    } while(--tries > 0);

	return ID();
}

ResCode ResourceManager::getExistingDegreeFromConsole()
{
	int tries = 3;
	ResCode code;
	do
	{
		code = ResCode::getFromConsole();
		if (getDegree(code) != nullptr)
		{ return code; }
		else
		{
			cout << "The degree does not exist. Try again:" << endl;
		}
    } while (--tries > 0);

	return ResCode();
}

void ResourceManager::saveCourses()
{
    FileWriter courseWriter("courses.bin");
    courseWriter.writeall<Course>(_courselist);
}

void ResourceManager::saveFDPs()
{
    FileWriter FDPWriter("FDPs.bin");
    FDPWriter.writeall<FDP>(_FDPlist);
}

void ResourceManager::saveSeminars()
{
    FileWriter seminarWriter("seminars.bin");
    seminarWriter.writeall<Seminar>(_seminarlist);
}

ResCode ResourceManager::createResCode()
{

    _RCgenerator.code[6]++;   // Increment code

    // Reset code if all codes are taken (not expected with our volume of data)
    if (_RCgenerator.code[0] == 'Z'+1)
    {
        _RCgenerator.code[0] = 'A' ;
    }

    //  Maintain range of valid values (after 9 go back to 0, after Z go back to A)
    for( int i=6; i>0; i--)
    {
        if (_RCgenerator.code[i] == '9'+1)
        {
            _RCgenerator.code[i] = '0';
            _RCgenerator.code[i-1]++;
        }
        else if (_RCgenerator.code[i] == 'Z'+1)
        {
            _RCgenerator.code[i] = 'A';
            _RCgenerator.code[i-1]++;
        }
    }

    return _RCgenerator;
}
