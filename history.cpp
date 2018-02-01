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


//upload history into file
void History::uploadHistory(fstream &file)
{    
    accountHistoryNode = top;
    while(accountHistoryNode) 
    {
        if (accountHistoryNode->next == NULL) break;
        accountHistoryNode = accountHistoryNode->next;
    }

    //upload files in reverse order
    while (accountHistoryNode != top)
    {
        //upload files
        file << accountHistoryNode->action << endl;
        file << accountHistoryNode->amount << endl;
        file << accountHistoryNode->total << endl;
        file << accountHistoryNode->date << endl;

        //set nextaccountHistoryNode to node before accountHistoryNode
        nextaccountHistoryNode = top;
        while (nextaccountHistoryNode)
        {
            if (nextaccountHistoryNode->next == accountHistoryNode || nextaccountHistoryNode->next == NULL) break;
            nextaccountHistoryNode = nextaccountHistoryNode->next;
        }

        //set accountHistoryNode to previous node then start again
        accountHistoryNode = nextaccountHistoryNode;
    } 

    //upload top files
    if (accountHistoryNode == top)
    {
        file << top->action << endl;
        file << top->amount << endl;
        file << top->total << endl;
        file << top->date << endl;
    }
}

//download history from file
void History::downloadHistory(fstream &accountFile)
{
    //temp vars
    string accountType, date, dummy;
    double transactionAmount, finalTotal;

    //extract first history which has an extra dummy variable
    getline(accountFile, dummy);
    getline(accountFile, accountType);
    accountFile >> transactionAmount;
    accountFile >> finalTotal;
    getline(accountFile, dummy);
    getline(accountFile, date);

    addToHistory(accountType, transactionAmount, finalTotal, date);

    //extract rest of data and place in list in correct order
    while (accountFile)
    {
        getline(accountFile, accountType);
        accountFile >> transactionAmount;
        accountFile >> finalTotal;
        getline(accountFile, dummy);
        getline(accountFile, date);

        addToHistory(accountType, transactionAmount, finalTotal, date);
    }

    //delete weird extra node
    top = top->next;
}