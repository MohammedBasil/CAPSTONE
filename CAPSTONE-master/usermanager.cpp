#include "usermanager.h"
#include <iostream>
#include <algorithm>
#include <cstring>
#include "commons.h"
#include "degree.h"
#include "filereader.h"
#include "filewriter.h"

UserManager::UserManager()
{
    _SINgenerator = { { '0', '0', '0', '0', '0', '0', '0', 0 } };
    _IDgenerator = { { 'A', 'A', 'A', 'A', 'A', 'A', 'A', 0 } };

    FileReader IDReader("indexes.bin");
    IDReader.readCode(_SINgenerator.id);
    IDReader.readCode(_IDgenerator.id);

    FileReader profReader("professors.bin");
    profReader.readall<Professor>(_proflist);

    FileReader adminReader("administrators.bin");
    adminReader.readall<Administrator>(_adminlist);

    FileReader studentReader("students.bin");
    studentReader.readall<Student>(_studlist);
}

UserManager::~UserManager()
{
    FileWriter IDWriter("indexes.bin");
    IDWriter.writeCode(_SINgenerator.id);
    IDWriter.writeCode(_IDgenerator.id);
}

void UserManager::createUser()
{
           cout << "Select type of member to create:" <<endl;
           cout << "1.- Professor" << endl;
           cout << "2.- Student" << endl;
           cout << "3.- Administrator" << endl;
           int sel;
           getInt(&sel);
           switch(sel)
           {
                case 1: createProfessor(); break;
                case 2: createStudent(); break;
                case 3: createAdmin(); break;
           }
}

void UserManager::createProfessor()
{
    ID identification=createID();
    char pass[32]{0};
    cout << "Please enter a password of less than 32 characters for the new Professor" << endl;
    getText(pass, sizeof(pass));
    Professor prof(identification, pass);
    _proflist.push_back(prof);
    cout << "Created professor with ID " << identification.id  << " and password " << pass << endl;

    FileWriter profWriter( "professors.bin");
    profWriter.writeall<Professor>(_proflist);
}


void UserManager::createAdmin()
{
    ID identification=createID();
    char pass[32];
    cout << "Please enter a password of less than 32 characters for the new Administrator" << endl;
    getText(pass, sizeof(pass));
    Administrator admin(identification, pass);
    _adminlist.push_back(admin);
    cout << "Created administrator with ID " << identification.id << " and password " << pass << endl;

    FileWriter adminWriter( "administrators.bin");
    adminWriter.writeall<Administrator>(_adminlist);
}

void UserManager::createStudent()
{
    ID identification=createSIN();
    char pass[32]; 
    cout << "Please enter a password of less than 32 characters for the new Student" << endl;
    getText(pass, sizeof(pass));
    cout << "Introduce the code of the degree of the course" << endl;
    ResCode degreecode;
    getText(degreecode.full, sizeof(degreecode.full));
    Student stud(identification, pass, degreecode);
    _studlist.push_back(stud);
    cout << "Created Student with SIN " << identification.id << " and password " << pass << endl;

    FileWriter studentWriter( "students.bin");
    studentWriter.writeall<Student>(_studlist);
}

void UserManager::editUser()
{
    cout << "Select type of member to edit:" <<endl;
    cout << "1.- Professor" << endl;
    cout << "2.- Student" << endl;
    cout << "3.- Administrator" << endl;
    int sel;
    getInt(&sel);
    ID identification;

    cout << "Please enter the ID or SIN of the User" << endl;
    getText(identification.id, sizeof(identification.id));

           switch(sel)
           {
                case 1: editProfessor(identification); break;
                case 2: editStudent(identification); break;
                case 3: editAdmin(identification); break;
           }
}


void UserManager::editProfessor(const ID &id){
    auto it=find_if(_proflist.begin(), _proflist.end(), [&id](const Professor &p){return strcmp(p.getID().id, id.id)==0;});
    char pass[32]{0};
    if (it!=_proflist.end()){
        Professor& professor=*it;
        bool quit = 0;
        while(quit==0){
            cout << "Select attribute to edit: " << endl;
            cout << "1.- Password" << endl;
            cout << "2.- Quit" << endl;

            int sel;
            getInt(&sel);

            switch (sel) {
            case 1: cout << "Enter the new password for the user: " << professor.getID().id << endl;
                    getText(pass, sizeof(pass));
                    professor.setPassword(pass);
                    cout << "New pass for professor: " <<  professor.getID().id << " is: " << professor.getPassword() << endl;
                break;
            case 2: quit=1;
                break;
            default: quit=1;
                break;
            }
        }
    }else{
        cout << "The user you have requested does not exist, please check the ID" << endl;
    }

    FileWriter profWriter( "professors.bin");
    profWriter.writeall<Professor>(_proflist);
}



