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
        void accountMenu();

};

Savings::Savings() : Accounts()
{
}

void Savings::accountMenu()
{
    cout << endl << "Savings Menu" << endl;
}

#endif