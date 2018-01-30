#include "savings.h"

Savings::Savings() : Accounts()
{}

void Savings::specifyFileType(string id, string fileName)
{
    pointerToActiveAccount = listOfOpenAccounts.getActiveAccount();
    pointerToActiveAccount->accountFileName = "S" + id + fileName + ".txt";
}

void Savings::displayAccounts()
{
    cout << endl << "Savings Account(s)" << endl;
    listOfOpenAccounts.displayNodes();
}

void Savings::accountOptionsMenu()
{
    pointerToActiveAccount = listOfOpenAccounts.getActiveAccount();
    
    do {
        menuInterface();

        switch(menuUserSelection)
        {
            case 1:
                depositFunds();
                break;
            case 2:
                mergeAccounts();
                break;
            case 3:
                transferFunds();
                break;
            case 4:
                pointerToActiveAccount->myHistory.displayHistory();
                break;
            case 5:
                deleteAccount();
                break;
            default:
                resetActiveAccount();
                break;
        }

        if (pointerToActiveAccount == NULL) menuUserSelection = 6;

    } while (menuUserSelection != 6);

    menuUserSelection = 0;
}

void Savings::menuInterface()
{
    displayActiveAccountDetails();
    displayMenuOptions();
    validateMenuInput(6);
}

void Savings::displayMenuOptions()
{
    cout << endl << "*** " << pointerToActiveAccount->accountName << " Options ***" << endl << endl;
    cout << "1. Deposit" << endl;
    cout << "2. Merge Accounts" << endl;
    cout << "3. Transfer Money" << endl;
    cout << "4. Display Account History" << endl;
    cout << "5. Delete Account" << endl;
    cout << "6. Back" << endl;
}

//cross account transfers need to be redone
void Savings::transferFunds()
{
    cout << endl << "In to which account type would you like to transfer funds?";
    menuUserSelection = inputErrorCatcher.chooseAccountType();

    if (menuUserSelection == 2) sameAccountTypeTransfer();
    else if (menuUserSelection == 1)
    {
        cout << "Cross transfer feature currently broken!" << endl;
    }
}
