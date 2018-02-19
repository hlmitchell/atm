#ifndef ACCOUNTTREE
#define ACCOUNTTREE

#include "checking.h"
#include "savings.h"
#include "inputError.h"

#include <iostream>
#include <vector>

struct treeNode
{
    Checking *myChecking;
    Savings *mySavings;

    treeNode *leftBranch;
    treeNode *rightBranch;
};

class AccountTree
{
    private:

        treeNode *root;
        vector<string> accountFileNames;

        int menuUserSelection;
        InputError inputErrorCatcher;

    public:
        AccountTree();
        ~AccountTree();

        void createAnAccount(string);
        void selectAnAccount();
        void requestTotalBalance();

        void chooseAccountType();
        void displayAccountOptions();
        void validateUserInput(int);

        void categorizeAccountFileNames(vector<string>);
        vector<string> getAllAccountFileNames();
};

#endif