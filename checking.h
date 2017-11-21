#ifndef CHECKING_H
#define CHECKING_H

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

#include "accounts.h"

using namespace std;

class Checking : public Accounts
{
    protected:
        accountNode *myNode;
    public:
        Checking();
        void createAccount();
        
};

Checking::Checking() : Accounts ()
{}

void Checking::createAccount()
{
    //create a new node in the list
    createNode();
    //assign the memory address to myNode
    myNode = findNode("");
    //name the account
    cout << endl << "What would you like to name this account? ";
    cin.ignore();
    getline(cin, myNode->accountName);
    //deposit into the account
    cout << endl << "How much money would you like to deposit (Enter 0 if none)? ";
    cin >> myNode->total;
    //boundsCheck(myNode->total, 0, 1000000000000000);



}

#endif