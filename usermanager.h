#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <vector>
#include "virtualcampus.h"
#include "student.h"
#include "professor.h"
#include "administrator.h"

class UserManager
{
public:
    UserManager(VirtualCampus& campus);
    ~UserManager();

    // User creation methods
    void createUser();
    void createStudent();
    void createProfessor();
    void createAdmin();

    // User edition methods
    void editUser();
    void editStudent(const ID &id);
    void editProfessor(const ID &id);
    void editAdmin(const ID &id);
    void deleteUser();

    // User listing methids
    void showUsers();
    void showProfessors();
    void showStudents();
    void showAdmins();

	unsigned int getUserCount() { return _adminlist.size() + _proflist.size() + _studlist.size(); }

    //Getters
    UniversityMember* getUser(const ID& id);
    Student* getStudent(const ID& id);
    Professor* getProfessor(const ID& id);
    Administrator* getAdmin(const ID& id);

    //Write to file each type of user
    void saveUsers(const Role role);

    //ID and SIN generators
    ID createID();
    ID createSIN();

    // Default administrator user to manage empty campus
	Administrator defaultAdmin;

private:
	VirtualCampus& _campus;

    ID _SINgenerator;
    ID _IDgenerator;

    vector<Professor>       _proflist;
    vector<Student>         _studlist;
    vector<Administrator>   _adminlist;
};


#endif // USERMANAGER_H
