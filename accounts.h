//Hannah Mitchell
//CS M20
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

        accountList myList;             //list of accounts

        accountNode *head;              //head of node/beginning of list
        accountNode *selectedAccount;   //current node/account

        string activeAccount;           //name of active account
        int userSelection;              //menu selection
        double withdep;                 //either with withdrawal or deposit amount
        char confirm;                   //user input for y/n prompt
        bool crossTransfer;             //indicates a transfer between account types

    public:
        //constructors and destructor
        Accounts();
        virtual ~Accounts();

        //setters
        void setFileNameGeneral(string);
        void resetSelectedAccount();
        void resetCrossTransfer();

        //getters
        bool getHead();
        vector<string> getAccountFileNames();
        accountNode *getSelectedAccount();
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

        //node actions
        void createNode(string);
        accountNode *findNode(string);
        void deleteNode(string);
        void displayNodes();

        //pure virtual functions
        virtual void setFileNameSpecific(string, string) = 0;
        virtual void displayAccounts() = 0;
        virtual void accountOptionsMenu() = 0;
        virtual void transfer() = 0;
};

//constructor
Accounts::Accounts()
{
    //set variables
    head = NULL;
    selectedAccount = NULL;
    activeAccount = "";
    userSelection = 0;
    withdep = 0;
}

//deletes linked list
Accounts::~Accounts()
{
    //for uploading the files
    accountNode *nodePtr;
    nodePtr = head;
    
    //create file for each account
    while (nodePtr)
    {
        myFile.open(nodePtr->accountFileName.c_str(), ios::out);
        myFile << nodePtr->accountName << endl;
        myFile << nodePtr->total << endl;
        //add history to file
        nodePtr->myHistory.uploadHistory(myFile);
        myFile.close();
        nodePtr = nodePtr->next;
    }

    //for deleting the linked list
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

//converts account name into file name
void Accounts::setFileNameGeneral(string id)
{
    //eliminate spaces from account name and store in file var
    string file;
    string temp = selectedAccount->accountName;
    for (int i = 0; i < temp.length(); i++)
    {
        if (temp[i] == ' ') continue;
        file += temp[i];
    }
    //label as checking or savings
    setFileNameSpecific(id, file);
}

//sets selected account to null
void Accounts::resetSelectedAccount()
{
    selectedAccount = NULL;
    activeAccount = "";
}

//reset cross transfer bool to false
void Accounts::resetCrossTransfer()
{
    crossTransfer = false;
}

//returns true or false if the list has been created
bool Accounts::getHead()
{
    if (head) return true;
    else return false;
}

//return account file name
vector<string> Accounts::getAccountFileNames()
{
    vector<string> temp;      //temp vector to return file names
    accountNode *nodePtr;     //temp pointer to cycle through nodes
    nodePtr = head;           //assign temp pointer to head of list

    //add all file names to temp vector
    while (nodePtr)
    {
        temp.push_back(nodePtr->accountFileName);
        nodePtr = nodePtr->next;
    }

    //return temp vector
    return temp;
}

//returns a selected account name
accountNode *Accounts::getSelectedAccount()
{
    return selectedAccount;
}

//returns money total of all checking accounts
double Accounts::getTotals()
{
    double totals = 0;      //holds total money
    accountNode *nodePtr;   //temp node pointer

    //initialize nodePtr to head of list
    nodePtr = head;

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
    createNode("NULL");
    //assign the memory address to myNode
    newNode = findNode("");
    //assign name
    newNode->accountName = tempName;
    //set to selected Account
    selectedAccount = newNode;
    //assign file name
    setFileNameGeneral(id);
    //reset
    resetSelectedAccount();

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
        selectedAccount = findNode(activeAccount);
        //if address is NULL, account name was not valid
        if (selectedAccount == NULL)
            cout << "Not an available account name!" << endl;
    } while (selectedAccount == NULL);
}

