//PROBLEM IN CHECK PIN. Because of binary formatting, cannot read pin without importing file
//first

#include "user.h"

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

//prototypes
void checkSelection(int&);
bool checkID(string&, fstream&);
void checkPin(string&);
void clearField();

int main()
{
    //variables
    fstream clientFile;     //client file
    int userSelection;      //selection for first menu
    string id;              //user ID
    string pin;             //user pin

    do {
        //display main menu
        cout << endl << "Welcome to Hannah's Bank!" << endl << endl;
        cout << "Please select an option from below:" << endl;
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
                checkPin(pin);
                
                //calls object user
                User myClient(id, pin);
/*
                //temporary shortcut
                id = "hlmitchell";
                checkID(id, clientFile);
                clientFile.close();
                User myClient(id);*/
                
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
void checkPin(string &p)
{
    bool valid = true;
    
    do
    {
        //make sure characters are all ints
        for (int i = 0; i < p.length(); i++)
        {
            if (p[i] < '0' || p[i] > '9')
                valid = false;
        }

        //if pin length isn't 4 then reprompt
        if (p.length() != 4 || valid == false)
        {
            cout << "Invalid Entry. Please try again: ";
            getline(cin, p);

            valid = true;
            for (int i = 0; i < p.length(); i++)
            {
                if (p[i] < '0' || p[i] > '9')
                    valid = false;
            }
        }
    } while(p.length() != 4 || valid == false);
}

/*********************************/
//function clear input field
/*********************************/
void clearField()
{
    cin.clear();
    cin.ignore(1000, '\n');
}
