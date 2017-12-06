//Hannah Mitchell
//CS M10B
//December 5th 2017

#ifndef INPUTERROR_H
#define INPUTERROR_H

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>

using namespace std;

class InputError
{
    protected:
        int userSelection;          //user selection from menus
    
    public:
        //constructor
        InputError();

        //input handlers
        int chooseAccountType();
        void checkPin(string&);
        void checkID(string&);
        void clearField();
        void yesNo(char&);
        
        //template functions
        template <class T>
        void boundsCheck(T&, const T, const T);
        template <class T>
        void cinFail(T&);
};

InputError::InputError()
{
    userSelection = 0;
}

//choose account type for menu options
int InputError::chooseAccountType()
{   
    cout << endl;
    //display part of menu and check bounds
    cout << endl;
    cout << "1. Checking" << endl;
    cout << "2. Savings" << endl;
    cout << "3. Back" << endl;
    cin >> userSelection;
    boundsCheck(userSelection, 1, 3);
    return userSelection;
}

//checks that pin is length of 4 and valid
void InputError::checkPin(string &p)
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

//checks for new user ID
void InputError::checkID(string &name)
{
    ofstream tempFile;
    //converts to file name
    string fileName = name + ".txt";

    //check to see if open, otherwise change id
    tempFile.open(fileName.c_str(), ios::in);
    
    //while file opens successfully, ask for a different username
    while (!tempFile.fail())
    {
        tempFile.close();
        cout << "Username has already been taken! Please try again: ";
        getline(cin, name);
        fileName = name + ".txt";
        tempFile.open(fileName.c_str());
    }

    tempFile.close();
}

//bounds check for menu selection or money movement
template <class T>
void InputError::boundsCheck(T &var, const T lower, const T upper)
{
    while (cin.fail() || var < lower || var > upper)
    {
        //cin.fail input error check
        cinFail(var);

        //check for in bounds
        while (var < lower || var > upper)
        {
            cout << "Invalid Entry. Please try again: ";
            cin >> var;
        }
    }
}

//checks if cin failed
template <class T>
void InputError::cinFail(T &var)
{
    //while string is entered in to number data type, reprompt
    while (cin.fail())
    {
        clearField();

        cout << "Invalid Entry. Please try again: ";
        cin >> var;
    }
}

//clears field to prevent menu skipping
void InputError::clearField()
{
    //clears field to prevent menu skipping
    cin.clear();
    cin.ignore(1000, '\n');
}

//validates yes or no input
void InputError::yesNo(char &x)
{
    clearField();
    
    //change lower case to upper
    if (x == 'y') x = 'Y';
    else if (x == 'n') x = 'N';

    //if user has entered y or n then reprompt
   while ((x != 'Y') && (x != 'N'))
    {
        cout << "Invalid Entry. Please try again: ";
        cin >> x;
        if (x == 'y') x = 'Y';
        else if (x == 'n') x = 'N';
        clearField();
    }
}

#endif