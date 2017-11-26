#ifndef CHECKING_H
#define CHECKING_H

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

#include "accounts.h"

using namespace std;

class Checking : public Accounts
{
    protected:
    public:
        Checking();
        void displayAccounts();
        void accountOptionsMenu();
        
};

Checking::Checking() : Accounts()
{}

void Checking::displayAccounts()
{
    cout << endl << "Checking Account(s)" << endl;
    displayNodes();
}

void Checking::accountOptionsMenu()
{   
    do {
        //advanced options
        cout << endl << "*** Advanced Options ***" << endl;
        cout << "1. Withdraw" << endl;
        cout << "2. Deposit" << endl;
        cout << "3. Merge Accounts" << endl;
        cout << "4. Transfer Money" << endl;
        cout << "5. Delete Account" << endl;
        cout << "6. Back" << endl;

        //validate input
        cin >> userSelection;
        //boundsCheck(userSelection, 1, 6);
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

    } while (userSelection != 6);

}

#endif