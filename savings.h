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
        double savingsTotal;
        bool activated;
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
    savingsTotal = 0;
    activated = false;
}

void Savings::mainMenu()
{
    cout << endl << "Savings Menu" << endl;
}

void Savings::editSavingsTotal(double num)
{
    savingsTotal += num;
}

void Savings::openStatus(bool x)
{
    activated = x;
}

bool Savings::getActivated()
{
    return activated;
}

double Savings::getSavingsTotal()
{
    return savingsTotal;
}

#endif