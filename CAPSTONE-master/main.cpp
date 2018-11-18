#include <iostream>
#include "resourcemanager.h"
#include "usermanager.h"
using namespace std;

int main()
{
    ResourceManager rm;
    UserManager um;
    bool quit = 0;
    int sel, choice;

    cout << "- Administrator mode" << endl << endl;
    cout << "-Choose the type of data you want to manage" << endl;
    cout << "1.- University members" << endl;
    cout << "2.- Resources" << endl;
    getInt(&choice);
    cout << "- Administrator mode - Resources -" << endl << endl;
    cout << "- Administrator mode - Resources -" << endl << endl;
switch (choice)
{
    case 1:
    while(quit==0)
    {
        cout << "Choose an action to perform:" << endl;
        cout << "1.- Create resource" << endl;
        cout << "2.- Edit resource" << endl;
        cout << "3.- Delete resource" << endl;
        cout << "4.- Quit" << endl;

        getInt(&sel);

        switch(sel)
        {
            case 1: um.createUser(); break;
            case 2: um.editUser(); break;
            case 3: um.deleteUser(); break;
            case 4: quit = 1; break;
            default: cout << "Invalid command." << endl; break;
        }
    }
        break;

    //____________________________________________________________________
    case 2:
        while(quit==0)
        {
            cout << "Choose an action to perform:" << endl;
            cout << "1.- Create resource" << endl;
            cout << "2.- Edit resource" << endl;
            cout << "3.- Delete resource" << endl;
            cout << "4.- Quit" << endl;

            getInt(&sel);

            switch(sel)
            {
                case 1: rm.createResource(); break;
                case 2: rm.editResource(); break;
                case 3: rm.deleteResource(); break;
                case 4: quit = 1; break;
                default: cout << "Invalid command." << endl; break;
            }
        }
        break;

    default: cout << "Invalid command." << endl;
        break;
}
    return 0;
}
