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
    pointerToAnAccount = head;

    while (pointerToAnAccount)
    {
        if (skipActiveAccountNameForMergers()) continue;
        displayAccountNameAndFunds();

        pointerToAnAccount = pointerToAnAccount->next;    
    }
}

bool accountList::skipActiveAccountNameForMergers()
{
    if (activeAccount != NULL)
        if (activeAccount->accountName == pointerToAnAccount->accountName)
        {
            pointerToAnAccount = pointerToAnAccount->next;
            return true;
        }
    return false;
}

void accountList::displayAccountNameAndFunds()
{
    cout << pointerToAnAccount->accountName << ": ";
    cout << fixed << setprecision(2);
    cout << "$" << pointerToAnAccount->totalFunds << endl;
}

void accountList::deleteNode(string name)
{
    deleteAccountFile();

    if (head->accountName == name)
    {
        deleteListHead();
    }
    else
    {
        transverseAccountListForDeletion(name);
    }
}

void accountList::deleteAccountFile()
{
    remove(activeAccount->accountFileName.c_str());
}

void accountList::deleteListHead()
{
    pointerToAnAccount = head->next;
    delete head;
    head = pointerToAnAccount;
}

void accountList::transverseAccountListForDeletion(string name)
{
    pointerToAnAccount = head;
    while (pointerToAnAccount != NULL && pointerToAnAccount->accountName != name)
    {
        pointerToNextAccount = pointerToAnAccount;
        pointerToAnAccount = pointerToAnAccount->next;
    }
    
    deleteAccount();
}

void accountList::deleteAccount()
{
    if (pointerToAnAccount)
    {
        pointerToNextAccount->next = pointerToAnAccount->next;
        delete pointerToAnAccount;
    }
}