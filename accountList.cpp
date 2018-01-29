//ATM MACHINE
//Hannah Mitchell
//CS M10B
//December 11th 2017

#include "accountList.h"

accountList::accountList()
{
    head = NULL;
    activeAccount = NULL;
}

accountList::~accountList()
{
    pointerToAnAccount = head;
    
    createAccountFiles();

    deleteAccountList();
}

void accountList::createAccountFiles()
{
    while (pointerToAnAccount)
    {
        myFile.open(pointerToAnAccount->accountFileName.c_str(), ios::out);

        addAccountDataToFile();
        addAccountHistoryToFile();

        myFile.close();

        pointerToAnAccount = pointerToAnAccount->next;
    }
}

void accountList::addAccountDataToFile()
{
    myFile << pointerToAnAccount->accountName << endl;
    myFile << pointerToAnAccount->totalFunds << endl;
}

void accountList::addAccountHistoryToFile()
{
    pointerToAnAccount->myHistory.uploadHistory(myFile);
}

void accountList::deleteAccountList()
{
    pointerToAnAccount = head;

    while (pointerToAnAccount != NULL)
    {
        pointerToNextAccount = pointerToAnAccount->next;
        delete pointerToAnAccount;
        pointerToAnAccount = pointerToNextAccount;
    }
    activeAccount = NULL;
}

void accountList::setActiveAccount(accountNode *node)
{
    activeAccount = node;
}

accountNode *accountList::getActiveAccount()
{
    return activeAccount;
}

accountNode *accountList::getListHead()
{
    return head;
}

void accountList::downloadNode(string fileName)
{
    createNode(fileName);
    
    myFile.open(pointerToAnAccount->accountFileName.c_str(), ios::in);
    if (!checkIfAccountFileExists()) return;
    downloadFileContents();
    myFile.close();
}

void accountList::createNode(string fileName)
{
    assignAccountVariables(fileName);
    appendNewAccountToAccountList();
}

void accountList::assignAccountVariables(string fileName)
{
    pointerToAnAccount = new accountNode;
    pointerToAnAccount->accountName = "";
    pointerToAnAccount->accountFileName = fileName;
    pointerToAnAccount->totalFunds = 0;
    pointerToAnAccount->next = NULL;
}

void accountList::appendNewAccountToAccountList()
{
    if (!head) head = pointerToAnAccount;
    
    else
    {
        pointerToNextAccount = head;
        while (pointerToNextAccount->next) pointerToNextAccount = pointerToNextAccount->next;
        pointerToNextAccount->next = pointerToAnAccount;
    }
}

bool accountList::checkIfAccountFileExists()
{
    if (!myFile)
    {
        cout << endl << pointerToAnAccount->accountFileName << " could not be found!" << endl;
        cout << "Removing memory file....." << endl;
        activeAccount = pointerToAnAccount;
        deleteNode(pointerToAnAccount->accountName);
        return false;
    }
    return true;
}

void accountList::downloadFileContents()
{
    myFile >> pointerToAnAccount->accountName;
    myFile >> pointerToAnAccount->totalFunds;

    pointerToAnAccount->myHistory.downloadHistory(myFile);
}

accountNode *accountList::findNode(string name)
{
    pointerToAnAccount = head;

    while (pointerToAnAccount)
    {
        if (pointerToAnAccount->accountName == name) return pointerToAnAccount;
        else pointerToAnAccount = pointerToAnAccount->next;
    }
    return NULL;
}

void accountList::displayNodes()
{
    //initialize pointerToAnAccount to head of list
    pointerToAnAccount = head;

    //while pointerToAnAccount isn't NULL, move through list
    while (pointerToAnAccount)
    {
        //for merging accounts, the selected account name is not displayed
        if (activeAccount != NULL)
            if (activeAccount->accountName == pointerToAnAccount->accountName)
            {
                pointerToAnAccount = pointerToAnAccount->next;
                continue;
            }

        //display the account values
        cout << pointerToAnAccount->accountName << ": ";
        //formatting
        cout << fixed << setprecision(2);
        cout << "$" << pointerToAnAccount->totalFunds << endl;

        //move to next node
        pointerToAnAccount = pointerToAnAccount->next;    
    }
}

void accountList::deleteNode(string name)
{
    //delete file
    remove(activeAccount->accountFileName.c_str());

    //check head of chain first
    if (head->accountName == name)
    {
        pointerToAnAccount = head->next;
        delete head;
        head = pointerToAnAccount;
    }

    //else delete node from chain
    else
    {
        //initialize pointerToAnAccount to head of list
        pointerToAnAccount = head;
        //run through nodes to find accountName that matches
        while (pointerToAnAccount != NULL && pointerToAnAccount->accountName != name)
        {
            pointerToNextAccount = pointerToAnAccount;
            pointerToAnAccount = pointerToAnAccount->next;
        }
        //deletes node
        if (pointerToAnAccount)
        {
            pointerToNextAccount->next = pointerToAnAccount->next;
            delete pointerToAnAccount;
        }

    }
}