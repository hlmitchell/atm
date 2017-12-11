//Hannah Mitchell
//CS M20
//December 5th 2017

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
        InputError errorCatcher;        //error catcher
        fstream myFile;                 //file for specific account

        accountList myList;             //list of accounts
        accountNode *nodePtr;           //pointer to selected account

        string activeAccount;           //name of active account
        int userSelection;              //menu selection
        double withdep;                 //either with withdrawal or deposit amount
        char confirm;                   //user input for y/n prompt
        bool crossTransfer;             //indicates a transfer between account types

    public:
        //constructors and destructor
        Accounts();
        virtual ~Accounts();

        //setters
        void setAccountFileNames(string);
        void setFileNameGeneral(string);
        void resetSelectedAccount();
        void resetCrossTransfer();

        //getters
        bool getHead();
        vector<string> getAccountFileNames();
        accountNode *getSelectedAccount();
        double getTotals();
        bool getCrossTransfer();

        //main menu actions
        bool selectAnAccount(string);

        //account actions
        void createAccount(string);
        void selectAccount();
        void deleteAccount();
        void deposit();
        void merge();
        void sameTypeTransfer();
        void sendToHistory(string, double, double, string);

        //pure virtual functions
        virtual void setFileNameSpecific(string, string) = 0;
        virtual void displayAccounts() = 0;
        virtual void accountOptionsMenu() = 0;
        virtual void transfer() = 0;
};

#endif