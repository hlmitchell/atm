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
        string stringSetter;              //holds strings to be set in a class
        int intSetter;                    //holds int to be set in a class
        bool accountTypeDoesNotExist;

        accountNode *savingsAccount;
        accountNode *checkingAccount;
        double transferAmount;
        
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
        void editUserInfo();

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