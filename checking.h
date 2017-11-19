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
        void accountMenu();
        
};

Checking::Checking() : Accounts ()
{
    accountTYPE = "checking";
}

void Checking::accountMenu()
{
    cout << endl << "Checking Menu" << endl;
}

#endif