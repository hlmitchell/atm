#ifndef ACCOUNTS_H
#define ACCOUNTS_H

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

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
        //node head
        accountNode *head;

    public:
        Accounts();
        virtual ~Accounts();
        void createAccount();
        void createNode();
        accountNode *findNode(string);
        void deleteNode(string);
        void displayNodes();

        virtual void displayAccounts() = 0;
};

Accounts::Accounts()
{
    head = NULL;
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
}

void Accounts::createAccount()
{
    accountNode *newNode;
    //create a new node in the list
    createNode();
    //assign the memory address to myNode
    newNode = findNode("");
    //name the account
    cout << endl << "What would you like to name this account? ";
    cin.ignore();
    getline(cin, newNode->accountName);
    //deposit into the account
    cout << endl << "How much money would you like to deposit (Enter 0 if none)? ";
    cin >> newNode->total;
    //boundsCheck(myNode->total, 0, 1000000000000000);
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
    if (!head)
    {
        head = newNode;
    }
    //else add new node to end of list
    else
    {
        //initialize nodePtr to head of list
        nodePtr = head;
        //find the last node in the list
        while (nodePtr->next)
        {
            nodePtr = nodePtr->next;
        }
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
        if (nodePtr->accountName == name)
        {
            return nodePtr;
        }
        else
        {
            nodePtr = nodePtr->next;
        }
    }

    cout << endl << "There is no account by that name!" << endl;
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
            //display the account values
            cout << nodePtr->accountName << endl;
            cout << "$" << nodePtr->total << endl << endl;

            //move to next node
            nodePtr = nodePtr->next;
    }
}

#endif

