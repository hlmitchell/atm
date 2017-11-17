#ifndef USER_H
#define USER_H

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

#include "checking.h"
#include "savings.h"

using namespace std;

class User
{
    protected:
        string id;
        int pin;
        string first;
        string last;
        int age;
        int userSelection;

        string fileName;
        fstream myFile;

        Checking myChecking;
        Savings mySavings;

    public:
        User();
        User(fstream&);
        void mainMenu();
        void storeUserInfo();
        
        //input error checking functions
        void checkPin(int&);

        template <class T>
        void boundsCheck(T&, const T, const T);

        template <class T>
        void cinFail(T&);
};

User::User()
{
    //collect basic information from user
    cout << "Thank you for choosing the People's Bank!" << endl;
    cout << "Please enter a username: ";
    cin.ignore();
    getline(cin, id);

    cout << "Choose a 4 digit pin: ";
    cin >> pin;
        //check for valid input for pin
    checkPin(pin);

    cout << endl << "Now we'll need to know some information about you!" << endl;
    cout << "What is your last name? ";
    cin.ignore();
    getline(cin, last);
    cout << "What is your first name? ";
    getline(cin, first);

    cout << "Please enter your age: ";
    cin >> age;
        //check for valid input for age
    boundsCheck(age, 16, 125);

    storeUserInfo();
    mainMenu();
}

User::User(fstream &file)
{
    cout << endl << "Welcome Back " << first << " !" << endl;

    mainMenu();
}

void User::mainMenu()
{
    do {
        cout << "Now I gots to figures outs some menu shits" << endl;
        cin >> userSelection;
    } while (userSelection != 0);
}

void User::storeUserInfo()
{
    fileName = id + ".txt";
    myFile.open(fileName.c_str(), fstream::out);
}





//ERROR GARBAGE

void User::checkPin(int &p)
{

    int copy = p;          //copy of p
    int length = 0;        //length of p

    while(cin.fail() || length != 4)
    {
        //cin.fail input error check
        cinFail(copy);

        //find length of pin
        while (copy > 0)
        {
            copy /= 10;
            length++;
        }

        //if pin length isn't 4 then reprompt
        if (length != 4)
        {
            cout << "Invalid Entry. Please try again: ";
            cin >> copy;
            length = 0;
        }
        //if pin is 4 then continue
        else {p = copy;}

    }
}

template <class T>
void User::boundsCheck(T &var, const T lower, const T upper)
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
void User::cinFail(T &var)
{
    while (cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');

        cout << "Invalid Entry. Please try again: ";
        cin >> var;
    }
}

#endif