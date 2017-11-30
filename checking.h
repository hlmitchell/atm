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
        void setFileName(string);

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
{
    /*checkingFile.open(accountFileName.c_str(), ios::out|ios::binary);

    checkingFile.write(reinterpret_cast<char *>(head), sizeof(head));
    
    checkingFile.close();*/
}

//sets file name
void Checking::setFileName(string id)
{
    accountFileName = id + "Checking.txt";
    /*checkingFile.open(accountFileName.c_str(), ios::in|ios::binary);

    if (checkingFile.fail()) return;
    else
    {
        checkingFile.read(reinterpret_cast<char *>(head), sizeof(head));
        checkingFile.close();
    }*/

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
        cout << "5. Delete Account" << endl;
        cout << "6. Back" << endl;

        //validate input
        cin >> userSelection;
        errorCatcher.boundsCheck(userSelection, 1, 6);
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