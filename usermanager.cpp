#include "usermanager.h"
#include <iostream>
#include <algorithm>
#include <cstring>
#include "commons.h"
#include "degree.h"
#include "filereader.h"
#include "filewriter.h"
#include "resourcemanager.h"

UserManager::UserManager(VirtualCampus& campus)
    :  defaultAdmin(ID(), ""), _campus(campus)
{
    _SINgenerator = { { '0', '0', '0', '0', '0', '0', '0', 0 } };   // Predetermined initial SIN generator value
    _IDgenerator = { { 'A', 'A', 'A', 'A', 'A', 'A', 'A', 0 } };    // Predetermined initial ID generator value

    FileReader IDReader("indexes.bin");     // If users already exist, the new initial value for SIN and ID generators is loaded from file
    IDReader.readCode(_SINgenerator.id);
    IDReader.readCode(_IDgenerator.id);

    FileReader profReader("professors.bin");            // Load existing professors
    profReader.readall<Professor>(_proflist);

    FileReader adminReader("administrators.bin");       // Load existing administrators
    adminReader.readall<Administrator>(_adminlist);

    FileReader studentReader("students.bin");           // Load existing students
    studentReader.readall<Student>(_studlist);
}

UserManager::~UserManager()
{
    FileWriter IDWriter("indexes.bin");         // Save last SIN and ID generators
    IDWriter.writeCode(_SINgenerator.id);
    IDWriter.writeCode(_IDgenerator.id);
}


void UserManager::createUser()
{
           cout << "Select type of member to create:" <<endl;
           cout << "1.- Professor" << endl;
           cout << "2.- Student" << endl;
           cout << "3.- Administrator" << endl;
           cout << endl;

		   int choice = getMenuChoice(1, 3);
           cout << endl;

		   switch (choice)
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

    saveUsers(Role::Professor);  // Write to file
}

void UserManager::createAdmin()
{
    ID identification=createID();
    char pass[32]{0};
    cout << "Please enter a password of less than 32 characters for the new Administrator" << endl;
    getText(pass, sizeof(pass));
    Administrator admin(identification, pass);
    _adminlist.push_back(admin);
    cout << "Created administrator with ID " << identification.id << " and password " << pass << endl;

    saveUsers(Role::Administrator);  // Write to file
}

void UserManager::createStudent()
{
    ID identification=createSIN();
    char pass[32]{0};
    cout << "Please enter a password of less than 32 characters for the new Student" << endl;
    getText(pass, sizeof(pass));
    cout << "Introduce the code of the degree of the course" << endl;
    ResCode degreecode = _campus.getResourceManager()->getExistingDegreeFromConsole();
    if (!degreecode.Valid()) { cout << "Student creation failed." << endl; return; }    // Fails after several tries
    Student stud(identification, pass, degreecode);
    _studlist.push_back(stud);
    cout << "Created Student with SIN " << identification.id << " and password " << pass << endl;

    saveUsers(Role::Student);  // Write to file
}


void UserManager::editUser()
{
	cout << "Select type of member to edit:" << endl;
	cout << "1.- Professor" << endl;
	cout << "2.- Student" << endl;
	cout << "3.- Administrator" << endl;
    cout << endl;

	int choice = getMenuChoice(1, 3);
    cout << endl;

	ID identification;

	cout << "Please enter the ID or SIN of the User" << endl;
	getText(identification.id, sizeof(identification.id));

	switch (choice)
	{
	case 1: editProfessor(identification); break;
	case 2: editStudent(identification); break;
	case 3: editAdmin(identification); break;
	}
}

void UserManager::editProfessor(const ID &id)
{
    Professor* professor = getProfessor(id);  // Tries to find professor with that ID
	if (professor != nullptr)
	{
        bool quit = false;
        while(!quit)
		{
            cout << "Select attribute to edit: " << endl;
            cout << "1.- Password" << endl;
            cout << "2.- Quit" << endl;
            cout << endl;

            char pass[32]{0};
			int choice = getMenuChoice(1, 2);
            cout << endl;

            switch (choice) 
			{
            case 1: cout << "Enter the new password for the user: " << professor->getID().id << endl;
                    getText(pass, sizeof(pass));
                    professor->setPassword(pass);
                    cout << "New password for professor: " <<  professor->getID().id << " is: " << professor->getPassword() << endl;
                break;
            case 2: quit=true;
                break;
            default: quit=true;
                break;
            }
        }
    }else{
        cout << "The user you have requested does not exist, please check the ID" << endl;
    }

    saveUsers(Role::Professor);  // Write to file
}

