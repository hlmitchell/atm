#ifndef ACCOUNTS_H
#define ACCOUNTS_H

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

#include "input.h"

using namespace std;

//node for linked list of accounts
struct accountNode {
    string accountName;
    double total;
    struct accountNode *next;
};

class Accounts
{
    protected:
        string accountFileName;
        Input errorCatcher;

        //node head
        accountNode *head;
        accountNode *selectedAccount;

        string activeAccount;
        int userSelection;
        double withdep;
        char confirm;    
        bool crossTransfer; 

    public:
        Accounts();
        virtual ~Accounts();
        bool getHead();
        accountNode *getSelectedAccount();

        void createAccount();
        void selectAccount();
        void deleteAccount();
        void deposit();
        void merge();

        void createNode();
        accountNode *findNode(string);
        void deleteNode(string);
        void displayNodes();

        //virtual void setFileName() = 0;
        virtual void displayAccounts() = 0;
        virtual bool accountOptionsMenu() = 0;
        virtual void transfer() = 0;
};

Accounts::Accounts()
{
    head = NULL;
    selectedAccount = NULL;
    activeAccount = "";
    userSelection = 0;
    withdep = 0;
}

//deletes linked list
Accounts::~Accounts()
{
    accountNode *nodePtr;
    accountNode *nextNode;

    //position nodePtr at head
    nodePtr = head;

    //while nodePtr is not at the end of the list
    while (nodePtr != NULL)
    {
        //save a pointer to the next node
        nextNode = nodePtr->next;
        //delete current node
        delete nodePtr;
        //move nodePtr to next node
        nodePtr = nextNode;
    }
    selectedAccount = NULL;
}

//returns true or false if the list has been created
bool Accounts::getHead()
{
    if (head) return true;
    else return false;
}

accountNode *Accounts::getSelectedAccount()
{
    return selectedAccount;
}

//creates a new account
void Accounts::createAccount()
{
    accountNode *newNode;
    string tempName;
    accountNode *tempNode;
    
    //name the account
    cout << endl << "What would you like to name this account? ";
    cin.ignore();

    //assign name to temp variable
    getline(cin, tempName);
    tempNode = findNode(tempName);
    //make sure name isn't repeat or blank
    while (tempNode != NULL || tempName == "")
    {
        //if name is a repeat prompt again
        if (tempNode != NULL)
        {
            cout << "Name already taken! Please try again: ";
            getline(cin, tempName);
            tempNode = findNode(tempName);
        }
        //if name is blank prompt again
        else
        {
            cout << "Account must have a name! Please try again: ";
            getline(cin, tempName);
            tempNode = findNode(tempName);
        }
    }

    //create a new node in the list
    createNode();
    //assign the memory address to myNode
    newNode = findNode("");
    //assign name
    newNode->accountName = tempName;

    //deposit money into the account
    cout << "How much money would you like to deposit (Enter 0 if none)? ";
    cin >> newNode->total;
    errorCatcher.boundsCheck(newNode->total, 0.0, 1000000000.0);

    //success message
    cout << endl << "Successfully created account " << newNode->accountName
         << " with current value of $" << fixed << setprecision(2)
         << newNode->total << "!" << endl;
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
        selectedAccount = findNode(activeAccount);
        //if address is NULL, account name was not valid
        if (selectedAccount == NULL)
            cout << "Not an available account name!" << endl;
    } while (selectedAccount == NULL);
}

void Accounts::deleteAccount()
{
    //if total funds aren't 0, do not delete account
    if (selectedAccount->total != 0)
    {
        cout << endl << "You must transfer your funds to another account first!" << endl;
        return;
    }

    //confirm deletion
    cout << endl << "Delete account " << selectedAccount->accountName << " (Y/N)? ";
    cin >> confirm;
    errorCatcher.yesNo(confirm); //error check

    if (confirm == 'Y')
    {
        cout << "Account " << selectedAccount->accountName << " has been deleted!" << endl;;
        deleteNode(selectedAccount->accountName);
    }
}

