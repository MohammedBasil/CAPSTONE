#include "virtualcampus.h"
#include "commons.h"
#include "resourcemanager.h"
#include "usermanager.h"
#include "filewriter.h"
#include "student.h"
#include "professor.h"
#include "administrator.h"

VirtualCampus::VirtualCampus()
    : _resourceManager( new ResourceManager(*this) )  // A resource manager is created with the virtual campus
    , _userManager( new UserManager(*this) )          // A user manager is created with the virtual campus
    , _currentUser( nullptr )
{

}

VirtualCampus::~VirtualCampus()
{
    if (_userManager != nullptr )
    { delete _userManager; }

    if (_resourceManager != nullptr)
    { delete _resourceManager; }
}

void VirtualCampus::start()
{
    menuInitialNotLoggedIn();   // We start the program and go to the initial menu
}

void VirtualCampus::menuInitialNotLoggedIn()
{
    // This menu exists so that we can log in with a different user afer we have
    // logged out without exiting and restarting the program

    while (true)
	{
		cout << endl;
		cout << " Virtual Campus " << endl;
		cout << "----------------" << endl;
		cout << "1.- Log in" << endl;
		cout << "2.- Exit" << endl;
        cout << endl;
		int choice = getMenuChoice(1, 2);
        cout << endl;

		switch (choice)
		{
		case 1: 
            menuLogin(); // Go to login
			break;
		case 2: 
            return; // Exit program
		}
	}
}

void VirtualCampus::menuInitialLoggedIn()
{
    // After logging in all users are offered to change their password or enter the virtual campus

    while (true)
	{
		cout << endl;
		cout << " Virtual Campus " << endl;
		cout << "----------------" << endl;
		cout << "1.- Enter Virtual Campus" << endl;
		cout << "2.- Change password" << endl;
		cout << "3.- Log out" << endl;
        cout << endl;
		int choice = getMenuChoice(1, 3);
        cout << endl;

		switch (choice)
		{
			case 1:
                // Go to the correct menu depending on the user type
                switch (_currentUser->getRole())
				{
					case Role::Administrator:
						menuAdministrator();
						break;
					case Role::Professor:
						menuProfessor();
						break;
					case Role::Student:
						menuStudent();
						break;
                    default: return;
				}
				break;
			case 2:
				menuChangePassword(); 
				break;
			case 3:
                this->_currentUser = nullptr; // We go back to the initial menu to log in
				return;
		}
	}
}

void VirtualCampus::menuLogin()
{
    // Check if there are users in the system,
	// if not, log the default administrator
    if (_userManager->getUserCount() == 0)
	{
        this->_currentUser = &_userManager->defaultAdmin;
	}
	else
	{
        // User has 3 tries to login successfully
		int tries = 3;
		while (tries > 0)
		{
			cout << endl;
			cout << "Introduce your SIN or PID: ";
			ID login = ID::getFromConsole();
			if (!login.Valid())
			{
				cout << "Invalid SIN or PID" << endl;
				tries--;
                continue; // Skips the rest of the current loop
			}

            UniversityMember* user = _userManager->getUser(login); //Try to find user with this ID
			if (user == nullptr)
			{
				cout << "The user does not exist" << endl;
				tries--;
                continue; // Skips the rest of the current loop
			}
            // If a user with this ID was found, the password is asked

			cout << "Introduce your password: ";
			char password[32] = { 0 };
			getText(password, 31);

            // Check that the password is correct
			if (strcmp(user->getPassword(), password) == 0)
			{
                cout << "LOGGED IN SUCCESSFULLY" << endl;
                // Set current user
                this->_currentUser = user;
                break; // Exit the loop
			}
			else
			{
				cout << "Invalid password." << endl;
				tries--;
				continue;
			}
		}

        // Return to initial menu after 3 failed tries
		if (tries <= 0) { return; }
	}

    menuInitialLoggedIn();  // Go to logged in menu after successful loggin
}

void VirtualCampus::menuChangePassword()
{
    cout << endl;
    cout << "Introduce your new password (max 32 characters):" << endl;
    char newpassword[32]{0};
	getText(newpassword, 32);
    _currentUser->setPassword(newpassword);             // Set new password
    _userManager->saveUsers(_currentUser->getRole());   // Save to file
	cout << "Password changed successfully" << endl << endl;

}


void VirtualCampus::menuAdministrator()
{
	while (true)
	{
		cout << endl;
		cout << "Administrator Menu" << endl;
		cout << "------------------" << endl;
		cout << "Choose the type of data you want to manage" << endl;
		cout << "1.- University members" << endl;
		cout << "2.- Resources" << endl;
		cout << "3.- Quit" << endl;
        cout << endl;

		int choice = getMenuChoice(1, 3);
        cout << endl;

		switch (choice)
		{
		case 1:
			menuAdministratorUsers();
			break;
		case 2:
			menuAdministratorResources();
			break;
		case 3:
            return; // Return to initial menu (still logged in)
		}
	}
}