void UserManager::editStudent(const ID &id)
{
    Student* student = getStudent(id);  // Tries to find student with that ID
	if (student != nullptr)
	{
        bool quit=false;
        while(!quit)
		{
            cout << "Select attribute to edit:" << endl;
            cout << "1.- Password" << endl;
            cout << "2.- Degree" << endl;
            cout << "3.- Quit" << endl;
            cout << endl;

            int choice = getMenuChoice(1,3);
            cout << endl;

            switch (choice) 
			{
                case 1:
                {
                    cout << "Enter the new password for the user: " << student->getID().id << endl;
                    char pass[32]{0};
                    getText(pass, sizeof(pass));
                    student->setPassword(pass);
                    break;
                }
                case 2:
                {
                    cout << "Enter the code of the new Degree for the student: " << student->getID().id << endl;
                    ResCode degreecode = _campus.getResourceManager()->getExistingDegreeFromConsole();
                    if (!degreecode.Valid()) { cout << "Student creation failed." << endl; return; }    // Fails after several tries
                    student->setDegree(degreecode);
                    break;
                }
                case 3:
                {
                    quit=true;
                    break;
                }
            }
        }
    }else{
        cout << "The user you have requested does not exist, please check the ID" << endl;
    }

    saveUsers(Role::Student);   // Write to file
}

void UserManager::editAdmin(const ID &id)
{
    Administrator* admin = getAdmin(id);    // Tries to find admin with that ID
	if (admin != nullptr)
	{
		bool quit = false;
        while(!quit)
		{
            cout << "Select attribute to edit:" << endl;
            cout << "1.- Password" << endl;
            cout << "2.- Quit" << endl;
            cout << endl;

			int choice = getMenuChoice(1, 2);
            cout << endl;

            switch (choice) 
			{
            case 1:
            {
                cout << "Enter the new password for the user: " << admin->getID().id << endl;
                char pass[32]{0};
                getText(pass, sizeof(pass));
                admin->setPassword(pass);
                break;
            }
            case 2: quit=true;
                break;
            }
        }
    }else{
        cout << "The user you have requested does not exist, please check the ID" << endl;
    }

    saveUsers(Role::Administrator);  // Write to file
}


