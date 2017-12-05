//Hannah Mitchell
//CS M20
//December 5th 2017

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
        void setFileNameSpecific(string, string);

        void displayAccounts();
        bool accountOptionsMenu();
        void transfer();
};

//empty constructor
Savings::Savings() : Accounts()
{}

//sets file name
void Savings::setFileNameSpecific(string id, string file)
{
    //create file name
    selectedAccount->accountFileName = "S" + id + file + ".txt";
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
        cout << "4. Display Account History" << endl;
        cout << "5. Delete Account" << endl;
        cout << "6. Back" << endl;

        //validate input
        cin >> userSelection;
        errorCatcher.boundsCheck(userSelection, 1, 6);
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
                if (crossTransfer == true) 
                {
                    crossTransfer = false;
                    return true;
                }
                break;
            case 4:
                selectedAccount->myHistory.display();
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

    //prevent transfer function activation in user.h
    return false;

}

//validates if transfer is savings or savings
void Savings::transfer()
{
    //choose an accounts type
    cout << endl << "In to which account type would you like to transfer funds?";
    userSelection = errorCatcher.chooseAccountType();

    //checking vs savings
    if (userSelection == 2) sameTypeTransfer();
    else if (userSelection == 1) crossTransfer = true; 
}

#endif