//ATM MACHINE
//Hannah Mitchell
//CS M10B
//December 11th 2017

#include "checking.h"

//empty constructor
Checking::Checking() : Accounts()
{}

//sets file name
void Checking::specifyFileType(string id, string fileName)
{
    //pointer to selected account
    pointerToActiveAccount = listOfOpenAccounts.getActiveAccount();
    
    //create file name
    pointerToActiveAccount->accountFileName = "C" + id + fileName + ".txt";
}

//displays account header
void Checking::displayAccounts()
{
    //header before account names listed
    cout << endl << "Checking Account(s)" << endl;
    listOfOpenAccounts.displayNodes();
}

//displays account options menu and switch
void Checking::accountOptionsMenu()
{   
    //set to selected account
    pointerToActiveAccount = listOfOpenAccounts.getActiveAccount();
    
    do {
        //display current account details
        cout << endl << "Current Account: " << pointerToActiveAccount->accountName << endl;
        cout << "Account Funds: $" << pointerToActiveAccount->totalFunds << endl;

        //advanced options
        cout << endl << "*** " << pointerToActiveAccount->accountName << " Options ***" << endl << endl;
        cout << "1. Withdraw" << endl;
        cout << "2. Deposit" << endl;
        cout << "3. Merge Accounts" << endl;
        cout << "4. Transfer Money" << endl;
        cout << "5. Display Account History" << endl;
        cout << "6. Delete Account" << endl;
        cout << "7. Back" << endl;

        //validate input
        cin >> menuUserSelection;
        inputErrorCatcher.checkForValidUserInput(menuUserSelection, 1, 7);
        inputErrorCatcher.clearKeyboardBuffer();

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
                //activate transfer function in user.h
                if (crossTransfer == true) return;
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
        
        //if account is deleted or merged, exit this menu automatically
        if (pointerToActiveAccount == NULL) menuUserSelection = 7;

    } while (menuUserSelection != 7);

    //reset variable
    menuUserSelection = 0;
}

//withdraw money
void Checking::withdrawFunds()
{
    //set to selected account
    pointerToActiveAccount = listOfOpenAccounts.getActiveAccount();
    
    //formatting
    cout << fixed << setprecision(2);
    //ask for withdraw amount and subtract from total
    cout << endl << "Withdraw amount: ";
    cin >> withdrawOrDepositValue;
    inputErrorCatcher.checkForValidUserInput(withdrawOrDepositValue, 0.0, 1000000000.0);

    //make sure there isn't overdraft
    if (pointerToActiveAccount->totalFunds - withdrawOrDepositValue < 0)
        cout << endl << "You do not have sufficient funds!" << endl;
    else 
    {
        //if deposit is more than 0
        if (withdrawOrDepositValue > 0)
        {
            pointerToActiveAccount->totalFunds = pointerToActiveAccount->totalFunds -= withdrawOrDepositValue;
            //display withdraw amount and new total
            cout << "Successfully withdrew $" << withdrawOrDepositValue << endl;
            cout << "New " << pointerToActiveAccount->accountName << " total is $" << pointerToActiveAccount->totalFunds << endl;
            
            //send to history
            pointerToActiveAccount->myHistory.addToHistory("Withdrawal", withdrawOrDepositValue, pointerToActiveAccount->totalFunds, "NULL");
        }
    }
}

//verify if transfer is a checking or savings
void Checking::transferFunds()
{
    //choose an accounts type
    cout << endl << "In to which account type would you like to transfer funds?";
    menuUserSelection = inputErrorCatcher.chooseAccountType();

    //checking vs savings
    if (menuUserSelection == 1) sameAccountTypeTransfer();
    else if (menuUserSelection == 2) crossTransfer = true;
}