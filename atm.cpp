#include "userMenu.h"
#include "inputError.h"

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

void displayMainMenu();
void attemptLogin(InputError&);
bool checkIfFileExists(string&);

int main()
{
    const int MINIMUM_MENU_INPUT = 1;
    const int MAXIMUM_MENU_INPUT = 3;

    InputError inputErrorCatcher;
    int menuUserSelection;  

    do {
        displayMainMenu();
        
        cin >> menuUserSelection;
        inputErrorCatcher.checkForValidUserInput(menuUserSelection, MINIMUM_MENU_INPUT, MAXIMUM_MENU_INPUT);
        inputErrorCatcher.clearKeyboardBuffer();

        switch (menuUserSelection)
        {
            case 1:
            {
                attemptLogin(inputErrorCatcher);
                break;
            }
            case 2:
            {
                UserMenu myClient;
                break;
            }
            default:
                break;
        }

    } while (menuUserSelection != MAXIMUM_MENU_INPUT);

    menuUserSelection = 0;
}

void displayMainMenu()
{
    cout << endl << "***Welcome to Hannah's Bank!***" << endl << endl;
    cout << "Please select an option from below:" << endl << endl;
    cout << "1. Login" << endl;
    cout << "2. Create a User Account" << endl;
    cout << "3. Exit" << endl;
}

void attemptLogin(InputError &inputErrorCatcher)
{
    string id;
    string pin;

    cout << endl << "Please Enter User ID: ";
    getline(cin, id);

    if (!checkIfFileExists(id)) return;
    
    cout << "Please Enter Pin: ";
    getline(cin, pin);
    
    inputErrorCatcher.checkForValidPinEntry(pin);
    
    UserMenu myClient(id, pin);
}

bool checkIfFileExists(string &idInquiry)
{
    fstream clientFile;

    idInquiry = idInquiry + ".txt";

    clientFile.open(idInquiry.c_str());
    if (clientFile.fail())
    {
        cout << "Not a registered user name!" << endl;
        return false;
    }
    else clientFile.close();
    return true;
}