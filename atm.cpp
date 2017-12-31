//ATM MACHINE
//Hannah Mitchell
//CS M10B
//December 11th 2017

#include "userMenu.h"
#include "inputError.h"

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

//prototypes
void attemptLogin(InputError&);
bool checkIfFileExists(string&);

int main()
{
    //constants
    const int MINIMUM_MENU_INPUT = 1;
    const int MAXIMUM_MENU_INPUT = 3;
    
    //variables
    InputError inputErrorCatcher;     //catches input errors
    int menuUserSelection;       //selection for first menu

    do {
        //display main menu
        cout << endl << "***Welcome to Hannah's Bank!***" << endl << endl;
        cout << "Please select an option from below:" << endl << endl;
        cout << "1. Login" << endl;
        cout << "2. Create a User Account" << endl;
        cout << "3. Exit" << endl;

        //checks if user input is integer between 1 and 3
        cin >> menuUserSelection;
        inputErrorCatcher.boundsCheck(menuUserSelection, MINIMUM_MENU_INPUT, MAXIMUM_MENU_INPUT);
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

    //reset variable
    menuUserSelection = 0;
}


//attempt to login to account using id and pin
void attemptLogin(InputError &inputErrorCatcher)
{
    //variables
    string id;                   //user ID
    string pin;                  //user pin

    //request user ID
    cout << endl << "Please Enter User ID: ";
    getline(cin, id);

    //checks to see if user file exists
    if (!checkIfFileExists(id)) return;
    
    //request user PIN
    cout << "Please Enter Pin: ";
    getline(cin, pin);
    
    //checks if pin is all integers
    inputErrorCatcher.checkForValidPinEntry(pin);
    
    //calls object user
    UserMenu myClient(id, pin);
}

//function checks if user ID exists by searching for file of same name
bool checkIfFileExists(string &idInquiry)
{
    //create file
    fstream clientFile;

    //convert id input to file name
    idInquiry = idInquiry + ".txt";

    //check to see if open, otherwise return false
    clientFile.open(idInquiry.c_str());
    if (clientFile.fail())
    {
        cout << "Not a registered user name!" << endl;
        return false;
    }
    else clientFile.close();
    return true;
}