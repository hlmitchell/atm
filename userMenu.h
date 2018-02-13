#ifndef USERMENU_H
#define USERMENU_H

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>

#include "userInfo.h"

using namespace std;

ostream &operator << (ostream &, UserInfo &);

class UserMenu
{
    private:
        int menuUserSelection;            
        bool accountTypeDoesNotExist;

        //accountNode *savingsAccount;
        //accountNode *checkingAccount;
        double transferAmount;
        
        UserInfo myInfo;                          
                   
        //Checking myChecking;    
        //Savings mySavings;  

        InputError inputErrorCatcher;

        void initializeClassVariables();
        void collectNewUserInfo();

        void mainMenu();
        void displayMenuOptions();
        void validateUserInput(int);
        void selectAnAccountMenuOption();
        void createAnAccountMenuOption();
        void requestTotalBalanceMenuOption();
        void editUserInfoMenuOption();
        void displayMenuEditOptions();

    public:
        UserMenu();
        UserMenu(string, string);
        ~UserMenu();
};

#endif