#include "accounts.h"

Accounts::Accounts()
{
    activeAccountName = "";
    secondAccountName = "";
    menuUserSelection = 0;
    withdrawOrDepositValue = 0;
}

Accounts::~Accounts()
{
    pointerToActiveAccount = NULL;
    secondAccount = NULL;
}

void Accounts::downloadExistingAccounts(string accountName)
{
    listOfOpenAccounts.downloadNode(accountName);
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

void Accounts::accessAccounts(string accountType)
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

void Accounts::displayActiveAccountDetails()
{
    cout << endl << "Current Account: " << pointerToActiveAccount->accountName << endl;
    cout << "Account Funds: $" << pointerToActiveAccount->totalFunds << endl;
}

void Accounts::validateMenuInput(int max)
{
    cin >> menuUserSelection;
    inputErrorCatcher.checkForValidUserInput(menuUserSelection, 1, max);
    inputErrorCatcher.clearKeyboardBuffer();
}

void Accounts::createAccount(string id)
{ 
    nameAccount();
    setTextFileName(id);

    pointerToActiveAccount = listOfOpenAccounts.getActiveAccount();

    makeInitialDeposit();

    confirmationOfNewAccountMessage();
    
    sendToHistory("Open Deposit", pointerToActiveAccount->totalFunds, pointerToActiveAccount->totalFunds);

    resetActiveAccount();
}

void Accounts::nameAccount()
{
    string accountName;        
    
    cout << endl << "What would you like to name this account? ";
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

        pointerToActiveAccount->myHistory.addToHistory("Deposit", withdrawOrDepositValue, pointerToActiveAccount->totalFunds);
    }
}

void Accounts::mergeAccounts()
{
    if (!checkIfOtherAccountsExist()) return;

    pointerToActiveAccount = listOfOpenAccounts.getActiveAccount();

    requestSecondAccountName();
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

void Accounts::requestSecondAccountName()
{
    do {
        cout << endl << "Enter the name of the account you wish to access: ";
        getline(cin, secondAccountName);

        secondAccount = listOfOpenAccounts.findNode(secondAccountName);

        if (secondAccount == NULL || secondAccount->accountName == pointerToActiveAccount->accountName)
        {
            cout << "Not an available account name!" << endl;
            secondAccount = NULL;
        }

    } while (secondAccount == NULL);
}

void Accounts::verifyAccountMerge()
{
    cout << "Are you sure you want to merge " << pointerToActiveAccount->accountName
         << " into " << secondAccount->accountName << " (Y/N)? ";
    cin >> yesOrNo;
    inputErrorCatcher.yesOrNoValidator(yesOrNo);
}

void Accounts::confirmedMerge()
{
    secondAccount->totalFunds += pointerToActiveAccount->totalFunds;
    cout << "Merge Successful!" << endl;

    secondAccount->myHistory.addToHistory("Merger Deposit", pointerToActiveAccount->totalFunds, secondAccount->totalFunds);

    confirmedDeletion();
}

void Accounts::sameAccountTypeTransfer()
{
    if (!checkIfOtherAccountsExist()) return;

    pointerToActiveAccount = listOfOpenAccounts.getActiveAccount();

    requestSecondAccountName();         

    requestTransferAmount();

    confirmedTransfer();
}

void Accounts::chooseAccountType()
{
    cout << endl << endl;
    cout << "1. Checking" << endl;
    cout << "2. Savings" << endl;
    cout << "3. Back" << endl;

    cin >> menuUserSelection;
    inputErrorCatcher.checkForValidUserInput(menuUserSelection, 1, 3);
    inputErrorCatcher.clearKeyboardBuffer();
}

void Accounts::requestTransferAmount()
{
    cout << "How much money would you like to transfer from " << pointerToActiveAccount->accountName
         << " to " << secondAccount->accountName << "? ";
    cin >> withdrawOrDepositValue;
    inputErrorCatcher.checkForValidUserInput(withdrawOrDepositValue, 0.0, pointerToActiveAccount->totalFunds);
}

void Accounts::confirmedTransfer()
{
    if (withdrawOrDepositValue > 0)
    {  
        ammendAccountTotals();
        transferSuccessMessage();
        
        pointerToActiveAccount->myHistory.addToHistory("Transfer Withdrawal", withdrawOrDepositValue, pointerToActiveAccount->totalFunds);
        secondAccount->myHistory.addToHistory("Transfer Deposit", withdrawOrDepositValue, secondAccount->totalFunds);
    }
}

void Accounts::ammendAccountTotals()
{
    pointerToActiveAccount->totalFunds -= withdrawOrDepositValue;
    secondAccount->totalFunds += withdrawOrDepositValue;
}

void Accounts::transferSuccessMessage()
{
    cout << endl << "Successfully transfered $" << withdrawOrDepositValue << "!" << endl;
    cout << "New " << pointerToActiveAccount->accountName << " total is $" << pointerToActiveAccount->totalFunds << endl;
    cout << "New " << secondAccount->accountName << " total is $" << secondAccount->totalFunds << endl;
}

void Accounts::sendToHistory(string transactionType, double transactionAmount, double newTotal)
{
    pointerToActiveAccount = listOfOpenAccounts.getActiveAccount();
    pointerToActiveAccount->myHistory.addToHistory(transactionType, transactionAmount, newTotal);
}