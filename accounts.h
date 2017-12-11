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
        accountNode *nodePtr;           //pointer to selected account

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
        void setAccountFileNames(string);
        void setFileNameGeneral(string);
        void resetSelectedAccount();
        void resetCrossTransfer();

        //getters
        bool getHead();
        vector<string> getAccountFileNames();
        accountNode *getSelectedAccount();
        double getTotals();
        bool getCrossTransfer();

        //menu actions
        bool selectAnAccount(string);

        //account actions
        void createAccount(string);
        void selectAccount();
        void deleteAccount();
        void deposit();
        void merge();
        void sameTypeTransfer();
        void sendToHistory(string, double, double, string);

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
    activeAccount = "";
    userSelection = 0;
    withdep = 0;
}

//deletes linked list
Accounts::~Accounts()
{
    nodePtr = NULL;
}

void Accounts::setAccountFileNames(string name)
{
    myList.createNode(name);
}

//converts account name into file name
void Accounts::setFileNameGeneral(string id)
{
    //pointer to selected account
    nodePtr = myList.getSelectedAccount();
    
    //eliminate spaces from account name and store in file var
    string file;
    string temp = nodePtr->accountName;
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
    //pointer to selected account
    myList.setSelectedAccount(NULL);
    
    nodePtr = NULL;
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
    if (myList.getListHead()) return true;
    else return false;
}

//return account file name
vector<string> Accounts::getAccountFileNames()
{
    //temp vector to return file names
    vector<string> temp;
    //assign pointer to head of list
    nodePtr = myList.getListHead();          

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
    return myList.getSelectedAccount();
}

//returns money total of all checking accounts
double Accounts::getTotals()
{
    //holds total funds
    double totals = 0;

    //initialize nodePtr to head of list
    nodePtr = myList.getListHead();

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

//select an account run through
bool Accounts::selectAnAccount(string accountType)
{
    //if no account exists then break
    if (!getHead()) 
    {
        cout << endl << "You have not created a " << accountType <<  " account yet!" << endl;
        return false;
    }
    //if returning from cross transfer go straight to menu
    else if (myList.getSelectedAccount())
    {
        accountOptionsMenu();
        return false;
    }
    else
    {   
        //else display all checking accounts
        displayAccounts();       
        selectAccount();

        //indicates transfer across account types
        bool transfer;

        //display further menu
        accountOptionsMenu();
                
        //check for transfer selection in account options menu
        transfer = getCrossTransfer();
        if (transfer == true) return true;
        else return false;
    }
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
    errorCatcher.checkString(tempName);
    tempNode = myList.findNode(tempName);
    //make sure name isn't repeat
    while (tempNode != NULL)
    {
        cout << "Name already taken! Please try again: ";
        getline(cin, tempName);
        tempNode = myList.findNode(tempName);
        
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
        nodePtr = myList.findNode(activeAccount);
        //if address is NULL, account name was not valid
        if (nodePtr == NULL)
            cout << "Not an available account name!" << endl;
    } while (nodePtr == NULL);

    //set selected account
    myList.setSelectedAccount(nodePtr);
}

//deletes an account
void Accounts::deleteAccount()
{
    //set to selected account
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
        resetSelectedAccount();
    }
}

//deposit money
void Accounts::deposit()
{
    //set to selected account
    nodePtr = myList.getSelectedAccount();
    
    //enter deposit amount
    cout << endl << "Deposit amount: ";
    cin >> withdep;
    errorCatcher.boundsCheck(withdep, 0.0, 1000000000.0);

    //if deposit is more than 0
    if (withdep > 0)
    {
        //add to total
        nodePtr->total += withdep;
        //display deposit amount and new total
        cout << "Successfully deposited $" << withdep << endl;
        cout << "New " << nodePtr->accountName << " total is $" << nodePtr->total << endl;

        //send to history
        nodePtr->myHistory.push("Deposit", withdep, nodePtr->total, "NULL");
    }
}

//merge two like accounts
void Accounts::merge()
{
    //set to head
    nodePtr = myList.getListHead();

    //merger account pointer and account name
    accountNode *mergPtr;
    string mergerAccountName;

    //check if other accounts exist for merger
    if (nodePtr->next == NULL)
    {
        cout << endl << "There are no other accounts of the same type!" << endl;
        return;
    }
    else displayAccounts();

    //set to selected account
    nodePtr = myList.getSelectedAccount();

    //while inputed account name doesn't exist, continue to prompt 
    do {
        //get account name
        cout << endl << "With which account would you like to merge " 
        << nodePtr->accountName << "? ";
        getline(cin, mergerAccountName);
        //find account address
        mergPtr = myList.findNode(mergerAccountName);
        //if address is NULL, account name was not valid
        if (mergPtr == NULL || mergPtr->accountName == nodePtr->accountName)
        {
            cout << "Not an available account name!" << endl;
            mergPtr = NULL;
        }
    } while (mergPtr == NULL);

    //verify with user
    cout << "Are you sure you want to merge " << nodePtr->accountName
         << " into " << mergPtr->accountName << " (Y/N)? ";
    cin >> confirm;
    errorCatcher.yesNo(confirm);

    //delete selected account and transfer funds to merger account
    if (confirm == 'Y')
    {
        //transfer money to merger accounts
        mergPtr->total += nodePtr->total;
        cout << "Merge Successful!" << endl;

        //send to history
        mergPtr->myHistory.push("Merger Deposit", nodePtr->total, mergPtr->total, "NULL");

        //delete account
        myList.deleteNode(nodePtr->accountName);
        resetSelectedAccount();
    }
}

//transferring money between like accounts
void Accounts::sameTypeTransfer()
{
    //set to head
    nodePtr = myList.getListHead();
    
    //pointer for checking transfer
    accountNode *transferPtr;
    string transferAccountName;

    //check to see if other accounts of this type exist
    if (nodePtr->next == NULL)
    {
        cout << endl << "There are no other accounts of the same type!" << endl;
        return;
    }

    //set to selected account
    nodePtr = myList.getSelectedAccount();

    //if accounts exist
    do 
    {
        //display accounts
        displayAccounts();
        
        //get account name for transfer
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

    //if transfer is not 0
    if (withdep > 0)
    {  
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

}

//sends to history from transfer handler of user class
void Accounts::sendToHistory(string type, double num, double t, string d)
{
    //set to selected account
    nodePtr = myList.getSelectedAccount();
    
    //send to history
    nodePtr->myHistory.push(type, num, t, d);
}

#endif