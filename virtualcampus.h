#ifndef VIRTUALCAMPUS_H
#define VIRTUALCAMPUS_H

class ResourceManager;
class UserManager;
class UniversityMember;

class VirtualCampus
{
public:
    VirtualCampus();
	~VirtualCampus();

    void start(); // Function that starts the entire program

    UserManager* getUserManager() { return _userManager;  }
    ResourceManager* getResourceManager() { return _resourceManager; }

private:
    // Common menus
	void menuInitialNotLoggedIn();
	void menuInitialLoggedIn();
	void menuLogin();
	void menuChangePassword();

    // Administrator menus
	void menuAdministrator();
	void menuAdministratorUsers();
	void menuAdministratorResources();

    // Professor menus
	void menuProfessor();

    // Student menus
	void menuStudent();
	void menuStudentCourses();
	void menuStudentFDPs();
	void menuStudentSeminars();

    ResourceManager*	_resourceManager;
    UserManager*		_userManager;

    // Logged in user
    UniversityMember*	_currentUser;
};

#endif // VIRTUALCAMPUS_H