void VirtualCampus::menuAdministratorUsers()
{
	while (true)
	{
		cout << endl;
		cout << "- Administrator mode - University Members -" << endl << endl;
		cout << "1.- Create user" << endl;
		cout << "2.- Edit user" << endl;
		cout << "3.- Delete user" << endl;
		cout << "4.- List users" << endl;
		cout << "5.- Quit" << endl;
        cout << endl;

		int choice = getMenuChoice(1, 5);
        cout << endl;

		switch (choice)
		{
		case 1:
            _userManager->createUser();
			break;
		case 2:
            _userManager->editUser();
			break;
		case 3:
            _userManager->deleteUser();
			break;
		case 4:
            _userManager->showUsers();
			break;
		case 5:
            return; // Return to admin menu
		}
	}
}

void VirtualCampus::menuAdministratorResources()
{
	while (true)
	{
        cout << endl;
        cout << "- Administrator mode - Resources -" << endl << endl;
		cout << "1.- Create resource" << endl;
		cout << "2.- Edit resource" << endl;
		cout << "3.- Delete resource" << endl;
		cout << "4.- List resources" << endl;
		cout << "5.- Quit" << endl;
        cout << endl;

		int choice = getMenuChoice(1, 5);
        cout << endl;

		switch (choice)
		{
		case 1:
            _resourceManager->createResource();
			break;
		case 2:
            _resourceManager->editResource(_currentUser);
			break;
		case 3:
            _resourceManager->deleteResource();
			break;
		case 4:
            _resourceManager->showResources(_currentUser);
			break;
		case 5:
            return; // Return to admin menu
		}
	}
}


void VirtualCampus::menuProfessor()
{
	while (true)
	{
        cout << endl;
        cout << "- Professor mode - " << endl << endl;
		cout << "1.- Modify resources" << endl;
		cout << "2.- Modify marks" << endl;
        cout << "3.- List enrolled resources" << endl;
        cout << "4.- Quit" << endl;
        cout << endl;

		int choice = getMenuChoice(1, 4);
        cout << endl;

		switch (choice)
		{
			case 1:
                _resourceManager->editResource(_currentUser);
				break;
			case 2:
                _resourceManager->editMarks(_currentUser);
				break;
			case 3:
                _resourceManager->showResources(_currentUser);
				break;
			case 4:
                return; // Return to initial menu (still logged in)
		}
	}
}


void VirtualCampus::menuStudent()
{
	while (true)
	{
		cout << endl;
		cout << "- Student mode -" << endl << endl;
		cout << "1.- Manage Courses" << endl;
		cout << "2.- Manage Final Degree Project" << endl;
		cout << "3.- Manage Seminars" << endl;
		cout << "4.- Quit" << endl;
        cout << endl;

		int choice = getMenuChoice(1, 4);
        cout << endl;

		switch (choice)
		{
		case 1:
			menuStudentCourses();
			break;
		case 2:
			menuStudentFDPs();
			break;
		case 3:
			menuStudentSeminars();
			break;
		case 4:
            return; // Return to initial menu (still logged in)
		}
	}
}

void VirtualCampus::menuStudentCourses()
{
	while (true)
	{
        cout << endl;
        cout << "- Student mode - Courses" << endl << endl;
		cout << "Choose an action to perform:" << endl;
		cout << "1.- Enroll Course" << endl;
		cout << "2.- Disenroll Course" << endl;
		cout << "3.- List Courses" << endl;
		cout << "4.- Quit" << endl;
        cout << endl;

		int choice = getMenuChoice(1, 4);
        cout << endl;

		switch (choice)
		{
		case 1:
            _resourceManager->enrollCourse(static_cast<Student*>(_currentUser));
			break;
		case 2:
            _resourceManager->disenrollCourse(static_cast<Student*>(_currentUser));
			break;
		case 3:
            _resourceManager->showCourses(_currentUser);
			break;
		case 4:
            return; // Return to student menu
		}
	}
}

void VirtualCampus::menuStudentFDPs()
{
	while (true)
	{
        cout << endl;
        cout << "- Student mode - Final Degree Project" << endl << endl;
		cout << "1.- Enroll Final Degree Project" << endl;
		cout << "2.- Disenroll Final Degree Project" << endl;
		cout << "3.- List Final Degree Project" << endl;
		cout << "4.- Quit" << endl;
        cout << endl;

		int choice = getMenuChoice(1, 4);
        cout << endl;

		switch (choice)
		{
		case 1:
            _resourceManager->enrollFDP(static_cast<Student*>(_currentUser));
			break;
		case 2:
            _resourceManager->disenrollFDP(static_cast<Student*>(_currentUser));
			break;
		case 3:
            _resourceManager->showFDPs(_currentUser);
			break;
		case 4:
            return; // Return to student menu
		}
	}
}

void VirtualCampus::menuStudentSeminars()
{
	while (true)
	{
        cout << endl;
        cout << "- Student mode - Seminars" << endl << endl;
		cout << "1.- Enroll Seminar" << endl;
		cout << "2.- Disenroll Seminar" << endl;
		cout << "3.- List Seminars" << endl;
		cout << "4.- Quit" << endl;
        cout << endl;

		int choice = getMenuChoice(1, 4);
        cout << endl;

		switch (choice)
		{
		case 1:
            _resourceManager->enrollSeminar(static_cast<Student*>(_currentUser));
			break;
		case 2:
            _resourceManager->disenrollSeminar(static_cast<Student*>(_currentUser));
			break;
		case 3:
            _resourceManager->showSeminars(_currentUser);
			break;
		case 4:
            return; // Return to student menu
		}
	}
}

