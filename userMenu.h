//Hannah Mitchell
//CS M10B
//December 5th 2017

#ifndef USERMENU_H
#define USERMENU_H

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>

#include "userInfo.h"

using namespace std;

//prototype for overloaded stream operator
ostream &operator << (ostream &, UserInfo &);

class UserMenu
{
    private:
        int userSelection;      //user input from menus
        bool transfer;          //returned from accounts menu, signals transferHandler()

        UserInfo myInfo;             //instance of userInfo class holding user data
        InputError errorCatcher;          //catches user input errors
        vector<string> accountData;  //list of all account file names

        string fileName;        //user file name with '.txt'
        fstream myFile;         //user file and account names

        Checking myChecking;    //instance of Checking class
        Savings mySavings;      //instance of Savings class

    public:
        //constructor and destructor
        UserMenu();
        UserMenu(string, string);
        ~UserMenu();

        //user manipulators
        void mainMenu();
        void editUserInfo();
        void transferHandler(bool); 

        //friend
        friend ostream & operator << (ostream &, UserInfo &);  
};

#endif