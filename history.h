#ifndef HISTORY_H
#define HISTORY_H

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <ctime>
#include <vector>

using namespace std;

struct accountHistory
{
    string action;
    double amount;
    double total;
    string date;
    struct accountHistory *next;
};

class History
{
    protected:
        accountHistory *top;
        time_t rawTime;

        accountHistory *accountHistoryNode;
        accountHistory *nextaccountHistoryNode;
        accountHistory *newTransactionHistory;

    public:
        History();
        ~History();

        void deleteHistory();

        void addToHistory(string, double, double);
        void addToHistory(string, double, double, string);
        void timeStampTransaction();
        void allocateNewHistoryNode(string, double, double);
        void appendHistoryNodeToList();

        void displayHistory();
        bool checkForHistory();
        void displayHistoryHeader();
        void displayTransactionHistory();

        void uploadHistory(fstream &);
        void downloadHistory(fstream &);
};

#endif