#include "resourcemanager.h"
#include <iostream>
#include <algorithm>
#include <cstring>
#include "filereader.h"
#include "filewriter.h"

ResourceManager::ResourceManager()
{
    _RCgenerator = { { 'A', 'A', 'A', '0', '0', '0', '0', 0 } };

    FileReader RCReader("rescode.bin");
    RCReader.readCode(_RCgenerator.full);

    FileReader degreeReader("degrees.bin");
    degreeReader.readall<Degree>(_degreeList);

    FileReader courseReader("courses.bin");
    courseReader.readall<Course>(_courselist);

    FileReader FDPReader("FDPs.bin");
    FDPReader.readall<FDP>(_FDPlist);

    FileReader seminarReader("seminars.bin");
    seminarReader.readall<Seminar>(_seminarlist);
}

ResourceManager::~ResourceManager()
{
    FileWriter RCWriter("rescode.bin");
    RCWriter.writeCode(_RCgenerator.full);
}

void ResourceManager::createResource()
{
           cout << "Select type of resource to create:" <<endl;
           cout << "1.- Course" << endl;
           cout << "2.- Final Degree Project (FDP)" << endl;
           cout << "3.- Seminar" << endl;
           cout << "4.- Degree" << endl;
           int sel;
           getInt(&sel);
           switch(sel)
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

    FileWriter degreeWriter("degrees.bin");
    degreeWriter.writeall<Degree>(_degreeList);
}

void ResourceManager::createCourse()        // MODIFICADO
{
    char name[255];
    cout << "Introduce the name of the course" << endl;
    getText(name, sizeof(name));
    cout << "Introduce the code of the degree of the course" << endl;
    ResCode degreecode;
    getText(degreecode.full, sizeof(degreecode.full));
    cout << "Introduce ID of first professor" << endl;
    ID prof1 = ID::getFromConsole();
    cout << "Introduce ID of second professor" << endl;
    ID prof2 = ID::getFromConsole();
    unsigned int credits;
    cout << "Number of credits:" << endl;
    getInt(&credits);

    ResCode code = createResCode();
    Course course(code, name, degreecode, prof1, prof2, credits);      //MODIFICADO
    _courselist.push_back(course);
    cout << "Created course with resource code " << code.full << endl;

    FileWriter courseWriter("courses.bin");
    courseWriter.writeall<Course>(_courselist);
}

void ResourceManager::createFDP()
{
    cout << "Introduce the code of the degree of the course" << endl;
    ResCode degreecode;
    getText(degreecode.full, sizeof(degreecode.full));
    cout << "Introduce ID of student" << endl;
    ID student = ID::getFromConsole();
    cout << "Introduce ID of tutor" << endl;
    ID tutor = ID::getFromConsole();
    cout << "Introduce ID of cotutor (optional)" << endl;
    ID cotutor = ID::getFromConsole();

    ResCode code = createResCode();
    FDP fdp(code, degreecode, student, tutor, cotutor);
    _FDPlist.push_back(fdp);
    cout << "Created Final Degree Project with resource code " << code.full << endl;

    FileWriter FDPWriter("FDPs.bin");
    FDPWriter.writeall<FDP>(_FDPlist);
}

void ResourceManager::createSeminar()
{
    cout << "Introduce ID of coordinator" << endl;
    ID coord = ID::getFromConsole();
    cout << "Introduce ID of speaker" << endl;
    ID speaker = ID::getFromConsole();
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
    cout << "Created seminar with resource code " << code.full << endl;

    FileWriter seminarWriter("seminars.bin");
    seminarWriter.writeall<Seminar>(_seminarlist);
}

void ResourceManager::editResource()
{
    cout << "Select type of resource to edit:" <<endl;
    cout << "1.- Course" << endl;
    cout << "2.- Final Degree Project (FDP)" << endl;
    cout << "3.- Seminar" << endl;
    int sel;
    getInt(&sel);

    cout << "Enter code of the resource to edit:" << endl;
    ResCode codecheck;
    getText(codecheck.full, sizeof(codecheck.full));

    switch(sel)
    {
         case 1: editCourse(codecheck); break;
         case 2: editFDP(codecheck); break;
         case 3: editSeminar(codecheck); break;
    }
}

