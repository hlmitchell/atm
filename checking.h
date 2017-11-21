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
        
    public:
        Checking();
        void createAccount();
        
};

Checking::Checking() : Accounts ()
{}

void Checking::createAccount()
{
    appendNode();
    cout << endl << "What would you like to name this account? " << endl;
}

#endif