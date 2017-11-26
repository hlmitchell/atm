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
        int userSelection;

    public:
        Savings();
        void displayAccounts();
        void accountOptionsMenu();

};

Savings::Savings() : Accounts()
{
}

void Savings::displayAccounts()
{
    cout << endl << "Savings Account(s)" << endl;
    displayNodes();
}

void Savings::accountOptionsMenu()
{   
    do {
        //advanced options
        cout << endl << "*** Advanced Options ***" << endl;
        cout << "1. Deposit" << endl;
        cout << "2. Merge Accounts" << endl;
        cout << "3. Transfer Money" << endl;
        cout << "4. Delete Account" << endl;
        cout << "5. Back" << endl;

        //validate input
        cin >> userSelection;
        //boundsCheck(userSelection, 1, 5);
        //clearField();

        switch(userSelection)
        {
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                deleteAccount();
                break;
            default:
                break;
        }

    } while (userSelection != 5);

}

#endif