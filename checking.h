//Hannah Mitchell
//CS M10B
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
        //constructor
        Checking();

        //setters
        void setFileNameSpecific(string, string);

        //account options
        void displayAccounts();
        void accountOptionsMenu();
        void withdraw();
        void transfer();
        
};

//empty constructor
Checking::Checking() : Accounts()
{}

//sets file name
void Checking::setFileNameSpecific(string id, string file)
{
    //pointer to selected account
    nodePtr = myList.getSelectedAccount();
    
    //create file name
    nodePtr->accountFileName = "C" + id + file + ".txt";
}

//displays account header
void Checking::displayAccounts()
{
    //header before account names listed
    cout << endl << "Checking Account(s)" << endl;
    myList.displayNodes();
}

//displays account options menu and switch
void Checking::accountOptionsMenu()
{   
    //set to selected account
    nodePtr = myList.getSelectedAccount();
    
    do {
        //display current account details
        cout << endl << "Current Account: " << nodePtr->accountName << endl;
        cout << "Account Funds: $" << nodePtr->total << endl;

        //advanced options
        cout << endl << "*** " << nodePtr->accountName << " Options ***" << endl << endl;
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
                //activate transfer function in user.h
                if (crossTransfer == true) return;
                break;
            case 5:
                nodePtr->myHistory.display();
                break;
            case 6:
                deleteAccount();
            default:
                resetSelectedAccount();
                break;
        }
        
        //if account is deleted or merged, exit this menu automatically
        if (nodePtr == NULL) userSelection = 7;

    } while (userSelection != 7);

    //reset variable
    userSelection = 0;
}

//withdraw money
void Checking::withdraw()
{
    //set to selected account
    nodePtr = myList.getSelectedAccount();
    
    //formatting
    cout << fixed << setprecision(2);
    //ask for withdraw amount and subtract from total
    cout << endl << "Withdraw amount: ";
    cin >> withdep;
    errorCatcher.boundsCheck(withdep, 0.0, 1000000000.0);

    //make sure there isn't overdraft
    if (nodePtr->total - withdep < 0)
        cout << endl << "You do not have sufficient funds!" << endl;
    else 
    {
        nodePtr->total = nodePtr->total -= withdep;
        //display withdraw amount and new total
        cout << "Successfully withdrew $" << withdep << endl;
        cout << "New " << nodePtr->accountName << " total is $" << nodePtr->total << endl;
        
        //send to history
        nodePtr->myHistory.push("Withdrawal", withdep, nodePtr->total, "NULL");
    }
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