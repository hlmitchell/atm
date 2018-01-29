//ATM MACHINE
//Hannah Mitchell
//CS M10B
//December 11th 2017

#include "accounts.h"

Accounts::Accounts()
{
    activeAccountName = "";
    mergerAccountName = "";
    transferAccountName = "";
    menuUserSelection = 0;
    withdrawOrDepositValue = 0;
}

Accounts::~Accounts()
{
    pointerToActiveAccount = NULL;
}

void Accounts::downloadExistingAccounts(string accountName)
{
    listOfOpenAccounts.createNode(accountName);
}

void Accounts::setTextFileName(string id)
{
    pointerToActiveAccount = listOfOpenAccounts.getActiveAccount();
    
    string accountNameWithoutSpaces = removeSpacesFromAccountName();

    specifyFileType(id, accountNameWithoutSpaces);
}

string Accounts::removeSpacesFromAccountName()
{
    string accountNameWithoutSpaces;
    string originalAccountName = pointerToActiveAccount->accountName;

    for (int i = 0; i < originalAccountName.length(); i++)
    {
        if (originalAccountName[i] == ' ') continue;
        accountNameWithoutSpaces += originalAccountName[i];
    }

    return accountNameWithoutSpaces;
}

void Accounts::resetActiveAccount()
{
    listOfOpenAccounts.setActiveAccount(NULL);
    
    pointerToActiveAccount = NULL;
    activeAccountName = "";
}

bool Accounts::getHeadOfAccountList()
{
    if (listOfOpenAccounts.getListHead()) return true;
    else return false;
}

vector<string> Accounts::getAccountFileNames()
{
    vector<string> fileNames;
    pointerToActiveAccount = listOfOpenAccounts.getListHead();          

    while (pointerToActiveAccount)
    {
        fileNames.push_back(pointerToActiveAccount->accountFileName);
        pointerToActiveAccount = pointerToActiveAccount->next;
    }

    return fileNames;
}

accountNode *Accounts::callGetActiveAccount()
{
    return listOfOpenAccounts.getActiveAccount();
}

double Accounts::getTotalMoneyForAllAccounts()
{
    double accountTotals = 0;

    pointerToActiveAccount = listOfOpenAccounts.getListHead();
    if (pointerToActiveAccount == NULL) return 0;

    while (pointerToActiveAccount)
    {
        accountTotals += pointerToActiveAccount->totalFunds;
        pointerToActiveAccount = pointerToActiveAccount->next;
    }
    return accountTotals;
}

void Accounts::selectAccount(string accountType)
{
    if (!getHeadOfAccountList()) 
    {
        cout << endl << "You have not created a " << accountType <<  " account yet!" << endl;
        return;
    }
    else
    {   
        displayAccounts();       
        selectAccount();
        accountOptionsMenu();
    }
}

void Accounts::createAccount(string id)
{ 
    nameAccount();
    setTextFileName(id);

    pointerToActiveAccount = listOfOpenAccounts.getActiveAccount();

    makeInitialDeposit();

    confirmationOfNewAccountMessage();
    
    sendToHistory(
        "Open Deposit", 
        pointerToActiveAccount->totalFunds, 
        pointerToActiveAccount->totalFunds, 
        "NULL"
    );

    resetActiveAccount();
}

void Accounts::nameAccount()
{
    string accountName;        
    
    cout << endl << "What would you like to name this account? ";
    cin.ignore();
    getline(cin, accountName);

    inputErrorCatcher.removeExtraWhiteSpaceFromString(accountName);
    verifyUniqueAccountName(accountName);

    setAccountName(accountName);
}

void Accounts::verifyUniqueAccountName(string accountName)
{
    accountNode *verifiedAccount;
    verifiedAccount = listOfOpenAccounts.findNode(accountName);

    while (verifiedAccount != NULL)
    {
        cout << "Name already taken! Please try again: ";
        getline(cin, accountName);
        verifiedAccount = listOfOpenAccounts.findNode(accountName);
    }
}

