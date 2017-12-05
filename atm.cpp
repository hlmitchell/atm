//Hannah Mitchell
//CS M20
//December 5th 2017

#include "user.h"
#include "input.h"

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

//prototypes
bool checkID(string&, fstream&);

int main()
{
    //variables
    Input errorCatcher;     //catches input errors
    fstream clientFile;     //client file
    int userSelection;      //selection for first menu
    string id;              //user ID
    string pin;             //user pin

    do {
        //display main menu
        cout << endl << "***Welcome to Hannah's Bank!***" << endl << endl;
        cout << "Please select an option from below:" << endl << endl;
        cout << "1. Login" << endl;
        cout << "2. Create a User Account" << endl;
        cout << "3. Exit" << endl;

        //checks if user input is integer between 1 and 3
        cin >> userSelection;
        errorCatcher.boundsCheck(userSelection, 1, 3);
        errorCatcher.clearField();

        switch (userSelection)
        {
            case 1:
            {
/*
                //request user ID
                cout << endl << "Please Enter User ID: ";
                getline(cin, id);
                //checks to see if user file exists
                if (!checkID(id, clientFile))
                    {break;}
                //request user PIN
                cout << "Please Enter Pin: ";
                getline(cin, pin);
                
                //checks if pin is all integers
                errorCatcher.checkPin(pin);
                
                //calls object user
                User myClient(id, pin);
                break;*/


                //temporary shortcut
                id = "hlmitchell";
                pin = "9090";
                checkID(id, clientFile);
                User myClient(id, pin);
                break;
            }
            case 2:
            {
                User myClient;
                break;
            }
            default:
                break;
        }

    } while (userSelection != 3);

    //reset variable
    userSelection = 0;
}


//function checks user ID exists
bool checkID(string &name, fstream &file)
{
    //convert to file name
    name = name + ".txt";

    //check to see if open, otherwise return false
    file.open(name.c_str());
    if (file.fail())
    {
        cout << "Not a registered user name!" << endl;
        return false;
    }
    else file.close();
    return true;
}