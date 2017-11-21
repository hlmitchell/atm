#ifndef ACCOUNTS_H
#define ACCOUNTS_H

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

class Accounts
{
    protected:
        //node for linked list of accounts
        struct accountNode {
            string accountName;
            double total;
            struct accountNode *next;
        };
        //node head
        accountNode *head;

    public:
        Accounts();
        virtual ~Accounts();
        void appendNode();
        void deleteNode(string);

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
    while (nodePtr->next)  //***************(nodePtr!=NULL)
    {
        //save a pointer to the next node
        nextNode = nodePtr->next;

        //delete current node
        delete nodePtr;

        //move nodePtr to next node
        nodePtr = nextNode;
    }
}

//deletes one node
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

void Accounts::appendNode()
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

#endif

