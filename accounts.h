#ifndef ACCOUNTS_H
#define ACCOUNTS_H

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

class Accounts
{
    protected:
        double total;
    public:
        Accounts();

        //virtual deposit() = 0;
        //void transfer();
};

Accounts::Accounts()
{
    total = 0;
}

#endif

