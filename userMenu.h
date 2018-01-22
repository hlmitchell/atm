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

        int menuUserSelection;            
        bool crossAccountTypeTransfer;    
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

        //handle new user
        void initializeClassVariables();
        void collectNewUserInfo();
        void requestUserName();
        void createUserFile();
        void requestUserPin();
        void validateUserPin();
        void requestFirstName();
        void requestLastName();
        void requestAge();

        //handle returning user
        void openUserFile(string);
        void readUserInfoFromFile();
        void readAccountNamesFromFile();
        void categorizeAccountNames();

        //log out procedure
        void writeUserInfoToFile();
        void getAndWriteAccountFileNames();
        void getCheckingAccountFileNames();
        void getSavingsAccountFileNames();
        void writeAccountNamesToFile();

        //main menu
        void mainMenu();
        void displayMenuOptions();
        void validateUserInput(int);
        void selectAnAccountMenuOption();
        void selectCheckingAccount();
        void selectSavingsAccount();
        void createAnAccountMenuOption();
        void requestTotalBalanceMenuOption();
        void editUserInfoMenuOption();

        //user info editting functions
        void displayMenuEditOptions();
        void requestNewPin();
        void requestNewFullName();
        void requestNewFirstName();
        void requestNewLastName();
        void requestNewAge();

        //transfer crap
        void crossAccountTypeTransferHandler(bool); 
        void checkingTransfer();
        void savingsTransfer();
        void outputNewAccountTotals();
        void selectASavingsAccount();
        void checkIfSavingsAccountExists();
        void getTransferAmountChecking();
        void ammendAccountTotalsChecking();
        void sendToHistory(string, string);
        void selectACheckingAccount();
        void checkIfCheckingAccountExists();
        void getTransferAmountSavings();
        void ammendAccountTotalsSavings();

        //friend
        friend ostream & operator << (ostream &, UserInfo &);  
};

#endif