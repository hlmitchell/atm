#ifndef HISTORY_H
#define HISTORY_H

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <ctime>
#include <vector>

using namespace std;

struct AccountHistory
{
    string action;
    double amount;
    double total;
    string date;
    struct AccountHistory *next;
};

class History
{
protected:
    AccountHistory *top;
    time_t rawTime;

    void deleteHistory();
    AccountHistory* allocateNewHistoryNode(string, double, double);
    void appendHistoryNodeToList(AccountHistory*);
    
    bool checkForHistory();
    void displayTransactions();
    
    void uploadHistory(fstream&, AccountHistory*);
    void writeToFile(fstream &, AccountHistory*);
    void downloadFirstHistoryTransaction(fstream &);
    void downloadRemainingHistoryTransactions(fstream &);
    
public:
    History() {top = NULL;};
    ~History() {deleteHistory();}

    void addToHistory(string, double, double);
    void addToHistory(string, double, double, string);
    void displayHistory();

    void uploadHistory(fstream &);
    void downloadHistory(fstream &);
};

#endif