//deposit money
void Accounts::deposit()
{
    //enter deposit amount
    cout << endl << "Deposit amount: ";
    cin >> withdep;
    errorCatcher.boundsCheck(withdep, 0.0, 1000000000.0);

    //add to total
    selectedAccount->total = selectedAccount->total += withdep;
    //display deposit amount and new total
    cout << "Successfully deposited $" << withdep << endl;
    cout << "New " << selectedAccount->accountName << " total is $" << selectedAccount->total << endl;
}

//merge two like accounts
void Accounts::merge()
{
    //merger account
    accountNode *merger;
    string mergerAccountName;

    //check if other accounts exist for merger
    if (head->next == NULL)
    {
        cout << endl << "There are no other accounts of the same type!" << endl;
        return;
    }
    else
    {
        cout << endl << "Other Related Accounts" << endl;
        displayNodes();
    }

    //while inputed account name doesn't exist, continue to prompt 
    do {
        //get account name
        cout << endl << "With which account would you like to merge " 
        << selectedAccount->accountName << "? ";
        getline(cin, mergerAccountName);
        //find account address
        merger = findNode(mergerAccountName);
        //if address is NULL, account name was not valid
        if (merger == NULL || merger->accountName == selectedAccount->accountName)
        {
            cout << "Not an available account name!" << endl;
            merger = NULL;
        }
    } while (merger == NULL);

    //verify with user
    cout << "Are you sure you want to merge " << selectedAccount->accountName
         << " into " << merger->accountName << " (Y/N)? ";
    cin >> confirm;
    errorCatcher.yesNo(confirm);

    //delete selected account and transfer funds to merger account
    if (confirm == 'Y')
    {
        merger->total += selectedAccount->total;
        deleteNode(selectedAccount->accountName);
        selectedAccount = NULL;
        cout << "Merge Successful!" << endl;
    }
}

//creates a node
void Accounts::createNode()
{
    accountNode *newNode;
    accountNode *nodePtr;

    //make a new node for the linked list and assign variable values
    newNode = new accountNode;
    newNode->accountName = "";
    newNode->total = 0;
    newNode->next = NULL;

    //if there are no nodes yet, make the first one
    if (!head) head = newNode;
    //else add new node to end of list
    else
    {
        //initialize nodePtr to head of list
        nodePtr = head;
        //find the last node in the list
        while (nodePtr->next) nodePtr = nodePtr->next;
        //insert newNode as the last node
        nodePtr->next = newNode;
    }
}

//finds node in list
accountNode *Accounts::findNode(string name)
{
    accountNode *nodePtr;

    //initialize nodePtr to head of list
    nodePtr = head;

    //while nodePtr isn't NULL, move through list
    while (nodePtr)
    {
        if (nodePtr->accountName == name) return nodePtr;
        else nodePtr = nodePtr->next;
    }
    return NULL;
}

//deletes a node
void Accounts::deleteNode(string name)
{
    accountNode *nodePtr;
    accountNode *previousNode;

    //check head of chain first
    if (head->accountName == name)
    {
        nodePtr = head->next;
        delete head;
        head = nodePtr;
    }

    //else delete node from chain
    else
    {
        //initialize nodePtr to head of list
        nodePtr = head;
        //run through nodes to find accountName that matches
        while (nodePtr != NULL && nodePtr->accountName != name)
        {
            previousNode = nodePtr;
            nodePtr = nodePtr->next;
        }
        //deletes node
        if (nodePtr)
        {
            previousNode->next = nodePtr->next;
            delete nodePtr;
        }

    }
}

void Accounts::displayNodes()
{
    accountNode *nodePtr;

    //initialize nodePtr to head of list
    nodePtr = head;

    //while nodePtr isn't NULL, move through list
    while (nodePtr)
    {
        //for merging accounts, the selected account name is not displayed
        if (selectedAccount != NULL)//avoids segmentation fault
            if (selectedAccount->accountName == nodePtr->accountName)
            {
                nodePtr = nodePtr->next;
                continue;
            }

        //display the account values
        cout << nodePtr->accountName << ": ";
        //formatting
        cout << fixed << setprecision(2);
        cout << "$" << nodePtr->total << endl;

        //move to next node
        nodePtr = nodePtr->next;    
    }
}

#endif