#include "history.h"

History::History()
{
    top = NULL;
}

History::~History()
{
    deleteHistory();
}

void History::deleteHistory()
{
    accountHistoryNode = top;

    while (accountHistoryNode != NULL)
    {
        nextaccountHistoryNode = accountHistoryNode->next;
        delete accountHistoryNode;
        accountHistoryNode = nextaccountHistoryNode;
    }
}

void History::addToHistory(string transactionType, double transactionAmount, double newTotal)
{
    allocateNewHistoryNode(transactionType, transactionAmount, newTotal);
    timeStampTransaction();

    appendHistoryNodeToList();  
}

void History::addToHistory(string transactionType, double transactionAmount, double newTotal, string date)
{
    allocateNewHistoryNode(transactionType, transactionAmount, newTotal);
    newTransactionHistory->date = date;

    appendHistoryNodeToList();
}

void History::allocateNewHistoryNode(string transactionType, double transactionAmount, double newTotal)
{
    newTransactionHistory = new accountHistory;
    newTransactionHistory->action = transactionType;
    newTransactionHistory->amount = transactionAmount;
    newTransactionHistory->total = newTotal;
}

void History::timeStampTransaction()
{
    time (&rawTime);
    newTransactionHistory->date = ctime(&rawTime);
    newTransactionHistory->date.pop_back();
}

void History::appendHistoryNodeToList()
{
    if (top == NULL)
    {
        top = newTransactionHistory;
        top->next = NULL;
    }
    else
    {
        newTransactionHistory->next = top;
        top = newTransactionHistory;
    }  
}

void History::displayHistory()
{
    accountHistoryNode = top;

    if (!checkForHistory()) return;

    displayHistoryHeader();
    displayTransactionHistory();

    cout << endl << "***End Transaction History***" << endl;
}

bool History::checkForHistory()
{
    if (accountHistoryNode == NULL) 
    {
        cout << endl << "There seems to be nothing here!" << endl;
        return false;
    }
    return true;
}

void History::displayHistoryHeader()
{
    cout << endl << "***Transaction History***" << endl;
    cout << endl << left << setw(21) << "Description" << setw(14) << "Amount" << setw(23) << "Available Balance";
    cout << setw(20) << "Posting Date" << endl;
}

void History::displayTransactionHistory()
{
    while (accountHistoryNode)
    {
        cout << fixed << setprecision(2) << left;
        cout << endl << setw(21) << accountHistoryNode->action;
        cout << setw(14) << accountHistoryNode->amount;
        cout << setw(23)<< accountHistoryNode->total;
        cout << setw(20) << accountHistoryNode->date << endl;

        accountHistoryNode = accountHistoryNode->next;
    }
}

void History::uploadHistory(fstream &file)
{    
    setHistoryNodeToBottomOfList();
    uploadFilesInReverseOrder(file);
}

void History::setHistoryNodeToBottomOfList()
{
    accountHistoryNode = top;
    while(accountHistoryNode) 
    {
        if (accountHistoryNode->next == NULL) break;
        accountHistoryNode = accountHistoryNode->next;
    }
}

void History::uploadFilesInReverseOrder(fstream &file)
{
    while (accountHistoryNode != top)
    {
        writeToFile(file);

        moveUpList();
        accountHistoryNode = nextaccountHistoryNode;

        uploadTopFile(file);
    } 
}

void History::moveUpList()
{
    nextaccountHistoryNode = top;
    while (nextaccountHistoryNode)
    {
        if (nextaccountHistoryNode->next == accountHistoryNode || nextaccountHistoryNode->next == NULL) break;
        nextaccountHistoryNode = nextaccountHistoryNode->next;
    }
}

void History::uploadTopFile(fstream &file)
{
    if (accountHistoryNode == top)
    {
        writeToFile(file);
    }
}

void History::writeToFile(fstream &file)
{
    file << accountHistoryNode->action << endl;
    file << accountHistoryNode->amount << endl;
    file << accountHistoryNode->total << endl;
    file << accountHistoryNode->date << endl;
}

void History::downloadHistory(fstream &accountFile)
{
    string accountType, date, dummy;
    double transactionAmount, finalTotal;

    downloadFirstHistoryTransaction(accountFile);
    downloadRemainingHistoryTransactions(accountFile);
}

void History::downloadFirstHistoryTransaction(fstream &accountFile)
{
    string accountType, date, dummy;
    double transactionAmount, finalTotal;
    
    //read first history transaction which has 2 dummy variables that I can't figure out
    getline(accountFile, dummy);
    getline(accountFile, accountType);
    accountFile >> transactionAmount;
    accountFile >> finalTotal;
    getline(accountFile, dummy);
    getline(accountFile, date);

    addToHistory(accountType, transactionAmount, finalTotal, date);
}

void History::downloadRemainingHistoryTransactions(fstream &accountFile)
{
    string accountType, date, dummy;
    double transactionAmount, finalTotal;
    
    //read remaining history transactions which have 1 dummy variable that I can't figure out
    while (accountFile)
    {
        getline(accountFile, accountType);
        accountFile >> transactionAmount;
        accountFile >> finalTotal;
        getline(accountFile, dummy);
        getline(accountFile, date);

        addToHistory(accountType, transactionAmount, finalTotal, date);
    }

    //the top node will be a weird incomplete Node that I can't figure out so this step ignores it
    top = top->next;
}