//ATM MACHINE
//Hannah Mitchell
//CS M10B
//December 11th 2017

#ifndef ACCOUNTS_H
#define ACCOUNTS_H

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>

#include "inputError.h"
#include "accountList.h"

using namespace std;

class Accounts
{
    protected:

    //variables
        InputError inputErrorCatcher;   //error catcher

        accountList listOfOpenAccounts;       //list of accounts
        accountNode *pointerToActiveAccount;  //pointer to selected account

        string activeAccountName;           //name of active account
        int menuUserSelection;                  //menu selection
        double withdrawOrDepositValue;      //either with withdrawal or deposit amount
        char yesOrNo;                       //user input for y/n prompt
        bool crossTransfer;                 //indicates a transfer between account types

    public:
        //constructors and destructor
        Accounts();
        virtual ~Accounts();

        //setters
        void downloadExistingAccounts(string);

        void setTextFileName(string);
        string removeSpacesFromAccountName();

        void resetActiveAccount();
        void resetCrossTransfer();

        //getters
        bool getHeadOfAccountList();
        vector<string> getAccountFileNames();
        accountNode *callGetActiveAccount();
        double getTotalMoneyForAllAccounts();
        bool getCrossTransfer();

        //main menu actions
        bool selectAccountForCrossTransfer(string);

        //account actions
        void createAccount(string);
        void selectAccount();
        void deleteAccount();
        void depositFunds();
        void mergeAccounts();
        void sameAccountTypeTransfer();
        void sendToHistory(string, double, double, string);

        //pure virtual functions
        virtual void specifyFileType(string, string) = 0;
        virtual void displayAccounts() = 0;
        virtual void accountOptionsMenu() = 0;
        virtual void transferFunds() = 0;
};

#endif