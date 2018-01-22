//ATM MACHINE
//Hannah Mitchell
//CS M10B
//December 11th 2017

#include "accounts.h"

Accounts::Accounts()
{
    activeAccountName = "";
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

void Accounts::resetCrossTransfer()
{
    crossTransfer = false;
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

bool Accounts::getCrossTransfer()
{
    return crossTransfer;
}

//bad code
bool Accounts::selectAccountForCrossTransfer(string accountType)
{
    if (!getHeadOfAccountList()) 
    {
        cout << endl << "You have not created a " << accountType <<  " account yet!" << endl;
        return false;
    }
    //if returning from cross transfer go straight to menu
    else if (listOfOpenAccounts.getActiveAccount())
    {
        accountOptionsMenu();
        return false;
    }
    else
    {   
        displayAccounts();       
        selectAccount();

        //indicates transfer across account types
        bool crossAccountTransfer;

        //display further menu
        accountOptionsMenu();
                
        //check for transfer selection in account options menu
        crossAccountTransfer = getCrossTransfer();
        if (crossAccountTransfer == true) return true;
        else return false;
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






//selects an account to edit 
void Accounts::selectAccount()
{
    //clear input
    cin.ignore();
    //while inputed account name doesn't exist, continue to prompt 
    do {
        //get account name
        cout << endl << "Enter the name of the account you wish to access: ";
        getline(cin, activeAccountName);
        //find account address
        pointerToActiveAccount = listOfOpenAccounts.findNode(activeAccountName);
        //if address is NULL, account name was not valid
        if (pointerToActiveAccount == NULL)
            cout << "Not an available account name!" << endl;
    } while (pointerToActiveAccount == NULL);

    //set selected account
    listOfOpenAccounts.setActiveAccount(pointerToActiveAccount);
}

//deletes an account
void Accounts::deleteAccount()
{
    //set to selected account
    pointerToActiveAccount = listOfOpenAccounts.getActiveAccount();
    
    //if total funds aren't 0, do not delete account
    if (pointerToActiveAccount->totalFunds != 0)
    {
        cout << endl << "You must empty the account funds first!" << endl;
        return;
    }

    //confirm deletion
    cout << endl << "Delete account " << pointerToActiveAccount->accountName << " (Y/N)? ";
    cin >> yesOrNo;
    inputErrorCatcher.yesOrNoValidator(yesOrNo); //error check

    //if yes
    if (yesOrNo == 'Y')
    {
        cout << "Account " << pointerToActiveAccount->accountName << " has been deleted!" << endl;
        //delete node and set selected account to NULL
        listOfOpenAccounts.deleteNode(pointerToActiveAccount->accountName);
        resetActiveAccount();
    }
}

//deposit money
void Accounts::depositFunds()
{
    //set to selected account
    pointerToActiveAccount = listOfOpenAccounts.getActiveAccount();
    
    //enter deposit amount
    cout << endl << "Deposit amount: ";
    cin >> withdrawOrDepositValue;
    inputErrorCatcher.checkForValidUserInput(withdrawOrDepositValue, 0.0, 1000000000.0);

    //if deposit is more than 0
    if (withdrawOrDepositValue > 0)
    {
        //add to total
        pointerToActiveAccount->totalFunds += withdrawOrDepositValue;
        //display deposit amount and new total
        cout << "Successfully deposited $" << withdrawOrDepositValue << endl;
        cout << "New " << pointerToActiveAccount->accountName << " total is $" << pointerToActiveAccount->totalFunds << endl;

        //send to history
        pointerToActiveAccount->myHistory.addToHistory("Deposit", withdrawOrDepositValue, pointerToActiveAccount->totalFunds, "NULL");
    }
}

//merge two like accounts
void Accounts::mergeAccounts()
{
    //set to head
    pointerToActiveAccount = listOfOpenAccounts.getListHead();

    //merger account pointer and account name
    accountNode *mergerAccount;
    string mergerAccountName;

    //check if other accounts exist for merger
    if (pointerToActiveAccount->next == NULL)
    {
        cout << endl << "There are no other accounts of the same type!" << endl;
        return;
    }
    else displayAccounts();

    //set to selected account
    pointerToActiveAccount = listOfOpenAccounts.getActiveAccount();

    //while inputed account name doesn't exist, continue to prompt 
    do {
        //get account name
        cout << endl << "With which account would you like to merge " 
        << pointerToActiveAccount->accountName << "? ";
        getline(cin, mergerAccountName);
        //find account address
        mergerAccount = listOfOpenAccounts.findNode(mergerAccountName);
        //if address is NULL, account name was not valid
        if (mergerAccount == NULL || mergerAccount->accountName == pointerToActiveAccount->accountName)
        {
            cout << "Not an available account name!" << endl;
            mergerAccount = NULL;
        }
    } while (mergerAccount == NULL);

    //verify with user
    cout << "Are you sure you want to merge " << pointerToActiveAccount->accountName
         << " into " << mergerAccount->accountName << " (Y/N)? ";
    cin >> yesOrNo;
    inputErrorCatcher.yesOrNoValidator(yesOrNo);

    //delete selected account and transfer funds to merger account
    if (yesOrNo == 'Y')
    {
        //transfer money to merger accounts
        mergerAccount->totalFunds += pointerToActiveAccount->totalFunds;
        cout << "Merge Successful!" << endl;

        //send to history
        mergerAccount->myHistory.addToHistory("Merger Deposit", pointerToActiveAccount->totalFunds, mergerAccount->totalFunds, "NULL");

        //delete account
        listOfOpenAccounts.deleteNode(pointerToActiveAccount->accountName);
        resetActiveAccount();
    }
}

//transferring money between like accounts
void Accounts::sameAccountTypeTransfer()
{
    //set to head
    pointerToActiveAccount = listOfOpenAccounts.getListHead();
    
    //pointer for checking transfer
    accountNode *transferPtr;
    string transferAccountName;

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
        transferPtr = listOfOpenAccounts.findNode(transferAccountName);
        //if address is NULL, account name was not valid
        if (transferPtr == NULL || transferPtr->accountName == pointerToActiveAccount->accountName)
        {
            cout << "Not an available account name!" << endl;
            transferPtr = NULL;
        }
    } while (transferPtr == NULL);

    //ask for transfer amount
    cout << "How much money would you like to transfer from " << pointerToActiveAccount->accountName
         << " to " << transferPtr->accountName << "? ";
    cin >> withdrawOrDepositValue;
    inputErrorCatcher.checkForValidUserInput(withdrawOrDepositValue, 0.0, pointerToActiveAccount->totalFunds);

    //if transfer is not 0
    if (withdrawOrDepositValue > 0)
    {  
        //ammend account totals
        pointerToActiveAccount->totalFunds -= withdrawOrDepositValue;
        transferPtr->totalFunds += withdrawOrDepositValue;
 
        //output success message and new totals for accounts
        cout << endl << "Successfully transfered $" << withdrawOrDepositValue << "!" << endl;
        cout << "New " << pointerToActiveAccount->accountName << " total is $" << pointerToActiveAccount->totalFunds << endl;
        cout << "New " << transferPtr->accountName << " total is $" << transferPtr->totalFunds << endl;

        //send to histories
        pointerToActiveAccount->myHistory.addToHistory("Transfer Withdrawal", withdrawOrDepositValue, pointerToActiveAccount->totalFunds, "NULL");
        transferPtr->myHistory.addToHistory("Transfer Deposit", withdrawOrDepositValue, transferPtr->totalFunds, "NULL");
    }

}

//sends to history from transfer handler of user class
void Accounts::sendToHistory(string transactionType, double transactionAmount, double newTotal, string date)
{
    //set to selected account
    pointerToActiveAccount = listOfOpenAccounts.getActiveAccount();
    
    //send to history
    pointerToActiveAccount->myHistory.addToHistory(transactionType, transactionAmount, newTotal, date);
}