//ATM MACHINE
//Hannah Mitchell
//CS M10B
//December 11th 2017

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
        fstream checkingFile;

    public:
        Checking();

        void specifyFileType(string, string);

        void displayAccounts();
        void accountOptionsMenu();
        void displayMenuOptions();
        void menuInterface();

        void withdrawFunds();
        void requestWithdrawalAmount();
        bool checkForOverdraft();
        void confirmedWithdrawal();
        void displayNewTotals();

        void transferFunds();
        
};

#endif