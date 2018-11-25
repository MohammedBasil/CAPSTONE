#ifndef USERMANAGER_H
#define USERMANAGER_H
#include"student.h"
#include"professor.h"
#include"administrator.h"
#include<vector>
#include"commons.h"


using namespace std;

class UserManager
{
public:
    UserManager(){}
    void createUser();
    void createStudent();
    void createProfessor();
    void createAdmin();

    void editUser();
    void editStudent(const ID &id);
    void editProfessor(const ID &id);
    void editAdmin(const ID &id);
    void deleteUser();

    void showUsers();
    void showProfessors();
    void showStudents();
    void showAdmins();

    vector <Student> getStudlist(){return _studlist;}           //NUEVO
    Student checkstudent (const ID idstud, bool *check);        // NUEVO

    ID createID();
    ID createSIN();
private:
    vector<Professor> _proflist;
    vector <Student> _studlist;
    vector <Administrator> _adminlist;
};


#endif // USERMANAGER_H
