//ATM MACHINE
//Hannah Mitchell
//CS M10B
//December 11th 2017

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
    string action;                  //action that occured
    double amount;                  //amount of money moved
    double total;                   //new account total after move
    string date;                    //date and time of transaction
    struct accountHistory *next;    //pointer to next accountHistory node
};

class History
{
    protected:
        accountHistory *top;    //top of linked list stack of account history
        time_t rawTime;         //time stamp holder

    public:
        //constructors and destructor
        History();
        ~History();

        //history manipulators
        void addToHistory(string, double, double, string);
        void displayHistory();
        void uploadHistory(fstream &);
        void downloadHistory(fstream &);
};

#endif