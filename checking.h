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
        void displayAccounts();
        
};

Checking::Checking() : Accounts ()
{}

void Checking::displayAccounts()
{
    cout << endl << "Checking Account(s)" << endl;
    displayNodes();
}

#endif