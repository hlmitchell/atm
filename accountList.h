//ATM MACHINE
//Hannah Mitchell
//CS M10B
//December 11th 2017

#ifndef ACCOUNTLIST_H
#define ACCOUNTLIST_H

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>

#include "history.h"

using namespace std;

//node for linked list of accounts
struct accountNode {
    string accountFileName;         //file name
    string accountName;             //account name
    double totalFunds;                   //total money in account
    History myHistory;              //instantiate history for the account
    struct accountNode *next;       //pointer to next node in list
};

class accountList {
    
    private:
        accountNode *head;              //pointer to head of list
        accountNode *activeAccount;     //current selected account 

        fstream myFile;                 //account files

    public:
        //constrcutor and destructor
        accountList();
        ~accountList();

        //setters
        void setActiveAccount(accountNode *);

        //getters
        accountNode *getActiveAccount();
        accountNode *getListHead();

        //node manipulators
        void createNode(string);
        accountNode *findNode(string);
        void displayNodes();
        void deleteNode(string);

};

#endif
