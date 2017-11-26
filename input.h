#ifndef INPUT_H
#define INPUT_H

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>

using namespace std;

class Input
{
    protected:
        int userSelection;
    
    public:
        Input();
        int chooseAccountType();

        void checkPin(string&);
        void checkID(string&);
        
        template <class T>
        void boundsCheck(T&, const T, const T);

        template <class T>
        void cinFail(T&);

        void clearField();

        void yesNo(char&);

};

Input::Input()
{}

//choose account type for menu options
int Input::chooseAccountType()
{   
    //display part of menu and check bounds
    cout << "1. Checking" << endl;
    cout << "2. Savings" << endl;
    cout << "3. Back" << endl;
    cin >> userSelection;
    boundsCheck(userSelection, 1, 3);
    return userSelection;
}

void Input::checkPin(string &p)
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
void Input::checkID(string &name)
{
    ofstream tempFile;
    //converts to file name
    string fileName = name + ".txt";

    //check to see if open, otherwise change id
    tempFile.open(fileName.c_str());
    
    while (!tempFile.fail())
    {
        cout << "Username has already been taken! Please try again: ";
        getline(cin, name);
        fileName = name + ".txt";
        tempFile.open(fileName.c_str());
    }
}

template <class T>
void Input::boundsCheck(T &var, const T lower, const T upper)
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

template <class T>
void Input::cinFail(T &var)
{
    while (cin.fail())
    {
        clearField();

        cout << "Invalid Entry. Please try again: ";
        cin >> var;
    }
}

void Input::clearField()
{
    cin.clear();
    cin.ignore(1000, '\n');
}

void Input::yesNo(char &x)
{
    clearField();
    
    //change lower case to upper
    if (x == 'y') x = 'Y';
    else if (x == 'n') x = 'N';

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