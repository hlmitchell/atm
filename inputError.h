//ATM MACHINE
//Hannah Mitchell
//CS M10B
//December 11th 2017

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
        void checkString(string&);
        
        //template functions
        template <class T>
        void boundsCheck(T&, const T, const T);
        template <class T>
        void cinFail(T&);
};

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
            clearField();
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

#endif