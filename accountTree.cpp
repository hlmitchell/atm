#include "accountTree.h"

AccountTree::AccountTree()
{
    root = new treeNode;
    root->myChecking = new Checking;
    root->mySavings = new Savings;
    menuUserSelection = 0;
}

AccountTree::~AccountTree()
{
    delete root->myChecking;
    delete root->mySavings;
}

void AccountTree::createAnAccount(string id)
{
    chooseAccountType();

    if (menuUserSelection == 1) 
    {
        root->myChecking->createAccount(id);
    }

    else if (menuUserSelection == 2) 
    {
        root->mySavings->createAccount(id);
    }
}

void AccountTree::selectAnAccount()
{
    chooseAccountType();

    if (menuUserSelection == 1) 
    {
        root->myChecking->accessAccounts("checking");
    }

    else if (menuUserSelection == 2) 
    {
        root->mySavings->accessAccounts("savings");
    }
}

void AccountTree::requestTotalBalance()
{
    cout << fixed << setprecision(2);

    cout << endl << "Your total balance for all accounts is: $" 
         << root->myChecking->getTotalMoneyForAllAccounts() +
            root->mySavings->getTotalMoneyForAllAccounts()
         << endl;
}


void AccountTree::chooseAccountType()
{   
    displayAccountOptions();
    validateUserInput(3);
}

void AccountTree::displayAccountOptions()
{
    cout << endl << "Which type of account would you like to create?";
    cout << endl << endl;
    cout << "1. Checking" << endl;
    cout << "2. Savings" << endl;
    cout << "3. Back" << endl;
}

void AccountTree::validateUserInput(int upperBounds)
{
    cin >> menuUserSelection;
    inputErrorCatcher.checkForValidUserInput(menuUserSelection, 1, upperBounds);
    inputErrorCatcher.clearKeyboardBuffer();
}


void AccountTree::categorizeAccountFileNames(vector<string> accountFileNames)
{
    for (int i = 0; i < accountFileNames.size(); i++)
    {
        if (accountFileNames[i][0] == 'C')
            root->myChecking->downloadExistingAccounts(accountFileNames[i]);
        else if (accountFileNames[i][0] == 'S')
            root->mySavings->downloadExistingAccounts(accountFileNames[i]);
    }
}

vector<string> AccountTree::getAllAccountFileNames()
{
    vector<string> allFileNames;
    vector<string> someFileNames;
    
    allFileNames = root->myChecking->getAccountFileNames();
    someFileNames = root->mySavings->getAccountFileNames();

    allFileNames.insert(allFileNames.end(), someFileNames.begin(), someFileNames.end());
    return allFileNames;
}