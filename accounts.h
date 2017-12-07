//Hannah Mitchell
//CS M10B
//December 5th 2017

#ifndef ACCOUNTS_H
#define ACCOUNTS_H

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>

#include "inputError.h"
#include "history.h"
#include "accountList.h"

using namespace std;

class Accounts
{
    protected:
        InputError errorCatcher;        //error catcher
        fstream myFile;                 //file for specific account

        accountList myList;             //list for accounts
        string activeAccount;           //name of active account
        vector<string> accountNames;    //checking account file name list

        accountNode *nodePtr;           //pointer to selected account

        int userSelection;              //menu selection
        double withdep;                 //either with withdrawal or deposit amount
        char confirm;                   //user input for y/n prompt
        bool crossTransfer;             //indicates a transfer between account types

    public:
        //constructor
        Accounts();
        ~Accounts();

        //setters
        void setFileNameGeneral(string);
        void resetCrossTransfer();
        void setAccountFileNames(string);

        //getters
        bool getHead();
        vector<string> getAccountFileNames();
        double getTotals();
        bool getCrossTransfer();

        //account actions
        void createAccount(string);
        void selectAccount();
        void deleteAccount();
        void deposit();
        void merge();
        void sameTypeTransfer();
        void sendToHistory(string, double, double, string);

        //pure virtual functions
        virtual void setFileNameSpecific(string, string, accountNode*) = 0;
        virtual void displayAccounts() = 0;
        virtual void accountOptionsMenu() = 0;
        virtual void transfer() = 0;

        //for transfer handler use in userMenu
        accountNode *getSelectedAccount();
        void resetSelectedAccount();
};

//constructor
Accounts::Accounts()
{
    userSelection = 0;
    withdep = 0;
}

Accounts::~Accounts()
{
    nodePtr = NULL;
}

//converts account name into file name
void Accounts::setFileNameGeneral(string id)
{
    //temp vars
    string file;

    //set node pointer to selected account
    nodePtr = myList.getSelectedAccount();
    
    //eliminate spaces from account name and store in file var
    string temp = nodePtr->accountName;
    for (int i = 0; i < temp.length(); i++)
    {
        if (temp[i] == ' ') continue;
        file += temp[i];
    }
    //label as checking or savings
    setFileNameSpecific(id, file, nodePtr);
}

//reset cross transfer bool to false
void Accounts::resetCrossTransfer()
{
    crossTransfer = false;
}

//creates node with set file names
void Accounts::setAccountFileNames(string name)
{
    myList.createNode(name);
}

//returns true or false if the list has been created
bool Accounts::getHead()
{   
    if (myList.getHead() != NULL) return true;
    else return false;
}

//return account file name
vector<string> Accounts::getAccountFileNames()
{
    vector<string> temp;            //temp vector to return file names
    nodePtr = myList.getHead();     //assign temp pointer to head of list

    //add all file names to temp vector
    while (nodePtr)
    {
        temp.push_back(nodePtr->accountFileName);
        nodePtr = nodePtr->next;
    }

    //return temp vector
    return temp;
}

//returns money total of all checking accounts
double Accounts::getTotals()
{
    //holds total money
    double totals = 0;      

    //initialize nodePtr to head of list
    nodePtr = myList.getHead();

    //if no accounts exist return 0
    if (nodePtr == NULL) return 0;

    //add all account totals together
    while (nodePtr)
    {
        totals += nodePtr->total;
        nodePtr = nodePtr->next;
    }
    return totals;
}

//return cross Transfer bool
bool Accounts::getCrossTransfer()
{
    return crossTransfer;
}

//creates a new account
void Accounts::createAccount(string id)
{
    accountNode *newNode;       //temp holder for new node
    string tempName;            //temp holder for account name
    accountNode *tempNode;      //temp holder to allow movement through list
    
    //name the account
    cout << endl << "What would you like to name this account? ";
    cin.ignore();

    //assign name to temp variable
    getline(cin, tempName);
    tempNode = myList.findNode(tempName);
    //make sure name isn't repeat or blank
    while (tempNode != NULL || tempName == "")
    {
        //if name is a repeat prompt again
        if (tempNode != NULL)
        {
            cout << "Name already taken! Please try again: ";
            getline(cin, tempName);
            tempNode = myList.findNode(tempName);
        }
        //if name is blank prompt again
        else
        {
            cout << "Account must have a name! Please try again: ";
            getline(cin, tempName);
            tempNode = myList.findNode(tempName);
        }
    }

    //create a new node in the list
    myList.createNode("NULL");
    //assign the memory address to myNode
    newNode = myList.findNode("");
    //assign name
    newNode->accountName = tempName;
    //set to selected Account
    myList.setSelectedAccount(newNode);
    //assign file name
    setFileNameGeneral(id);
    //reset
    myList.resetSelectedAccount();

    //deposit money into the account
    cout << "How much money would you like to deposit (Enter 0 if none)? ";
    cin >> newNode->total;
    errorCatcher.boundsCheck(newNode->total, 0.0, 1000000000.0);

    //success message
    cout << endl << "Successfully created account " << newNode->accountName
         << " with current value of $" << fixed << setprecision(2)
         << newNode->total << "!" << endl;

    //send to history
    newNode->myHistory.push("Open Deposit", newNode->total, newNode->total, "NULL");
}

//selects an account to edit 
void Accounts::selectAccount()
{
    //clear input
    cin.ignore();

    //while inputed account name doesn't exist, continue to prompt 
    do {
        //get account name
        cout << endl << "Enter the name of the account you wish to access: ";
        getline(cin, activeAccount);
        //find account address
        nodePtr = myList.findNode(activeAccount);
        //if address is NULL, account name was not valid
        if (nodePtr == NULL)
            cout << "Not an available account name!" << endl;
    } while (nodePtr == NULL);

    //set selected account to node pointer
    myList.setSelectedAccount(nodePtr);
}

