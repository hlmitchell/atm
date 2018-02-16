#ifndef INPUTERROR_H
#define INPUTERROR_H

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>

using namespace std;

class InputError
{
    private:
        static const int ONE = 1;
        static const int THREE = 3;
        static const int PIN_LENGTH = 4; 
        static const char ZERO = '0';
        static const char NINE = '9';
        
    public:
        void checkForValidPinEntry(string&);
        void checkForValidIDEntry(string&);
        void clearKeyboardBuffer();
        void yesOrNoValidator(char&);
        void removeExtraWhiteSpaceFromString(string&);

        template <class T>
        void checkForValidUserInput(T&, const T, const T);
        template <class T>
        void checkIfCinFail(T&);
};

template <class T>
void InputError::checkForValidUserInput(T &userSelection, const T lowerBound, const T upperBound)
{
    while (cin.fail() || userSelection < lowerBound || userSelection > upperBound)
    {
        checkIfCinFail(userSelection);

        while (userSelection < lowerBound || userSelection > upperBound)
        {
            clearKeyboardBuffer();
            cout << "Invalid Entry. Please try again: ";
            cin >> userSelection;
        }
    }
}

template <class T>
void InputError::checkIfCinFail(T &userSelection)
{
    while (cin.fail())
    {
        clearKeyboardBuffer();

        cout << "Invalid Entry. Please try again: ";
        cin >> userSelection;
    }
}

#endif