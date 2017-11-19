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
        string accountTYPE;
        string accountName;
        double total;
    public:
        Accounts();
        void editTotal(double);
        double getTotal();

        virtual void accountMenu() = 0;

};

Accounts::Accounts()
{
    accountName = "";
    total = 0;
}

void Accounts::editTotal(double num)
{
    total += num;
}

double Accounts::getTotal()
{
    return total;
}

#endif

