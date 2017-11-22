#include "user.h"

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

//prototypes
void checkSelection(int&);
bool checkID(string&, fstream&);
void checkPin(int&);
bool validatePin(int, fstream&);
void clearField();

int main()
{
    //variables
    fstream clientFile;     //client file
    int userSelection;     //selection for first menu
    string id;              //user ID
    int pin;                //user pin

    do {

        //display main menu
        cout << endl << "Welcome to the People's Bank!" << endl;
        cout << "Please select an option from below." << endl;
        cout << "1. Login" << endl;
        cout << "2. Create a User Account" << endl;
        cout << "3. Exit" << endl;

        //checks if user input is integer between 1 and 3
        cin >> userSelection;
        checkSelection(userSelection);
        clearField();

        switch (userSelection)
        {
            case 1:
            {
/*
                //request user ID
                cout << endl << "Please Enter User ID: ";
                cin.ignore();
                getline(cin, id);

                //checks to see if user file exists
                if (!checkID(id, clientFile))
                    {break;}

                //request user PIN
                cout << "Please Enter Pin: ";
                cin >> pin;
                clearField();
                
                //checks if pin is integer
                checkPin(pin);
                //checks is pin is accurate for account
                if(!validatePin(pin, clientFile))
                    {break;}

                //calls object user
                User myClient(id);*/

                //temporary shortcut
                id = "hlmitchell";
                checkID(id, clientFile);
                clientFile.close();
                User myClient(id);
                
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
}


/**************************/
//function checks user input
/**************************/
void checkSelection(int &input)
{
    while (cin.fail() || input < 0 || input > 3)
    {
        clearField();

        cout << "Invalid Entry. Please try again: ";
        cin >> input;
    }
}

/*******************************/
//function checks user ID exists
/*******************************/
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
    return true;
}

/*********************************/
//function checks if PIN is integer
/*********************************/
void checkPin(int &num)
{
    //checks to see if input was an integer
    while (cin.fail())
    {
        clearField();

        cout << "Invalid Entry. Please try again: ";
        cin >> num;
    }
}

/*********************************/
//function checks if PIN is valid
/*********************************/
bool validatePin(int p, fstream &file)
{
    int num;
    file >> num;
    if (num != p)
    {
        cout << "Invalid Pin!" << endl;
        return false;
    }
    return true;
}

/*********************************/
//function clear input field
/*********************************/
void clearField()
{
    cin.clear();
    cin.ignore(1000, '\n');
}