//deletes an account
void Accounts::deleteAccount()
{
    nodePtr = myList.getSelectedAccount();

    //if total funds aren't 0, do not delete account
    if (nodePtr->total != 0)
    {
        cout << endl << "You must empty the account funds first!" << endl;
        return;
    }

    //confirm deletion
    cout << endl << "Delete account " << nodePtr->accountName << " (Y/N)? ";
    cin >> confirm;
    errorCatcher.yesNo(confirm); //error check

    //if yes
    if (confirm == 'Y')
    {
        cout << "Account " << nodePtr->accountName << " has been deleted!" << endl;
        //delete node and set selected account to NULL
        myList.deleteNode(nodePtr->accountName);
        myList.resetSelectedAccount();
    }
}

//deposit money
void Accounts::deposit()
{
    nodePtr = myList.getSelectedAccount();
    
    //enter deposit amount
    cout << endl << "Deposit amount: ";
    cin >> withdep;
    errorCatcher.boundsCheck(withdep, 0.0, 1000000000.0);

    //add to total
    nodePtr->total += withdep;
    //display deposit amount and new total
    cout << "Successfully deposited $" << withdep << endl;
    cout << "New " << nodePtr->accountName << " total is $" << nodePtr->total << endl;

    //send to history
    nodePtr->myHistory.push("Deposit", withdep, nodePtr->total, "NULL");
}

//merge two like accounts
void Accounts::merge()
{
    //get head
    accountNode *headPtr;
    headPtr = myList.getHead();

    //get selected account
    nodePtr = myList.getSelectedAccount();

    //temp vars for merger node
    accountNode *mergerPtr;
    string mergerAccountName;

    //check if other accounts exist for merger
    if (headPtr->next == NULL)
    {
        cout << endl << "There are no other accounts of the same type!" << endl;
        return;
    }
    else displayAccounts();

    //while inputed account name doesn't exist, continue to prompt 
    do {
        //get account name
        cout << endl << "With which account would you like to merge " 
        << nodePtr->accountName << "? ";
        getline(cin, mergerAccountName);
        //find account address
        mergerPtr = myList.findNode(mergerAccountName);
        //if address is NULL, account name was not valid
        if (mergerPtr == NULL || mergerPtr->accountName == nodePtr->accountName)
        {
            cout << "Not an available account name!" << endl;
            mergerPtr = NULL;
        }
    } while (mergerPtr == NULL);

    //verify with user
    cout << "Are you sure you want to merge " << nodePtr->accountName
         << " into " << mergerPtr->accountName << " (Y/N)? ";
    cin >> confirm;
    errorCatcher.yesNo(confirm);

    //delete selected account and transfer funds to merger account
    if (confirm == 'Y')
    {
        //transfer money to merger accounts
        mergerPtr->total += nodePtr->total;
        cout << "Merge Successful!" << endl;

        //send to history
        mergerPtr->myHistory.push("Merger Deposit", nodePtr->total, mergerPtr->total, "NULL");

        //delete account
        myList.deleteNode(nodePtr->accountName);
        myList.resetSelectedAccount();
    }
}

//transferring money between like accounts
void Accounts::sameTypeTransfer()
{
    //pointer to head
    accountNode *headPtr;
    headPtr = myList.getHead();

    //pointer to selected account
    nodePtr = myList.getSelectedAccount();
    
    //pointer for transfer
    accountNode *transferPtr;
    string transferAccountName;

    //check to see if other accounts of this type exist
    if (headPtr->next == NULL)
    {
        cout << endl << "There are no other accounts of the same type!" << endl;
        return;
    }
    //if they do exist
    do 
    {
        //display accounts
        displayAccounts();
        
        //get account name for trasnfer
        cin.ignore();
        cout << endl << "Enter the name of the account you wish to access: ";                
        getline(cin, transferAccountName);

        //find account address
        transferPtr = myList.findNode(transferAccountName);
        //if address is NULL, account name was not valid
        if (transferPtr == NULL || transferPtr->accountName == nodePtr->accountName)
        {
            cout << "Not an available account name!" << endl;
            transferPtr = NULL;
        }
    } while (transferPtr == NULL);

    //ask for transfer amount
    cout << "How much money would you like to transfer from " << nodePtr->accountName
         << " to " << transferPtr->accountName << "? ";
    cin >> withdep;
    errorCatcher.boundsCheck(withdep, 0.0, nodePtr->total);

    //ammend account totals
    nodePtr->total -= withdep;
    transferPtr->total += withdep;

    //output success message and new totals for accounts
    cout << endl << "Successfully transfered $" << withdep << "!" << endl;
    cout << "New " << nodePtr->accountName << " total is $" << nodePtr->total << endl;
    cout << "New " << transferPtr->accountName << " total is $" << transferPtr->total << endl;

    //send to histories
    nodePtr->myHistory.push("Transfer Withdrawal", withdep, nodePtr->total, "NULL");
    transferPtr->myHistory.push("Transfer Deposit", withdep, transferPtr->total, "NULL");

}

//sends to history from transfer handler of user class
void Accounts::sendToHistory(string type, double num, double t, string d)
{
    //selected account
    nodePtr = myList.getSelectedAccount();
    
    //send to history
    nodePtr->myHistory.push(type, num, t, d);
}

//for transfer handler use, return selected account
accountNode *Accounts::getSelectedAccount()
{
    return myList.getSelectedAccount();
}
        
//for transfer handler use
void Accounts::resetSelectedAccount()
{
    myList.resetSelectedAccount();
}

#endif