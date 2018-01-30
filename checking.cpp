#include "checking.h"

Checking::Checking() : Accounts()
{}

void Checking::specifyFileType(string id, string fileName)
{
    pointerToActiveAccount = listOfOpenAccounts.getActiveAccount();
    pointerToActiveAccount->accountFileName = "C" + id + fileName + ".txt";
}

void Checking::displayAccounts()
{
    cout << endl << "Checking Account(s)" << endl;
    listOfOpenAccounts.displayNodes();
}

void Checking::accountOptionsMenu()
{   
    pointerToActiveAccount = listOfOpenAccounts.getActiveAccount();
    
    do {
        menuInterface();

        switch(menuUserSelection)
        {
            case 1:
                withdrawFunds();
                break;
            case 2:
                depositFunds();
                break;
            case 3:
                mergeAccounts();
                break;
            case 4:
                transferFunds();
                break;
            case 5:
                pointerToActiveAccount->myHistory.displayHistory();
                break;
            case 6:
                deleteAccount();
            default:
                resetActiveAccount();
                break;
        }
        
        if (pointerToActiveAccount == NULL) menuUserSelection = 7;

    } while (menuUserSelection != 7);

    menuUserSelection = 0;
}

void Checking::menuInterface()
{
    displayActiveAccountDetails();
    displayMenuOptions();
    validateMenuInput(7);
}

void Checking::displayMenuOptions()
{
    cout << endl << "*** " << pointerToActiveAccount->accountName << " Options ***" << endl << endl;
    cout << "1. Withdraw" << endl;
    cout << "2. Deposit" << endl;
    cout << "3. Merge Accounts" << endl;
    cout << "4. Transfer Money" << endl;
    cout << "5. Display Account History" << endl;
    cout << "6. Delete Account" << endl;
    cout << "7. Back" << endl;
}

void Checking::withdrawFunds()
{
    pointerToActiveAccount = listOfOpenAccounts.getActiveAccount();
    
    requestWithdrawalAmount();
    if (checkForOverdraft()) return;
    confirmedWithdrawal();
}

void Checking::requestWithdrawalAmount()
{
    cout << endl << "Withdraw amount: ";
    cin >> withdrawOrDepositValue;
    inputErrorCatcher.checkForValidUserInput(withdrawOrDepositValue, 0.0, 1000000000.0);
}

bool Checking::checkForOverdraft()
{
    if (pointerToActiveAccount->totalFunds - withdrawOrDepositValue < 0)
    {
        cout << endl << "You do not have sufficient funds!" << endl;
        return true;
    }
    return false;
}

void Checking::confirmedWithdrawal()
{
    if (withdrawOrDepositValue > 0)
    {
        pointerToActiveAccount->totalFunds = pointerToActiveAccount->totalFunds -= withdrawOrDepositValue;
        displayNewTotals();
        
        sendToHistory("Withdrawal", withdrawOrDepositValue, pointerToActiveAccount->totalFunds, "NULL");
    }
}

void Checking::displayNewTotals()
{
    cout << fixed << setprecision(2);
    cout << "Successfully withdrew $" << withdrawOrDepositValue << endl;
    cout << "New " << pointerToActiveAccount->accountName << " total is $" << pointerToActiveAccount->totalFunds << endl;
}

//cross account trasnfers need to be redone
void Checking::transferFunds()
{
    cout << endl << "In to which account type would you like to transfer funds?";
    menuUserSelection = inputErrorCatcher.chooseAccountType();

    if (menuUserSelection == 1) sameAccountTypeTransfer();
    else if (menuUserSelection == 2)
    {
        cout << "Cross transfer feature currently broken!" << endl;
    }
}