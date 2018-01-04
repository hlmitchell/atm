//ATM MACHINE
//Hannah Mitchell
//CS M10B
//December 11th 2017

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

        //variables
        int menuUserSelection;            //user input from menus
        bool crossAccountTypeTransfer;    //returned from accounts menu, signals transferHandler()

        UserInfo myInfo;                  //instance of userInfo class holding user data
        InputError inputErrorCatcher;          //catches user input errors
        vector<string> accountFileNames;       //list of all account file names

        string txtFileName;             //user file name with '.txt'
        fstream userInfoFile;           //user file and account names

        Checking myChecking;    //instance of Checking class
        Savings mySavings;      //instance of Savings class

    public:
        //constructor and destructor
        UserMenu();
        UserMenu(string, string);
        ~UserMenu();

        //user manipulators
        void displayMainMenu();
        void editUserInfo();
        void crossAccountTypeTransferHandler(bool); 

        //friend
        friend ostream & operator << (ostream &, UserInfo &);  
};

#endif