#include "history.h"

//constructor sets top to NULL
History::History()
{
    top = NULL;
}

//destructor deletes linked list
History::~History()
{
    //temp pointers
    accountHistory *nodePtr;
    accountHistory *nextNode;

    //position nodePtr at top
    nodePtr = top;

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

//pushes new history node onto top of stack
void History::addToHistory(string transactionType, double transactionAmount, double newTotal, string date)
{
    accountHistory *newTransactionHistory;    //pointer to new node

    //get time
    time (&rawTime);

    //allocate new node and store arguments there
    newTransactionHistory = new accountHistory;
    newTransactionHistory->action = transactionType;
    newTransactionHistory->amount = transactionAmount;
    newTransactionHistory->total = newTotal;
    if (date == "NULL")
    {
        newTransactionHistory->date = ctime(&rawTime);
        //remove '\n' from end
        newTransactionHistory->date.pop_back();
    }
    else newTransactionHistory->date = date;

    //if stack is empty, assign new node to top
    if (top == NULL)
    {
        top = newTransactionHistory;
        top->next = NULL;
    }
    //otherwise set new node to top and push others down stack
    else
    {
        newTransactionHistory->next = top;
        top = newTransactionHistory;
    }    
}

//display account history
void History::displayHistory()
{
    accountHistory *transactionHistory;    //temp pointer
    transactionHistory = top;              //set temp pointer to top of stack

    //if top is NULL, there is no history available
    if (transactionHistory == NULL) 
    {
        cout << endl << "There seems to be nothing here!" << endl;
        return;
    }

    //header message
    cout << endl << "***Transaction History***" << endl;
    //item line description
    cout << endl << left << setw(21) << "Description" << setw(14) << "Amount" << setw(23) << "Available Balance";
    cout << setw(20) << "Posting Date" << endl;

    //if top isn't NULL, go through list and display accounts
    while (transactionHistory)
    {
        //formatting
        cout << fixed << setprecision(2) << left;
        cout << endl << setw(21) << transactionHistory->action;
        cout << setw(14) << transactionHistory->amount;
        cout << setw(23)<< transactionHistory->total;
        cout << setw(20) << transactionHistory->date << endl;
        //move to next node
        transactionHistory = transactionHistory->next;
    }

    //footer message
    cout << endl << "***End Transaction History***" << endl;
    return;
}

//upload history into file
void History::uploadHistory(fstream &file)
{    
    //temp nodes for moving through files
    accountHistory *nodePtr;
    accountHistory *prevNode;

    //set nodePtr to end of list
    nodePtr = top;
    while(nodePtr) 
    {
        if (nodePtr->next == NULL) break;
        nodePtr = nodePtr->next;
    }

    //upload files in reverse order
    while (nodePtr != top)
    {
        //upload files
        file << nodePtr->action << endl;
        file << nodePtr->amount << endl;
        file << nodePtr->total << endl;
        file << nodePtr->date << endl;

        //set prevNode to node before nodePtr
        prevNode = top;
        while (prevNode)
        {
            if (prevNode->next == nodePtr || prevNode->next == NULL) break;
            prevNode = prevNode->next;
        }

        //set nodePtr to previous node then start again
        nodePtr = prevNode;
    } 

    //upload top files
    if (nodePtr == top)
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