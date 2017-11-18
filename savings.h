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
        string accountTYPE;
        string accountName;
        double savingsTotal;
    public:
        Savings();
        void mainMenu();
        void openStatus(bool);
        void editSavingsTotal(double);
        bool getActivated();
        double getSavingsTotal();

};

Savings::Savings()
{
    accountTYPE = "savings";
    accountName = "";
    savingsTotal = 0;
}

void Savings::mainMenu()
{
    cout << endl << "Savings Menu" << endl;
}

void Savings::editSavingsTotal(double num)
{
    savingsTotal += num;
}

double Savings::getSavingsTotal()
{
    return savingsTotal;
}

#endif