void Accounts::setAccountName(string accountName)
{
    accountNode *newAccount;
    
    listOfOpenAccounts.createNode("NULL");
    newAccount = listOfOpenAccounts.findNode("");

    newAccount->accountName = accountName;
    listOfOpenAccounts.setActiveAccount(newAccount);
}

void Accounts::makeInitialDeposit()
{
    cout << "How much money would you like to deposit (Enter 0 if none)? ";
    cin >> pointerToActiveAccount->totalFunds;
    inputErrorCatcher.checkForValidUserInput(pointerToActiveAccount->totalFunds, 0.0, 1000000000.0);
}

void Accounts::confirmationOfNewAccountMessage()
{
    cout << endl << "Successfully created account " << pointerToActiveAccount->accountName
         << " with current value of $" << fixed << setprecision(2)
         << pointerToActiveAccount->totalFunds << "!" << endl;
}

void Accounts::selectAccount()
{
    requestAccountName();
    listOfOpenAccounts.setActiveAccount(pointerToActiveAccount);
}

void Accounts::requestAccountName()
{
    cin.ignore();

    do {
        cout << endl << "Enter the name of the account you wish to access: ";
        getline(cin, activeAccountName);

        pointerToActiveAccount = listOfOpenAccounts.findNode(activeAccountName);

        if (pointerToActiveAccount == NULL)
            cout << "Not an available account name!" << endl;

    } while (pointerToActiveAccount == NULL);
}

void Accounts::deleteAccount()
{
    pointerToActiveAccount = listOfOpenAccounts.getActiveAccount();
    
    if (!checkIfAccountFundsAreZero()) return;

    confirmAccountDeletion();
    
    if (yesOrNo == 'Y')
    {
        cout << "Account " << pointerToActiveAccount->accountName << " has been deleted!" << endl;
        confirmedDeletion();
    }
}

void Accounts::confirmedDeletion()
{
    listOfOpenAccounts.deleteNode(pointerToActiveAccount->accountName);
    resetActiveAccount();
}

bool Accounts::checkIfAccountFundsAreZero()
{
    if (pointerToActiveAccount->totalFunds != 0)
    {
        cout << endl << "You must empty the account funds first!" << endl;
        return false;
    }
    return true;
}

void Accounts::confirmAccountDeletion()
{
    cout << endl << "Delete account " << pointerToActiveAccount->accountName << " (Y/N)? ";
    cin >> yesOrNo;
    inputErrorCatcher.yesOrNoValidator(yesOrNo);
}

void Accounts::depositFunds()
{
    pointerToActiveAccount = listOfOpenAccounts.getActiveAccount();
    
    requestDepositAmount();
    addFundsToTotal();
}

void Accounts::requestDepositAmount()
{
    cout << endl << "Deposit amount: ";
    cin >> withdrawOrDepositValue;
    inputErrorCatcher.checkForValidUserInput(withdrawOrDepositValue, 0.0, 1000000000.0);
}

void Accounts::addFundsToTotal()
{
    if (withdrawOrDepositValue > 0)
    {
        pointerToActiveAccount->totalFunds += withdrawOrDepositValue;
    
        cout << "Successfully deposited $" << withdrawOrDepositValue << endl;
        cout << "New " << pointerToActiveAccount->accountName << " total is $" << pointerToActiveAccount->totalFunds << endl;

        pointerToActiveAccount->myHistory.addToHistory("Deposit", withdrawOrDepositValue, pointerToActiveAccount->totalFunds, "NULL");
    }
}

void Accounts::mergeAccounts()
{
    if (!checkIfOtherAccountsExist()) return;

    pointerToActiveAccount = listOfOpenAccounts.getActiveAccount();

    requestMergerAccountName();
    verifyAccountMerge();

    if (yesOrNo == 'Y')
    {
        confirmedMerge();
    }
}

