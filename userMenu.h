#ifndef USERMENU_H
#define USERMENU_H

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>

#include "userInfo.h"
#include "accountTree.h"

using namespace std;

class UserMenu
{
    private:
        int menuUserSelection;

        AccountTree *myAccounts;
        UserInfo *myInfo;
         
        InputError inputErrorCatcher; 

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
        UserMenu(AccountTree&, UserInfo&);
        ~UserMenu(); 
};

#endif