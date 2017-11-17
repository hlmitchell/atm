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
        double checkingTotal;
        bool activated;
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
    checkingTotal = 0;
    activated = false;
}

void Checking::mainMenu()
{
    cout << endl << "Checking Menu" << endl;
}

void Checking::editCheckingTotal(double num)
{
    checkingTotal += num;
}

void Checking::openStatus(bool x)
{
    activated = x;
}

bool Checking::getActivated()
{
    return activated;
}

double Checking::getCheckingTotal()
{
    return checkingTotal;
}

#endif