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
        string stringSetter;              
        int intSetter;                    
        bool accountTypeDoesNotExist;

        accountNode *savingsAccount;
        accountNode *checkingAccount;
        double transferAmount;
        
        UserInfo myInfo;                  
        InputError inputErrorCatcher;          
        vector<string> accountFileNames;       

        string txtFileName;             
        fstream userInfoFile;           

        Checking myChecking;    
        Savings mySavings;      

    public:
        UserMenu();
        UserMenu(string, string);
        ~UserMenu();

        void initializeClassVariables();
        void collectNewUserInfo();
        void requestUserName();
        void createUserFile();
        void requestUserPin();
        void validateUserPin();
        void requestFirstName();
        void requestLastName();
        void requestAge();

        void openUserFile(string);
        void readUserInfoFromFile();
        void readAccountNamesFromFile();
        void categorizeAccountNames();

        void writeUserInfoToFile();
        void getAndWriteAccountFileNames();
        void getCheckingAccountFileNames();
        void getSavingsAccountFileNames();
        void writeAccountNamesToFile();

        void mainMenu();
        void displayMenuOptions();
        void validateUserInput(int);
        void selectAnAccountMenuOption();
        void createAnAccountMenuOption();
        void requestTotalBalanceMenuOption();
        void editUserInfoMenuOption();

        void displayMenuEditOptions();
        void requestNewPin();
        void requestNewFullName();
        void requestNewFirstName();
        void requestNewLastName();
        void requestNewAge();

        friend ostream & operator << (ostream &, UserInfo &);  
};

#endif