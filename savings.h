#ifndef SAVINGS_H
#define SAVINGS_H

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

#include "accounts.h"

using namespace std;

class Savings : public Accounts
{
    protected:

    public:
        Savings();
        void displayAccounts();

};

Savings::Savings() : Accounts()
{
}

void Savings::displayAccounts()
{
    cout << endl << "Savings Account(s)" << endl;
    displayNodes();
}

#endif