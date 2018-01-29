//ATM MACHINE
//Hannah Mitchell
//CS M10B
//December 11th 2017

#include "savings.h"

//empty constructor
Savings::Savings() : Accounts()
{}

//sets file name
void Savings::specifyFileType(string id, string fileName)
{
    //pointer to selected account
    pointerToActiveAccount = listOfOpenAccounts.getActiveAccount();
    
    //create file name
    pointerToActiveAccount->accountFileName = "S" + id + fileName + ".txt";
}

//displays account header
void Savings::displayAccounts()
{
    cout << endl << "Savings Account(s)" << endl;
    listOfOpenAccounts.displayNodes();
}

//displays savings menu and switch
void Savings::accountOptionsMenu()
{
    //set to selected account
    pointerToActiveAccount = listOfOpenAccounts.getActiveAccount();
    
    do {
        cout << endl << "Current Account: " << pointerToActiveAccount->accountName << endl;
        cout << "Account Funds: $" << pointerToActiveAccount->totalFunds << endl;

        //advanced options
        cout << endl << "*** " << pointerToActiveAccount->accountName << " Options ***" << endl << endl;
        cout << "1. Deposit" << endl;
        cout << "2. Merge Accounts" << endl;
        cout << "3. Transfer Money" << endl;
        cout << "4. Display Account History" << endl;
        cout << "5. Delete Account" << endl;
        cout << "6. Back" << endl;

        //validate input
        cin >> menuUserSelection;
        inputErrorCatcher.checkForValidUserInput(menuUserSelection, 1, 6);
        inputErrorCatcher.clearKeyboardBuffer();

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

        //if account is deleted or merged, exit this menu automatically
        if (pointerToActiveAccount == NULL) menuUserSelection = 6;

    } while (menuUserSelection != 6);

    //reset variable
    menuUserSelection = 0;
}

//validates if transfer is savings or savings
void Savings::transferFunds()
{
    //choose an accounts type
    cout << endl << "In to which account type would you like to transfer funds?";
    menuUserSelection = inputErrorCatcher.chooseAccountType();

    //checking vs savings
    if (menuUserSelection == 2) sameAccountTypeTransfer();
    else if (menuUserSelection == 1)
    {
        cout << "Cross transfer feature currently broken!" << endl;
    }
}
