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
        string accountTYPE;
        string accountName;
        double checkingTotal;
    public:
        Checking();
        void mainMenu();
        void openStatus(bool);
        void editCheckingTotal(double);
        bool getActivated();
        double getCheckingTotal();

};

Checking::Checking()
{
    accountTYPE = "checking";
    accountName = "";
    checkingTotal = 0;
}

void Checking::mainMenu()
{
    cout << endl << "Checking Menu" << endl;
}

void Checking::editCheckingTotal(double num)
{
    checkingTotal += num;
}

double Checking::getCheckingTotal()
{
    return checkingTotal;
}

#endif