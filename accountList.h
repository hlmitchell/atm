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

struct accountNode {
    string accountFileName;
    string accountName;
    double totalFunds;
    History myHistory;
    struct accountNode *next;
};

class accountList {
    
    private:
        accountNode *head;
        accountNode *activeAccount;
        accountNode *pointerToAnAccount;
        accountNode *pointerToNextAccount;

        fstream myFile;

    public:
        accountList();

        ~accountList();
        void createAccountFiles();
        void addAccountDataToFile();
        void addAccountHistoryToFile();
        void deleteAccountList();

        void setActiveAccount(accountNode *);

        accountNode *getActiveAccount();
        accountNode *getListHead();

        void createNode(string);
        void assignAccountVariables(string);
        void appendNewAccountToAccountList();

        void downloadNode(string);
        bool checkIfAccountFileExists();
        void downloadFileContents();

        accountNode *findNode(string);
        void displayNodes();
        void deleteNode(string);
};

#endif
