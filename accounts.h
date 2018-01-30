//ATM MACHINE
//Hannah Mitchell
//CS M10B
//December 11th 2017

#ifndef ACCOUNTS_H
#define ACCOUNTS_H

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>

#include "inputError.h"
#include "accountList.h"

using namespace std;

class Accounts
{
    protected:
        InputError inputErrorCatcher;

        accountList listOfOpenAccounts;   
        accountNode *pointerToActiveAccount;
        accountNode *secondAccount;
        
        string activeAccountName;   
        string secondAccountName;


        int menuUserSelection;                 
        double withdrawOrDepositValue;     
        char yesOrNo;                       

    public:
        Accounts();
        virtual ~Accounts();

        void downloadExistingAccounts(string);

        void setTextFileName(string);
        string removeSpacesFromAccountName();

        void resetActiveAccount();

        bool getHeadOfAccountList();
        vector<string> getAccountFileNames();
        accountNode *callGetActiveAccount();
        double getTotalMoneyForAllAccounts();

        void accessAccounts(string);

        void displayActiveAccountDetails();
        void validateMenuInput(int);

        void createAccount(string);
        void nameAccount();
        void verifyUniqueAccountName(string);
        void setAccountName(string);
        void makeInitialDeposit();
        void confirmationOfNewAccountMessage();

        void selectAccount();
        void requestAccountName();

        void deleteAccount();
        bool checkIfAccountFundsAreZero();
        void confirmAccountDeletion();
        void confirmedDeletion();

        void depositFunds();
        void requestDepositAmount();
        void addFundsToTotal();

        void mergeAccounts();
        bool checkIfOtherAccountsExist();
        void requestSecondAccountName();
        void verifyAccountMerge();
        void confirmedMerge();

        void sameAccountTypeTransfer();
        void requestTransferAmount();
        void confirmedTransfer();
        void ammendAccountTotals();
        void transferSuccessMessage();

        void sendToHistory(string, double, double, string);

        //virtual void displayMenuOptions();
        //virtual void menuInterface();
        virtual void specifyFileType(string, string) = 0;
        virtual void displayAccounts() = 0;
        virtual void accountOptionsMenu() = 0;
        virtual void transferFunds() = 0;
};

#endif