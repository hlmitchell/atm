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
        fstream savingsFile;
    public:
        Savings();
        ~Savings();
        void setFileName(string);

        void displayAccounts();
        void accountOptionsMenu();
        void transfer();

};

Savings::Savings() : Accounts()
{}

Savings::~Savings()
{}

void Savings::setFileName(string id)
{
    accountFileName = id + "Savings.txt";
    /*savingsFile.open(accountFileName.c_str(), ios::in);

    if (savingsFile.fail()) return;*/
}

void Savings::displayAccounts()
{
    cout << endl << "Savings Account(s)" << endl;
    displayNodes();
}

void Savings::accountOptionsMenu()
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
        boundsCheck(userSelection, 1, 5);
        clearField();

        switch(userSelection)
        {
            case 1:
                deposit();
                break;
            case 2:
                merge();
                break;
            case 3:
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

}

void Savings::transfer()
{}

#endif