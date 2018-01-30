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

    public:
        History();
        ~History();

        void addToHistory(string, double, double, string);
        void displayHistory();
        void uploadHistory(fstream &);
        void downloadHistory(fstream &);
};

#endif