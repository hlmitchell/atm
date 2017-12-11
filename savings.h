//ATM MACHINE
//Hannah Mitchell
//CS M10B
//December 11th 2017

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
        fstream savingsFile;    //savings file
    public:
        //constructor
        Savings();

        //setters
        void setFileNameSpecific(string, string);

        //account options
        void displayAccounts();
        void accountOptionsMenu();
        void transfer();
};

#endif