void UserManager::deleteUser()
{
    cout << "Select type of user to delete:" <<endl;
    cout << "1.- Professor" << endl;
    cout << "2.- Student" << endl;
    cout << "3.- Administrator" << endl;
    cout << endl;
    
	int choice = getMenuChoice(1, 3);
    cout << endl;

    cout << "Enter ID of the user to delete:" << endl;
    ID identification;
    getText(identification.id, sizeof(identification.id));

    switch(choice)
    {
         case 1:
                {
                    bool found = false;
                    for (auto it=_proflist.begin(); it!=_proflist.end(); it++)
                    {
                        if (it->getID().Equals(identification))
                        {
                            _proflist.erase(it);
                            cout << "User "<< identification.id << " deleted." << endl;

                            saveUsers(Role::Professor); // Save to file
                            found = true;
                            break;
                        }
                    }

                    if (!found)
                    {
                            cout << "No professor with that ID exists." << endl;
                    }
                }
                break;

         case 2:
                {
                    bool found = false;
                    for (auto it=_studlist.begin(); it!=_studlist.end(); it++)
                    {
                        if (it->getID().Equals(identification))
                        {
                            _studlist.erase(it);
                            cout << "User "<< identification.id << " deleted." << endl;

                            saveUsers(Role::Student);   // Save to file
                            found = true;
                            break;
                        }
                    }
                    if (!found)
                    {
                            cout << "No student with that ID exists." << endl;
                    }
                }
                break;
         case 3:
                {
                    bool found = false;
                    for (auto it=_adminlist.begin(); it!=_adminlist.end(); it++)
                    {
                        if (it->getID().Equals(identification))
                        {
                            _adminlist.erase(it);
                            cout << "User "<< identification.id << " deleted." << endl;

                            saveUsers(Role::Administrator); // Save to file
                            found = true;
                            break;
                        }
                    }

                    if (!found)
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
	showAdmins();
    showProfessors();
    showStudents();
}

void UserManager::showProfessors()
{
    cout << " Professors: " << endl;
    for (unsigned int i=0; i<_proflist.size(); i++)
	{
        cout << "\t Professor ID: " << _proflist[i].getID().id << endl;
        cout << "\t Password: " << _proflist[i].getPassword() << endl;
        cout << endl;
    }
}

void UserManager::showStudents()
{
    cout << " Students: " << endl;
    for (unsigned int i=0; i<_studlist.size(); i++)
	{
        cout << "\t Student SIN: " << _studlist[i].getID().id << endl;
        cout << "\t Password: " << _studlist[i].getPassword() << endl;
        cout << "\t Degree: " << _studlist[i].getDegree().code << endl;
        cout << endl;
    }
}

void UserManager::showAdmins()
{
    cout << " Administrators: " << endl;
    for (unsigned int i=0; i<_adminlist.size(); i++)
	{
        cout << "\t Administrator ID: " << _adminlist[i].getID().id << endl;
        cout << "\t Password: " << _adminlist[i].getPassword() << endl;
        cout << endl;
    }
}


ID UserManager::createSIN()
{

    _SINgenerator.id[6]++;  // Increment SIN

    // Reset code if all codes are taken (not expected with our volume of data)
    if (_SINgenerator.id[0] == '9'+1)
    {
        _SINgenerator.id[0] = '0' ;
    }

    // Maintain range of valid values (after 9 go back to 0)
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

    _IDgenerator.id[6]++;   // Increment ID

    // Reset code if all codes are taken (not expected with our volume of data)
    if (_IDgenerator.id[0] == 'Z'+1)
    {
        _IDgenerator.id[0] = 'A' ;
    }

    // Maintain range of valid values (after Z go back to A)
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


UniversityMember* UserManager::getUser(const ID& id)
{
	UniversityMember* user = nullptr;
    // Try to get an admin
	user = getAdmin(id);
    // If there's no admin with this id
	if (user == nullptr)
	{
        // Try to get a professor
		user = getProfessor(id);	
	}
    // If there's no professor with this id
	if (user == nullptr)
	{
        // Try to get a student
		user = getStudent(id);
	}

    // Return what we found or null
	return user;
}

Student* UserManager::getStudent(const ID& id)
{
	for (size_t i = 0; i < _studlist.size(); i++)
	{
		if (id.Equals(_studlist[i].getID()))
		{
			return &_studlist[i];
		}
	}
	return nullptr;
}

Professor* UserManager::getProfessor(const ID&id)
{
	for (unsigned int i = 0; i < _proflist.size(); i++)
	{
		if (id.Equals(_proflist[i].getID()))
		{
			return &_proflist[i];
		}
	}
	return nullptr;
}

Administrator* UserManager::getAdmin(const ID&id)
{
	for (unsigned int i = 0; i < _adminlist.size(); i++)
	{
		if (id.Equals(_adminlist[i].getID()))
		{
			return &_adminlist[i];
		}
	}
	return nullptr;
}

void UserManager::saveUsers(const Role role)
{
    // Saves users to file according to their type
    switch(role)
    {
        case Role::Student:
        {
            FileWriter studentWriter( "students.bin");
            studentWriter.writeall<Student>(_studlist);
            break;
        }
        case Role::Professor:
        {
            FileWriter profWriter( "professors.bin");
            profWriter.writeall<Professor>(_proflist);
            break;
        }
        case Role::Administrator:
        {
            FileWriter adminWriter( "administrators.bin");
            adminWriter.writeall<Administrator>(_adminlist);
            break;
        }
        case Role::Any:
        {
            FileWriter studentWriter( "students.bin");
            studentWriter.writeall<Student>(_studlist);

            FileWriter profWriter( "professors.bin");
            profWriter.writeall<Professor>(_proflist);

            FileWriter adminWriter( "administrators.bin");
            adminWriter.writeall<Administrator>(_adminlist);
            break;
        }
    }
}