void ResourceManager::editCourse(const ResCode &code)
{
    // 'it' iterates over all the resources (courses) in the list of courses and compares their code to the code of the resource to edit
    // once it is found this Course is assigned to 'course'
    auto it = find_if(_courselist.begin(), _courselist.end(), [&code](const Resource& resource) {return strcmp(resource.getCode().full, code.full) == 0;});

    if (it != _courselist.end())
    {
      Course& course = *it;
      bool quit = 0;
      while (quit == 0)
      {
          cout << "Select attribute to edit:" << endl;
          cout << "1.- ID of professor 1" << endl;
          cout << "2.- ID of professor 2" << endl;
          cout << "3.- Number of credits" << endl;
          cout << "4.- Status" << endl;
          cout << "5.- Stop editing" << endl;

          int sel;
          getInt(&sel);

          switch(sel)
          {
            case 1:   cout << "Enter ID of first professor" << endl;
                      course.setProfessor1ID(ID::getFromConsole());
                      break;
            case 2:   cout << "Enter ID of second professor" << endl;
                      course.setProfessor2ID(ID::getFromConsole());
                      break;
            case 3:   cout << "Enter new number of credits:" << endl;
                      unsigned int credits;
                      getInt(&credits);
                      course.setCredits(credits);
                      break;
            case 4:
                    {
                      cout << "Select status:" << endl;
                      cout << "1.- Created" << endl;
                      cout << "2.- In progress" << endl;
                      cout << "3.- Completed" << endl;
                      int stat;
                      getInt(&stat);

                      switch(stat)
                      {
                          case 1: course.setStatus(Created); break;
                          case 2: course.setStatus(InProgress); break;
                          case 3: course.setStatus(Completed); break;
                      }

                    }
                    break;
            case 5: quit = 1; break;

          }

       }


      cout << "Course edited." <<endl;
    }
    else
    {
        cout << "No course with that code exists." <<endl;
    }

    FileWriter courseWriter("courses.bin");
    courseWriter.writeall<Course>(_courselist);

}

