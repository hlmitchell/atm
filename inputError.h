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
    public:
        //constructor
        InputError();

        //input handlers
        int chooseAccountType();
        void checkForValidPinEntry(string&);
        void checkForValidIDEntry(string&);
        void clearKeyboardBuffer();
        void yesOrNoValidator(char&);
        void removeExtraWhiteSpaceFromString(string&);

        //template functions
        template <class T>
        void checkForValidUserInput(T&, const T, const T);
        template <class T>
        void checkIfCinFail(T&);
};

//bounds check for menu selection or money movement
template <class T>
void InputError::checkForValidUserInput(T &userSelection, const T lowerBound, const T upperBound)
{
    while (cin.fail() || userSelection < lowerBound || userSelection > upperBound)
    {
        //cin.fail input error check
        checkIfCinFail(userSelection);

        //check for in bounds
        while (userSelection < lowerBound || userSelection > upperBound)
        {
            clearKeyboardBuffer();
            cout << "Invalid Entry. Please try again: ";
            cin >> userSelection;
        }
    }
}

//checks if cin failed
template <class T>
void InputError::checkIfCinFail(T &userSelection)
{
    //while string is entered in to number data type, reprompt
    while (cin.fail())
    {
        clearKeyboardBuffer();

        cout << "Invalid Entry. Please try again: ";
        cin >> userSelection;
    }
}

#endif