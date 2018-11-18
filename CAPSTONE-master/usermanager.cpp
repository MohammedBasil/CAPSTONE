#include "usermanager.h"
#include <iostream>
#include <algorithm>
#include <cstring>
#include "commons.h"
#include "degree.h"

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
    char pass[32];
    cout << "please enter a password of less than 32 characters for the new Professor" << endl;
    getText(pass, sizeof(pass));
    Professor prof(id, pass);
    prof.setRole();
    _proflist.push_back(prof);
    cout << "Created professor with ID " << identification.id  << "and password " << pass << endl;
}


void UserManager::createAdmin()
{
    ID identification=createID();
    char pass[32];
    cout << "please enter a password of less than 32 characters for the new Administrator" << endl;
    getText(pass, sizeof(pass));
    Administrator admin(id, pass);
    prof.setRole();
    _adminlist.push_back(admin);
    cout << "Created administrator with ID " << identification.id << "and password " << pass << endl;
}

void UserManager::createStudent()
{
    ID identification=createSIN();
    char pass[32];
    string degname;
    Degree degree;
    cout << "please enter a password of less than 32 characters for the new Student" << endl;
    getText(pass, sizeof(pass));
    cout << "please enter the degree for the new Student" << endl;
    cin >> degname;
    degree.setname(degname);
    Student stud(id, pass, degree);
    stud.setRole();
    _adminlist.push_back(stud);
    cout << "Created Student with SIN " << identification.id << "and password " << pass << endl;
}

void UserManager::editUser()
{
    cout << "Select type of member to create:" <<endl;
    cout << "1.- Professor" << endl;
    cout << "2.- Student" << endl;
    cout << "3.- Administrator" << endl;
    int sel;
    getInt(&sel);
    ID identification;

    cout << "please enter the ID or SIN of the User" << endl;
    getText(identification.id, sizeof(identification.id));

           switch(sel)
           {
                case 1: editProfessor(identification); break;
                case 2: editStudent(identification); break;
                case 3: editAdmin(identification); break;
           }
}


void UserManager::editProfessor(const ID &id){
    auto it=find_if(_proflist.begin(), _proflist.end(), [&id](const UniversityMember &member){return strcmp(member.getID().id, id.id)==0;});

    if (it!=_proflist.end()){
        Professor& professor=*it;
        bool quit;
        while(quit=0){
            cout << "Select attribute to edit:" << endl;
            cout << "1.- Password" << endl;

            int sel;
            getInt(&sel);

            switch (sel) {
            case 1: cout << "enter the new password for the user:" << professor.getID().id << endl;

                break;
            default: quit=1;
                break;
            }
        }
    }else{
        cout << "the user you have requested does not exist, please check the ID" << endl;
    }
}



void UserManager::editStudent(const ID &id){
    auto it=find_if(_studlist.begin(), _studlist.end(), [&id](const UniversityMember &member){return strcmp(member.getID().id, id.id)==0;});

    if (it!=_studlist.end()){
        Student& student=*it;
        bool quit;
        while(quit=0){
            cout << "Select attribute to edit:" << endl;
            cout << "1.- Password" << endl;
            cout << "2.- Degree" << endl;

            int sel;
            getInt(&sel);

            switch (sel) {
            case 1: cout << "enter the new password for the user:" << student.getID().id << endl;
                char pass[32];
                getText(pass, sizeof(pass));
                student.setPassword(pass);
                break;
            case 2: cout << "enter the new Degree for the student:" << student.getID().id << endl;
                string degname;
                Degree deg;
                deg.setname(degname);
                student.setDegree(deg);
            default: quit=1;
                break;
            }
        }
    }else{
        cout << "the user you have requested does not exist, please check the ID" << endl;
    }
}










ID UserManager::createSIN()
{
    static ID SIN = { { '0', '0', '0', '0', '0', '0', '0', 0 } };

    SIN.id[6]++;

    // Reset code if all codes are taken (not expected with our volume of data)
    if (SIN.id[0] == '9'+1)
    {
        SIN.id[0] = '0' ;
    }

    // Increment code (numbers and letters)
    for( int i=6; i>0; i--)
    {
        if (SIN.id[i] == '9'+1)
        {
            SIN.id[i] = '0';
            SIN.id[i-1]++;
        }

    }

    return SIN;
}





ID UserManager::createID()
{
    static ID ident = { { 'A', 'A', 'A', 'A', 'A', 'A', 'A', 0 } };

    ident.id[6]++;

    if (ident.id[0] == 'Z'+1)
    {
        ident.id[0] = 'A' ;
    }

    for( int i=6; i>0; i--)
    {
        if (ident.id[i] == 'Z'+1)
        {
            ident.id[i] = 'A';
            ident.id[i-1]++;
        }

    }

    return ident;
}
