//Hannah Mitchell
//CS M10B
//December 5th 2017

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
        fstream checkingFile;       //checking file

    public:
        //constructor
        Checking();

        //setters
        void setFileNameSpecific(string, string);

        //account options
        void displayAccounts();
        void accountOptionsMenu();
        void withdraw();
        void transfer();
        
};

#endif