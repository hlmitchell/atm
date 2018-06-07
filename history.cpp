#include "history.h"

void History::deleteHistory()
{
    AccountHistory *nextNode;

    while (top != NULL)
    {
        nextNode = top->next;
        delete top;
        top = nextNode;
    }
}

void History::addToHistory(string transactionType, double transactionAmount,
                           double newTotal)
{
    AccountHistory *newNode;
    newNode = allocateNewHistoryNode(transactionType, transactionAmount,
                                     newTotal);
    
    time (&rawTime);
    newNode->date = ctime(&rawTime);
    newNode->date.pop_back();

    appendHistoryNodeToList(newNode);
}

void History::addToHistory(string transactionType, double transactionAmount,
                           double newTotal, string date)
{
    AccountHistory *newNode;
    newNode = allocateNewHistoryNode(transactionType, transactionAmount, newTotal);
    newNode->date = date;

    appendHistoryNodeToList(newNode);
}

AccountHistory* History::allocateNewHistoryNode(string transactionType,
                                    double transactionAmount, double newTotal)
{
    AccountHistory *newTransactionHistory = new AccountHistory;
    newTransactionHistory->action = transactionType;
    newTransactionHistory->amount = transactionAmount;
    newTransactionHistory->total = newTotal;
    return newTransactionHistory;
}

void History::appendHistoryNodeToList(AccountHistory *newNode)
{
    if (top == NULL)
    {
        top = newNode;
        top->next = NULL;
    }
    else
    {
        newNode->next = top;
        top = newNode;
    }  
}

void History::displayHistory()
{
    if (!checkForHistory()) return;

    cout << endl << "***Transaction History***" << endl;
    cout << endl << left << setw(21) << "Description" << setw(14) << "Amount"
         << setw(23) << "Available Balance";
    cout << setw(20) << "Posting Date" << endl;
    
    displayTransactions();

    cout << endl << "***End Transaction History***" << endl;
}

bool History::checkForHistory()
{
    if (top == NULL)
    {
        cout << endl << "There seems to be nothing here!" << endl;
        return false;
    }
    return true;
}

void History::displayTransactions()
{
    AccountHistory *node = top;
    
    while (node)
    {
        cout << fixed << setprecision(2) << left;
        cout << endl << setw(21) << node->action;
        cout << setw(14) << node->amount;
        cout << setw(23)<< node->total;
        cout << setw(20) << node->date << endl;

        node = node->next;
    }
}

void History::uploadHistory(fstream &file)
{
    uploadHistory(file, top);   //call private, recursive overload
}

void History::uploadHistory(fstream &file, AccountHistory *node)
{
    if (node != NULL)
    {
        uploadHistory(file, node->next);
        writeToFile(file, node);
    }
}

void History::writeToFile(fstream &file, AccountHistory *node)
{
    file << node->action << endl;
    file << node->amount << endl;
    file << node->total << endl;
    file << node->date << endl;
}

void History::downloadHistory(fstream &accountFile)
{
    downloadFirstHistoryTransaction(accountFile);
    downloadRemainingHistoryTransactions(accountFile);
}

void History::downloadFirstHistoryTransaction(fstream &accountFile)
{
    string accountType, date, dummy;
    double transactionAmount, finalTotal;
    
    //read first history transaction which has 2 dummy variables
    //that I can't figure out
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
    
    //read remaining history transactions which have 1 dummy
    //variable that I can't figure out
    while (accountFile)
    {
        getline(accountFile, accountType);
        accountFile >> transactionAmount;
        accountFile >> finalTotal;
        getline(accountFile, dummy);
        getline(accountFile, date);

        addToHistory(accountType, transactionAmount, finalTotal, date);
    }

    //the top node will be a weird incomplete Node that I can't figure out
    //so this step ignores it
    top = top->next;
}