void UserManager::editStudent(const ID &id){
    auto it=find_if(_studlist.begin(), _studlist.end(), [&id](const Student &s){return strcmp(s.getID().id, id.id)==0;});
    if (it!=_studlist.end()){
        Student& student=*it;
        bool quit=0;
        while(quit==0){
            cout << "Select attribute to edit:" << endl;
            cout << "1.- Password" << endl;
            cout << "2.- Degree" << endl;
            cout << "3.- Quit" << endl;

            int sel;
            getInt(&sel);

            switch (sel) {
            case 1: cout << "Enter the new password for the user: " << student.getID().id << endl;
                char pass[32];
                getText(pass, sizeof(pass));
                student.setPassword(pass);
                break;
            case 2: cout << "Enter the code of the new Degree for the student: " << student.getID().id << endl;
                ResCode degreecode;
                getText(degreecode.full, sizeof(degreecode.full));
                student.setDegree(degreecode);
                break;
            case 3: quit=1;
                break;
            }
        }
    }else{
        cout << "The user you have requested does not exist, please check the ID" << endl;
    }

    FileWriter studentWriter( "students.bin");
    studentWriter.writeall<Student>(_studlist);
}


void UserManager::editAdmin(const ID &id){
    auto it=find_if(_adminlist.begin(), _adminlist.end(), [&id](const Administrator &a){return strcmp(a.getID().id, id.id)==0;});

    if (it!=_adminlist.end()){
        Administrator& admin=*it;
        bool quit=0;
        while(quit==0){
            cout << "Select attribute to edit:" << endl;
            cout << "1.- Password" << endl;
            cout << "2.- Quit" << endl;

            int sel;
            getInt(&sel);

            switch (sel) {
            case 1: cout << "Enter the new password for the user: " << admin.getID().id << endl;
                char pass[32];
                getText(pass, sizeof(pass));
                admin.setPassword(pass);
                break;

            case 2: quit=1;
                break;
            }
        }
    }else{
        cout << "The user you have requested does not exist, please check the ID" << endl;
    }

    FileWriter adminWriter( "administrators.bin");
    adminWriter.writeall<Administrator>(_adminlist);
}



void UserManager::deleteUser()
{
    cout << "Select type of user to delete:" <<endl;
    cout << "1.- Professor" << endl;
    cout << "2.- Student" << endl;
    cout << "3.- Administrator" << endl;
    int sel;
    getInt(&sel);

    cout << "Enter ID of the user to delete:" << endl;
    ID identification;
    getText(identification.id, sizeof(identification.id));

    switch(sel)
    {
         case 1:
                {
                    auto it = find_if(_proflist.begin(), _proflist.end(), [&identification](const Professor& professor) {return strcmp(professor.getID().id, identification.id) == 0;});

                    if (it != _proflist.end())
                    {
                            _proflist.erase(it);
                            cout << "User "<< identification.id << " deleted." << endl;

                            FileWriter profWriter( "professors.bin");
                            profWriter.writeall<Professor>(_proflist);
                    }
                    else
                    {
                        cout << "No user with that ID exists." << endl;
                    }
                }
                        break;

         case 2:
                {
                    auto it = find_if(_studlist.begin(), _studlist.end(), [&identification](const Student& student) {return strcmp(student.getID().id, identification.id) == 0;});

                    if (it != _studlist.end())
                    {
                            _studlist.erase(it);
                            cout << "User "<< identification.id << " deleted." << endl;

                            FileWriter studentWriter( "students.bin");
                            studentWriter.writeall<Student>(_studlist);
                    }
                    else
                    {
                        cout << "No user with that ID exists." << endl;
                    }
                }
                        break;
         case 3:
                {
                    auto it = find_if(_adminlist.begin(), _adminlist.end(), [&identification](const Administrator& administrator) {return strcmp(administrator.getID().id, identification.id) == 0;});

                    if (it != _adminlist.end())
                    {
                            _adminlist.erase(it);
                            cout << "User "<< identification.id << " deleted." << endl;

                            FileWriter adminWriter( "administrators.bin");
                            adminWriter.writeall<Administrator>(_adminlist);
                    }
                    else
                    {
                        cout << "No user with that ID exists." << endl;
                    }
                }
                        break;
    }



}


void UserManager::showUsers()
{
    cout << "List of Users:" << endl;
    showProfessors();
    showStudents();
    showAdmins();

}
void UserManager::showProfessors()
{
    cout << " Professors: " << endl;
    for (unsigned int i=0; i<_proflist.size(); i++){
        cout << "\t Professor ID: " << _proflist[i].getID().id << endl;
        cout << "\t Password: " << _proflist[i].getPassword() << endl;
    }
}