void ResourceManager::editFDP(const ResCode &code)
{
    auto it = find_if(_FDPlist.begin(), _FDPlist.end(), [&code](const Resource& resource) {return strcmp(resource.getCode().full, code.full) == 0;});

    if (it != _FDPlist.end())
    {
      FDP& fdp = *it;

      bool quit = 0;
      while (quit == 0)
      {
          cout << "Select attribute to edit:" << endl;
          cout << "1.- ID of student" << endl;
          cout << "2.- ID of tutor" << endl;
          cout << "3.- ID of cotutor" << endl;
          cout << "4.- Status" << endl;
          cout << "5.- Stop editing" << endl;

          int sel;
          getInt(&sel);

          switch(sel)
          {
            case 1:   cout << "Enter ID of student" << endl;
                      fdp.setStudentID(ID::getFromConsole());
                      break;
            case 2:   cout << "Enter ID of tutor" << endl;
                      fdp.setTutorID(ID::getFromConsole());
                      break;
            case 3:   cout << "Enter ID of cotutor" << endl;
                      fdp.setCotutorID(ID::getFromConsole());
                      break;
            case 4:
                    {
                      cout << "Select status:" << endl;
                      cout << "1.- Created" << endl;
                      cout << "2.- In progress" << endl;
                      cout << "3.- Completed" << endl;
                      int stat;
                      getInt(&stat);

                      switch(stat)
                      {
                          case 1: fdp.setStatus(Created); break;
                          case 2: fdp.setStatus(InProgress); break;
                          case 3: fdp.setStatus(Completed); break;
                      }

                    }
                    break;
            case 5: quit = 1; break;

          }

       }


      cout << "Final Degree Project edited." <<endl;
    }
    else
    {
        cout << "No Final Degree Project with that code exists." <<endl;
    }

    FileWriter FDPWriter("FDPs.bin");
    FDPWriter.writeall<FDP>(_FDPlist);
}
void ResourceManager::editSeminar(const ResCode &code)
{
    auto it = find_if(_seminarlist.begin(), _seminarlist.end(), [&code](const Resource& resource) { return strcmp(resource.getCode().full, code.full) == 0;});

    if (it != _seminarlist.end())
    {
      Seminar& seminar = *it;

      bool quit = 0;
      while (quit == 0)
      {
          cout << "Select attribute to edit:" << endl;
          cout << "1.- ID coordinator" << endl;
          cout << "2.- ID of speaker" << endl;
          cout << "3.- Number of seats" << endl;
          cout << "4.- Date" << endl;
          cout << "5.- Status" << endl;
          cout << "6.- Stop editing" << endl;

          int sel;
          getInt(&sel);

          switch(sel)
          {
            case 1:   cout << "Enter ID of coordinator" << endl;
                      seminar.setCoordinatorID(ID::getFromConsole());
                      break;
            case 2:   cout << "Enter ID of speaker" << endl;
                      seminar.setSpeakerID(ID::getFromConsole());
                      break;
            case 3:   cout << "Enter new number of seats:" << endl;
                      unsigned int numseats;
                      getInt(&numseats);
                      seminar.setSeats(numseats);
                      break;
            case 4:
                   {
                      Date newdate;
                      unsigned int day, month, year;
                      cout << "Enter new year:" << endl;
                      getInt(&year);
                      cout << "Enter new month:" << endl;
                      getInt(&month);
                      cout << "Enter new day:" << endl;
                      getInt(&day);
                      newdate.day = day;
                      newdate.month = month;
                      newdate.year = year;
                      seminar.setDate(newdate);
                   }
                    break;
            case 5:
                    {
                      cout << "Select status:" << endl;
                      cout << "1.- Created" << endl;
                      cout << "2.- In progress" << endl;
                      cout << "3.- Completed" << endl;
                      int stat;
                      getInt(&stat);

                      switch(stat)
                      {
                          case 1: seminar.setStatus(Created); break;
                          case 2: seminar.setStatus(InProgress); break;
                          case 3: seminar.setStatus(Completed); break;
                      }

                    }
                    break;
            case 6: quit = 1; break;

          }

       }

      cout << "Seminar edited." <<endl;
    }
    else
    {
        cout << "No seminar with that code exists." <<endl;
    }

    FileWriter seminarWriter("seminars.bin");
    seminarWriter.writeall<Seminar>(_seminarlist);
}

void ResourceManager::deleteResource()
{
    cout << "Select type of resource to delete:" <<endl;
    cout << "1.- Course" << endl;
    cout << "2.- Final Degree Project (FDP)" << endl;
    cout << "3.- Seminar" << endl;
    int sel;
    getInt(&sel);

    cout << "Enter code of the resource to delete:" << endl;
    ResCode code;
    getText(code.full, sizeof(code.full));

    switch(sel)
    {
         case 1:
                {
                    auto it = find_if(_courselist.begin(), _courselist.end(), [&code](const Resource& resource) {return strcmp(resource.getCode().full, code.full) == 0;});

                    if (it != _courselist.end())
                    {
                            _courselist.erase(it);
                            cout << "Course deleted." << endl;

                            FileWriter courseWriter("courses.bin");
                            courseWriter.writeall<Course>(_courselist);
                    }
                    else
                    {
                        cout << "No course with that code exists." << endl;
                    }
                }
                        break;

         case 2:
                {
                    auto it = find_if(_FDPlist.begin(), _FDPlist.end(), [&code](const Resource& resource) {return strcmp(resource.getCode().full, code.full) == 0;});

                    if (it != _FDPlist.end())
                    {
                            _FDPlist.erase(it);
                            cout << "Final Degree Project deleted." << endl;

                            FileWriter FDPWriter("FDPs.bin");
                            FDPWriter.writeall<FDP>(_FDPlist);
                    }
                    else
                    {
                        cout << "No Final Degree Project with that code exists." << endl;
                    }
                }

                        break;
         case 3:
                {
                    auto it = find_if(_seminarlist.begin(), _seminarlist.end(), [&code](const Resource& resource) {return strcmp(resource.getCode().full, code.full) == 0;});

                    if (it != _seminarlist.end())
                    {
                            _seminarlist.erase(it);
                            cout << "Seminar deleted." << endl;

                            FileWriter seminarWriter("seminars.bin");
                            seminarWriter.writeall<Seminar>(_seminarlist);
                    }
                    else
                    {
                        cout << "No seminar with that code exists." << endl;
                    }
                }
                        break;
    }
}


