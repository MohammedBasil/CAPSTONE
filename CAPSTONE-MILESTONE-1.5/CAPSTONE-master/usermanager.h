#ifndef USERMANAGER_H
#define USERMANAGER_H
#include"student.h"
#include"professor.h"
#include"administrator.h"
#include<vector>


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

    ID createID();
    ID createSIN();
private:
    vector<Professor> _proflist;
    vector <Student> _studlist;
    vector <Administrator> _adminlist;
};


#endif // USERMANAGER_H
