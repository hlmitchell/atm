//Hannah Mitchell
//CS M20
//December 5th 2017

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
        fstream checkingFile;       //checking file

    public:
        Checking();
        ~Checking();
        void setFileNameSpecific(string, string);

        void displayAccounts();
        bool accountOptionsMenu();
        void withdraw();
        void transfer();
        
};

//empty constructor
Checking::Checking() : Accounts()
{}

//desctructor uploads file data
Checking::~Checking()
{}

//sets file name
void Checking::setFileNameSpecific(string id, string file)
{
    //create file name
    selectedAccount->accountFileName = "C" + id + file + ".txt";
}

//displays account header
void Checking::displayAccounts()
{
    //header before account names listed
    cout << endl << "Checking Account(s)" << endl;
    displayNodes();
}

//displays account options menu and switch
bool Checking::accountOptionsMenu()
{   
    do {
        cout << endl << "Current Account: " << selectedAccount->accountName << endl;
        cout << "Account Funds: $" << selectedAccount->total << endl;

        //advanced options
        cout << endl << "*** " << selectedAccount->accountName << " Options ***" << endl << endl;
        cout << "1. Withdraw" << endl;
        cout << "2. Deposit" << endl;
        cout << "3. Merge Accounts" << endl;
        cout << "4. Transfer Money" << endl;
        cout << "5. Display Account History" << endl;
        cout << "6. Delete Account" << endl;
        cout << "7. Back" << endl;

        //validate input
        cin >> userSelection;
        errorCatcher.boundsCheck(userSelection, 1, 7);
        errorCatcher.clearField();

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
                transfer();
                //activate transfer function in user.h and reset crossTransfer
                if (crossTransfer == true) 
                {
                    crossTransfer = false;
                    return true;
                }
                break;
            case 5:
                selectedAccount->myHistory.display();
                break;
            case 6:
                deleteAccount();
            default:
                selectedAccount = NULL;
                break;
        }
        
        //if account is deleted or merged, exit this menu automatically
        if (selectedAccount == NULL) userSelection = 7;

    } while (userSelection != 7);

    //prevent transfer function activation in user.h
    return false;
}

//withdraw money
void Checking::withdraw()
{
    //formatting
    cout << fixed << setprecision(2);
    //ask for withdraw amount and subtract from total
    cout << endl << "Withdraw amount: ";
    cin >> withdep;
    errorCatcher.boundsCheck(withdep, 0.0, 1000000000.0);

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

    //send to history
    selectedAccount->myHistory.push("Withdrawal of", withdep, selectedAccount->total);
}

//verify if transfer is a checking or savings
void Checking::transfer()
{
    //choose an accounts type
    cout << endl << "In to which account type would you like to transfer funds?";
    userSelection = errorCatcher.chooseAccountType();

    //checking vs savings
    if (userSelection == 1) sameTypeTransfer();
    else if (userSelection == 2) crossTransfer = true; 
}

#endif