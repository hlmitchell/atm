#include "accountList.h"

//constructor
accountList::accountList()
{
    head = NULL;
    selectedAccount = NULL;
}

//destructor
accountList::~accountList()
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

//sets selected Account
void accountList::setSelectedAccount(accountNode *node)
{
    selectedAccount = node;
}

//return selected account
accountNode *accountList::getSelectedAccount()
{
    return selectedAccount;
}

//return head of list
accountNode *accountList::getListHead()
{
    return head;
}

//creates a node
void accountList::createNode(string fileName)
{
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
            cout << endl << newNode->accountFileName << " could not be found!" << endl;
            cout << "Removing memory file....." << endl;
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
accountNode *accountList::findNode(string name)
{
    //pointer to node
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

//display nodes of a type
void accountList::displayNodes()
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

//deletes a node
void accountList::deleteNode(string name)
{
    //delete file
    remove(selectedAccount->accountFileName.c_str());
    
    //pointers to nodes
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