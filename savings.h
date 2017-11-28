#ifndef SAVINGS_H
#define SAVINGS_H

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

#include "accounts.h"

using namespace std;

class Savings : public Accounts
{
    protected:
        fstream savingsFile;    //savings file
    public:
        Savings();
        ~Savings();
        void setFileName(string);

        void displayAccounts();
        bool accountOptionsMenu();
        void transfer();

};

//empty constructor
Savings::Savings() : Accounts()
{}

//destructor uploads file data
Savings::~Savings()
{}

//sets file name
void Savings::setFileName(string id)
{
    accountFileName = id + "Savings.txt";
    /*savingsFile.open(accountFileName.c_str(), ios::in);

    if (savingsFile.fail()) return;*/
}

//displays account header
void Savings::displayAccounts()
{
    cout << endl << "Savings Account(s)" << endl;
    displayNodes();
}

//displays savings menu and switch
bool Savings::accountOptionsMenu()
{   
    do {

        cout << endl << "Current Account: " << selectedAccount->accountName << endl;
        cout << "Account Funds: $" << selectedAccount->total << endl;

        //advanced options
        cout << endl << "*** " << selectedAccount->accountName << " Options ***" << endl << endl;
        cout << "1. Deposit" << endl;
        cout << "2. Merge Accounts" << endl;
        cout << "3. Transfer Money" << endl;
        cout << "4. Delete Account" << endl;
        cout << "5. Back" << endl;

        //validate input
        cin >> userSelection;
        errorCatcher.boundsCheck(userSelection, 1, 5);
        errorCatcher.clearField();

        switch(userSelection)
        {
            case 1:
                deposit();
                break;
            case 2:
                merge();
                break;
            case 3:
                transfer();
                //activate transfer function in user.h
                if (crossTransfer == true) return true;
                break;
            case 4:
                deleteAccount();
                break;
            default:
                selectedAccount = NULL;
                break;
        }

        //if account is deleted or merged, exit this menu automatically
        if (selectedAccount == NULL) userSelection = 5;

    } while (userSelection != 5);

    //prevent transfer function activation in user.h
    return false;

}

//validates if transfer is savings or savings
void Savings::transfer()
{
    cout << endl << "In to which account type would you like to transfer funds?" << endl;
    userSelection = errorCatcher.chooseAccountType();
    if (userSelection == 2)
    {
        displayNodes();
    }
    else if (userSelection == 1) crossTransfer = true; 
}

#endif