//deletes an account
void Accounts::deleteAccount()
{
    //if total funds aren't 0, do not delete account
    if (selectedAccount->total != 0)
    {
        cout << endl << "You must empty the account funds first!" << endl;
        return;
    }

    //confirm deletion
    cout << endl << "Delete account " << selectedAccount->accountName << " (Y/N)? ";
    cin >> confirm;
    errorCatcher.yesNo(confirm); //error check

    //if yes
    if (confirm == 'Y')
    {
        cout << "Account " << selectedAccount->accountName << " has been deleted!" << endl;
        //delete node and set selected account to NULL
        deleteNode(selectedAccount->accountName);
        selectedAccount = NULL;
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

    //send to history
    selectedAccount->myHistory.push("Deposit", withdep, selectedAccount->total, "NULL");
}

//merge two like accounts
void Accounts::merge()
{
    //merger account
    accountNode *merger;        //node to hold account to be merged into
    string mergerAccountName;   //name of merger account

    //check if other accounts exist for merger
    if (head->next == NULL)
    {
        cout << endl << "There are no other accounts of the same type!" << endl;
        return;
    }
    else displayAccounts();

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
        //transfer money to merger accounts
        merger->total += selectedAccount->total;
        cout << "Merge Successful!" << endl;

        //send to history
        merger->myHistory.push("Merger Deposit", selectedAccount->total, merger->total, "NULL");

        //delete account
        deleteNode(selectedAccount->accountName);
        selectedAccount = NULL;
    }
}

//transferring money between like accounts
void Accounts::sameTypeTransfer()
{
    //pointer for checking transfer
    accountNode *ptr;
    string transferAccountName;

    //check to see if other accounts of this type exist
    if (head->next == NULL)
    {
        cout << endl << "There are no other accounts of the same type!" << endl;
        return;
    }
    //if they do exist
    do 
    {
        //display accounts
        displayAccounts();
        
        //get account name for merger
        cin.ignore();
        cout << endl << "Enter the name of the account you wish to access: ";                
        getline(cin, transferAccountName);

        //find account address
        ptr = findNode(transferAccountName);
        //if address is NULL, account name was not valid
        if (ptr == NULL || ptr->accountName == selectedAccount->accountName)
        {
            cout << "Not an available account name!" << endl;
            ptr = NULL;
        }
    } while (ptr == NULL);

    //ask for transfer amount
    cout << "How much money would you like to transfer from " << selectedAccount->accountName
         << " to " << ptr->accountName << "? ";
    cin >> withdep;
    errorCatcher.boundsCheck(withdep, 0.0, selectedAccount->total);

    //ammend account totals
    selectedAccount->total -= withdep;
    ptr->total += withdep;

    //output success message and new totals for accounts
    cout << endl << "Successfully transfered $" << withdep << "!" << endl;
    cout << "New " << selectedAccount->accountName << " total is $" << selectedAccount->total << endl;
    cout << "New " << ptr->accountName << " total is $" << ptr->total << endl;

    //send to histories
    selectedAccount->myHistory.push("Transfer Withdrawal", withdep, selectedAccount->total, "NULL");
    ptr->myHistory.push("Transfer Deposit", withdep, ptr->total, "NULL");

}

//sends to history from transfer handler of user class
void Accounts::sendToHistory(string type, double num, double t, string d)
{
    //send to history
    selectedAccount->myHistory.push(type, num, t, d);
}

//creates a node
void Accounts::createNode(string fileName)
{
    //Taco
    myList.createNode(fileName);
    
    accountNode *newNode;   //holder for new node
    accountNode *nodePtr;   //temp node to move through list

    //make a new node for the linked list and assign variable values
    newNode = new accountNode;
    newNode->accountName = "";
    newNode->accountFileName = fileName;
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

    //if file is being dowloaded, assign variable names
    if (newNode->accountFileName != "NULL")
    {
        //open file
        myFile.open(newNode->accountFileName.c_str(), ios::in);

        //if file doesn't exist, delete file info and return
        if (!myFile)
        {
            cout << endl << "Some of your account files could not be found!" << endl;
            cout << "Deleting file accessor....." << endl;
            selectedAccount = newNode;
            deleteNode(newNode->accountName);
            return;
        }
        //otherwise upload file info
        myFile >> newNode->accountName;
        myFile >> newNode->total;

        //download history
        newNode->myHistory.downloadHistory(myFile);

        myFile.close();
    }
}

//finds node in list
accountNode *Accounts::findNode(string name)
{
    accountNode *nodePtr;   //temp holder

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
    //delete file
    remove(selectedAccount->accountFileName.c_str());
    
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

//display nodes of a type
void Accounts::displayNodes()
{
    accountNode *nodePtr;

    //initialize nodePtr to head of list
    nodePtr = head;

    //while nodePtr isn't NULL, move through list
    while (nodePtr)
    {
        //for merging accounts, the selected account name is not displayed
        if (selectedAccount != NULL)
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