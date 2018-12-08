#include "virtualcampus.h"
#include "resourcemanager.h"
#include "usermanager.h"
#include <algorithm>

VirtualCampus::VirtualCampus()
{

}

int VirtualCampus::start(){

    ResourceManager rm;
    UserManager um;
    bool quit = 0;
    int sel, choice, u;
    ID ide;
    char ans, ex;
    Student* currentStudent;

    u=um.login();

    if (u==-1){return 0;}

while (quit == 0){

    bool quit2 = 0;


    while (quit2==0){
    switch (u){

         case 0:
                cout << "- Administrator mode" << endl << endl;
                cout << "-Choose the type of data you want to manage" << endl;
                cout << "1.- University members" << endl;
                cout << "2.- Resources" << endl;
                cout << "3.- Quit" << endl;
                getInt(&choice);

                switch (choice)
                {
                    case 1:

                        cout << "- Administrator mode - University Members -" << endl << endl;
                        cout << "Choose an action to perform:" << endl;
                        cout << "1.- Create user" << endl;
                        cout << "2.- Edit user" << endl;
                        cout << "3.- Delete user" << endl;
                        cout << "4.- List users" << endl;
                        cout << "5.- Quit" << endl;

                        getInt(&sel);

                        switch(sel)
                        {
                            case 1: um.createUser(); break;
                            case 2: um.editUser(); break;
                            case 3: um.deleteUser(); break;
                            case 4: um.showUsers(); break;
                            case 5: quit2 = 1; break;
                            default: cout << "Invalid command." << endl; break;
                        }

                        break;

                    //____________________________________________________________________
                    case 2:

                            cout << "- Administrator mode - Resources -" << endl << endl;
                            cout << "Choose an action to perform:" << endl;
                            cout << "1.- Create resource" << endl;
                            cout << "2.- Edit resource" << endl;
                            cout << "3.- Delete resource" << endl;
                            cout << "4.- List resources" << endl;
                            cout << "5.- Quit" << endl;

                            getInt(&sel);

                            switch(sel)
                            {
                                case 1: rm.createResource(); break;
                                case 2: rm.editResource(); break;
                                case 3: rm.deleteResource(); break;
                                case 4: rm.showResources(); break;
                                case 5: quit2 = 1; break;
                                default: cout << "Invalid command." << endl; break;
                            }

                        break;
                    case 3: quit2=1;
                    cout << " Do you want to exit the program? (Y/N)" << endl;
                    cin >> ex;
                    if ((ex=='y') | (ex=='Y')){
                        quit=1;
                    }
                    break;

                    default: cout << "Invalid command." << endl;
                    break;
                    }

                 break;

        case 2: cout << "- Student mode -" << endl << endl;
                cout << "- Please enter your ID" << endl;
                getText(ide.id, sizeof(ide.id));

                cout << "Choose an action to perform:" << endl;
                cout << "1.- Manage Courses" << endl;
                cout << "2.- Enroll FDP" << endl;
                cout << "3.- Enroll Seminar" << endl;
                cout << "4.- Quit" << endl;
                getInt(&sel);
                    switch (sel)
                    {
                    case 1: cout << "- Course list manager" << endl << endl;

                            currentStudent = um.getStudent(ide);

                            if (currentStudent==nullptr){
                                cout << " No user with that ID" << endl;
                            }else {

                              currentStudent->manageCourses(rm.getCourselist());
                            }

                        break;

                    case 4: cout << " Do you want to exit the student mode? (Y/N)" << endl;
                            cin >> ans;
                            if ((ans=='y') | (ans=='Y')){
                                quit2=1;
                            }
                            cout << " Do you want to exit the program? (Y/N)" << endl;
                            cin >> ex;
                            if ((ex=='y') | (ex=='Y')){
                                quit=1;
                            }

                        break;
                    default: cout << "Invalid command." << endl; break;
                    }

            break;
        case 3: quit2=1; quit=1; break;


      }
    }
}
return 0;
}