void ResourceManager::showResources()
{
    cout << "List of resources:" << endl;
    showCourses();
    showFDPs();
    showSeminars();
}

void ResourceManager::showCourses()
{
    cout << "Courses:" << endl;
    for (size_t i=0; i<_courselist.size(); i++)
    {
        cout << "\tCourse ID: " << _courselist[i].getCode().full << endl;
        cout << "\tCourse Name: " << _courselist[i].getname() << endl;
        // Degree
        cout << "\tNumber of credits: " << _courselist[i].getCredits() << endl;
        cout << "\tStatus: " << getStatusString(_courselist[i].getStatus()) << endl;
        cout << "\tID of professors: " << _courselist[i].getProfessor1ID().id << ", " << _courselist[i].getProfessor2ID().id << endl << endl;
    }
}

void ResourceManager::showFDPs()
{
    cout << "Final Degree Projects:" << endl;
    for (size_t i=0; i<_FDPlist.size(); i++)
    {
        cout << "\tFinal Degree Project ID: " << _FDPlist[i].getCode().full << endl;
        //Degree
        cout << "\tStatus: " << getStatusString(_FDPlist[i].getStatus()) << endl;
        cout << "\tTutor: " << _FDPlist[i].getTutorID().id << endl;
        if (_FDPlist[i].getTutorID().Valid())
        {
            cout << "\tCo-tutor: " << _FDPlist[i].getCotutorID().id << endl;
        }
        cout << "\tStudent: ";
        if (_FDPlist[i].getStudentID().Valid())
        {
            cout << _FDPlist[i].getStudentID().id << endl;
        }
        else
        {
            cout << "Not assigned" << endl;
        }
    }
}

void ResourceManager::showSeminars()
{
    cout << "Seminars:" << endl;
    for (size_t i=0; i<_seminarlist.size(); i++)
    {
        cout << "\tSeminar ID: " << _seminarlist[i].getCode().full << endl;
        cout << "\tStatus: " << getStatusString(_seminarlist[i].getStatus()) << endl;
        cout << "\tDate: " << _seminarlist[i].getDate().day << "/" << _seminarlist[i].getDate().month << "/" << _seminarlist[i].getDate().year << endl;
        cout << "\tNumber of seats: " << _seminarlist[i].getSeats() << endl;
        cout << "\tSpeaker: " << _seminarlist[i].getSpeakerID().id << endl;
        cout << "\tCoordinator: " << _seminarlist[i].getCoordinatorID().id << endl;
    }
}

ResCode ResourceManager::createResCode()
{

    _RCgenerator.full[6]++;

    // Reset code if all codes are taken (not expected with our volume of data)
    if (_RCgenerator.full[0] == 'Z'+1)
    {
        _RCgenerator.full[0] = 'A' ;
    }

    // Increment code (numbers and letters)
    for( int i=6; i>0; i--)
    {
        if (_RCgenerator.full[i] == '9'+1)
        {
            _RCgenerator.full[i] = '0';
            _RCgenerator.full[i-1]++;
        }
        else if (_RCgenerator.full[i] == 'Z'+1)
        {
            _RCgenerator.full[i] = 'A';
            _RCgenerator.full[i-1]++;
        }
    }

    return _RCgenerator;
}
