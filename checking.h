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
        void withdraw();
        void transfer();
        
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
        cout << "Current Account: " << selectedAccount->accountName << "\t";
        cout << "Account Funds: $" << selectedAccount->total << endl;

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
        boundsCheck(userSelection, 1, 6);
        clearField();

        switch(userSelection)
        {
            case 1:
                withdraw();
                break;
            case 2:
                deposit();
                break;
            case 3:
                merge();
                break;
            case 4:
                break;
            case 5:
                deleteAccount();
                break;
            default:
                selectedAccount = NULL;
                break;
        }
        
        //if account is deleted or merged, exit this menu automatically
        if (selectedAccount == NULL) userSelection = 6;

    } while (userSelection != 6);

}

void Checking::withdraw()
{
    //formatting
    cout << fixed << setprecision(2);
    //ask for withdraw amount and subtract from total
    cout << endl << "Withdraw amount: ";
    cin >> withdep;
    boundsCheck(withdep, 0.0, 1000000000.0);

    //make sure there isn't overdraft
    if (selectedAccount->total - withdep < 0)
        cout << endl << "You do not have sufficient funds!" << endl;
    else 
    {
        selectedAccount->total = selectedAccount->total -= withdep;
        //display withdraw amount and new total
        cout << "Successfully withdrew $" << withdep << endl;
        cout << "New " << selectedAccount->accountName << " total is $" << selectedAccount->total << endl;
    }
}

void Checking::transfer()
{
    cout << endl << "In to which account type would you like to transfer funds?";
    userSelection = chooseAccountType();
    if (userSelection == 1)
    {
        displayNodes();
    }
    else if (userSelection == 2)
    {
        cout << "Probs";
    }
    
}

#endif