bool Accounts::checkIfOtherAccountsExist()
{
    pointerToActiveAccount = listOfOpenAccounts.getListHead();

    if (pointerToActiveAccount->next == NULL)
    {
        cout << endl << "There are no other accounts of the same type!" << endl;
        return false;
    }
    else displayAccounts();
    return true;
}

void Accounts::requestMergerAccountName()
{
    do {
        cout << endl << "With which account would you like to merge " 
        << pointerToActiveAccount->accountName << "? ";
        getline(cin, mergerAccountName);

        mergerAccount = listOfOpenAccounts.findNode(mergerAccountName);

        if (mergerAccount == NULL || mergerAccount->accountName == pointerToActiveAccount->accountName)
        {
            cout << "Not an available account name!" << endl;
            mergerAccount = NULL;
        }

    } while (mergerAccount == NULL);
}

void Accounts::verifyAccountMerge()
{
    cout << "Are you sure you want to merge " << pointerToActiveAccount->accountName
         << " into " << mergerAccount->accountName << " (Y/N)? ";
    cin >> yesOrNo;
    inputErrorCatcher.yesOrNoValidator(yesOrNo);
}

void Accounts::confirmedMerge()
{
    mergerAccount->totalFunds += pointerToActiveAccount->totalFunds;
    cout << "Merge Successful!" << endl;

    mergerAccount->myHistory.addToHistory("Merger Deposit", pointerToActiveAccount->totalFunds, mergerAccount->totalFunds, "NULL");

    confirmedDeletion();
}

void Accounts::sameAccountTypeTransfer()
{
    pointerToActiveAccount = listOfOpenAccounts.getListHead();
    
    //check to see if other accounts of this type exist
    if (pointerToActiveAccount->next == NULL)
    {
        cout << endl << "There are no other accounts of the same type!" << endl;
        return;
    }

    //set to selected account
    pointerToActiveAccount = listOfOpenAccounts.getActiveAccount();

    //if accounts exist
    do 
    {
        //display accounts
        displayAccounts();
        
        //get account name for transfer
        cin.ignore();
        cout << endl << "Enter the name of the account you wish to access: ";                
        getline(cin, transferAccountName);

        //find account address
        transferAccount = listOfOpenAccounts.findNode(transferAccountName);
        //if address is NULL, account name was not valid
        if (transferAccount == NULL || transferAccount->accountName == pointerToActiveAccount->accountName)
        {
            cout << "Not an available account name!" << endl;
            transferAccount = NULL;
        }
    } while (transferAccount == NULL);

    //ask for transfer amount
    cout << "How much money would you like to transfer from " << pointerToActiveAccount->accountName
         << " to " << transferAccount->accountName << "? ";
    cin >> withdrawOrDepositValue;
    inputErrorCatcher.checkForValidUserInput(withdrawOrDepositValue, 0.0, pointerToActiveAccount->totalFunds);

    //if transfer is not 0
    if (withdrawOrDepositValue > 0)
    {  
        //ammend account totals
        pointerToActiveAccount->totalFunds -= withdrawOrDepositValue;
        transferAccount->totalFunds += withdrawOrDepositValue;
 
        //output success message and new totals for accounts
        cout << endl << "Successfully transfered $" << withdrawOrDepositValue << "!" << endl;
        cout << "New " << pointerToActiveAccount->accountName << " total is $" << pointerToActiveAccount->totalFunds << endl;
        cout << "New " << transferAccount->accountName << " total is $" << transferAccount->totalFunds << endl;

        //send to histories
        pointerToActiveAccount->myHistory.addToHistory("Transfer Withdrawal", withdrawOrDepositValue, pointerToActiveAccount->totalFunds, "NULL");
        transferAccount->myHistory.addToHistory("Transfer Deposit", withdrawOrDepositValue, transferAccount->totalFunds, "NULL");
    }

}

void Accounts::sendToHistory(string transactionType, double transactionAmount, double newTotal, string date)
{
    pointerToActiveAccount = listOfOpenAccounts.getActiveAccount();
    pointerToActiveAccount->myHistory.addToHistory(transactionType, transactionAmount, newTotal, date);
}