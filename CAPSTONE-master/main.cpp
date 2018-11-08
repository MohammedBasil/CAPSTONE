#include <iostream>
#include "resourcemanager.h"
using namespace std;

int main()
{
    ResourceManager rm;
    bool quit = 0;
    int sel;

    cout << "- Administrator mode - Resources -" << endl << endl;

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


    return 0;
}