void UserManager::showStudents()
{
    cout << " Students: " << endl;
    for (unsigned int i=0; i<_studlist.size(); i++){
        cout << "\t Student SIN: " << _studlist[i].getID().id << endl;
        cout << "\t Password: " << _studlist[i].getPassword() << endl;
        cout << "\t Degree: " << _studlist[i].getDegree().full << endl;
//        cout << "\t The courses that student: " << _studlist[i].getID().id << " is enrolling are" << endl;
//        _studlist[i].printCourses();
    }
}


void UserManager::showAdmins()
{
    cout << " Administrators: " << endl;
    for (unsigned int i=0; i<_adminlist.size(); i++){
        cout << "\t Administrator ID: " << _adminlist[i].getID().id << endl;
        cout << "\t Password: " << _adminlist[i].getPassword() << endl;
    }
}


ID UserManager::createSIN()
{

    _SINgenerator.id[6]++;

    // Reset code if all codes are taken (not expected with our volume of data)
    if (_SINgenerator.id[0] == '9'+1)
    {
        _SINgenerator.id[0] = '0' ;
    }

    // Increment code (numbers and letters)
    for( int i=6; i>0; i--)
    {
        if (_SINgenerator.id[i] == '9'+1)
        {
            _SINgenerator.id[i] = '0';
            _SINgenerator.id[i-1]++;
        }

    }

    return _SINgenerator;
}

ID UserManager::createID()
{

    _IDgenerator.id[6]++;

    if (_IDgenerator.id[0] == 'Z'+1)
    {
        _IDgenerator.id[0] = 'A' ;
    }

    for( int i=6; i>0; i--)
    {
        if (_IDgenerator.id[i] == 'Z'+1)
        {
            _IDgenerator.id[i] = 'A';
            _IDgenerator.id[i-1]++;
        }

    }

    return _IDgenerator;
}


//Student UserManager::checkstudent(const ID idstud, bool *check){
//    *check=0;
//    unsigned int r;
//    for (unsigned int i=0; i<_studlist.size(); i++){
//        if (strcmp(idstud.id, _studlist[i].getID().id)==0){
//            r=i;
//            *check=0;
//            break;
//        } else{
//            *check=1;
//        }

//    }
//    return _studlist[r];
//}

Student* UserManager::getStudent(const ID &id)
{
        for (unsigned int i=0; i<_studlist.size(); i++)
        {
            if (strcmp(id.id, _studlist[i].getID().id)==0)
            {
                return &_studlist[i];
            }
        }
        return nullptr;
}

Professor* UserManager::getProfessor(const ID &id)
{
        for (unsigned int i=0; i<_proflist.size(); i++)
        {
            if (strcmp(id.id, _proflist[i].getID().id)==0)
            {
                return &_proflist[i];
            }
        }
        return nullptr;
}


Administrator* UserManager::getAdmin(const ID &id)
{
        for (unsigned int i=0; i<_adminlist.size(); i++)
        {
            if (strcmp(id.id, _adminlist[i].getID().id)==0)
            {
                return &_adminlist[i];
            }
        }
        return nullptr;
}




int UserManager::login(){

    ID identification;
    char pass[32];
    UniversityMember *user;
    int mode=-1; // admin=0   professor=1    student=2
    if (_studlist.size()==0 && _adminlist.size()==0 && _proflist.size()==0){
        mode=0;
    } else {
    cout << "Please enter your ID:" << endl;
    getText(identification.id, sizeof(identification.id));
    user=this->getAdmin(identification);
    if (user==nullptr) {
        user=this->getProfessor(identification);
        if (user==nullptr) {
            user=this->getStudent(identification);
            if (user==nullptr){
                cout << "No user with ID " << identification.id << " found." << endl;
                mode=-1;
            }else{
                cout << "Please enter your password:" << endl;
                getText(pass, sizeof(pass));
                if (strcmp(pass, user->getPassword())==0){
                    cout << "SUCCESSFUL LOGIN" << endl << endl;
                    mode=2;
                }
            }
        } else {
            cout << "Please enter your password:" << endl;
            getText(pass, sizeof(pass));
            if (strcmp(pass, user->getPassword())==0){
                cout << "SUCCESSFUL LOGIN" << endl << endl;
                mode=1;
            }}
    } else {
        cout << "Please enter your password:" << endl;
        getText(pass, sizeof(pass));
        if (strcmp(pass, user->getPassword())==0){
            cout << "SUCCESSFUL LOGIN" << endl << endl;
            mode=0;
        }
    }
  } return mode;
}
