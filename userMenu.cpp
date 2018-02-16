#include "userMenu.h"

const string UserMenu::CHECKING = "checking";
const string UserMenu::SAVINGS = "savings";

UserMenu::UserMenu()
{
    menuUserSelection = 0;
}

UserMenu::UserMenu(Checking &myCheck, Savings &mySave, UserInfo &myIn)
{
    myChecking = &myCheck;
    mySavings = &mySave;
    myInfo = &myIn;

    mainMenu();
}

UserMenu::~UserMenu()
{
    myChecking = NULL;
    mySavings = NULL;
    myInfo = NULL;
}

void UserMenu::mainMenu()
{
    do {
        
        displayMenuOptions();
        validateUserInput(5);

        switch(menuUserSelection)
        {
            case 1:
                selectAnAccountMenuOption();
                break;
            case 2:
                createAnAccountMenuOption();
                break;
            case 3:
                editUserInfoMenuOption();
                break;
            case 4:
                requestTotalBalanceMenuOption();
            default:
                break;
        }
    } while (menuUserSelection != 5);

    menuUserSelection = 0;
}

void UserMenu::displayMenuOptions()
{
    cout << endl << "*** Main Menu ***" << endl << endl;
    cout << "1. Select an Account" << endl;
    cout << "2. Create an Account" << endl;
    cout << "3. Edit User Information" << endl;
    cout << "4. Request Total Balance" << endl;
    cout << "5. Log Out" << endl;
}

void UserMenu::validateUserInput(int upperBounds)
{
    cin >> menuUserSelection;
    inputErrorCatcher.checkForValidUserInput(menuUserSelection, 1, upperBounds);
    inputErrorCatcher.clearKeyboardBuffer();
}

void UserMenu::selectAnAccountMenuOption()
{
    chooseAccountType();

    if (menuUserSelection == 1) 
    {
        myChecking->accessAccounts(CHECKING);
    }

    else if (menuUserSelection == 2) 
    {
        mySavings->accessAccounts(SAVINGS);
    }
}

void UserMenu::createAnAccountMenuOption()
{
    chooseAccountType();

    if (menuUserSelection == 1) 
    {
        myChecking->createAccount(myInfo->getId());
    }

    else if (menuUserSelection == 2) 
    {
        mySavings->createAccount(myInfo->getId());
    }
}

void UserMenu::chooseAccountType()
{   
    displayAccountOptions();
    validateUserInput(3);
}

void UserMenu::displayAccountOptions()
{
    cout << endl << "Which type of account would you like to create?";
    cout << endl << endl;
    cout << "1. Checking" << endl;
    cout << "2. Savings" << endl;
    cout << "3. Back" << endl;
}

void UserMenu::requestTotalBalanceMenuOption()
{
    cout << fixed << setprecision(2);

    cout << endl << "Your total balance for all accounts is: $" 
         << myChecking->getTotalMoneyForAllAccounts() 
         << endl;
}

void UserMenu::editUserInfoMenuOption()
{
    do {

        myInfo->displayUserInfo();
        displayMenuEditOptions();
        validateUserInput(4);

        switch(menuUserSelection)
        {
            case 1:
                myInfo->requestUserPin();
                break;
            case 2:
                myInfo->requestFirstName();
                myInfo->requestLastName();
                break;
            case 3:
                myInfo->requestAge();
                break;
            default:
                break;
        }
    
    } while (menuUserSelection != 4);

    menuUserSelection = 0;
}

void UserMenu::displayMenuEditOptions()
{
    cout << endl << "Which of the following would you like to edit: " << endl;
    cout << endl;
    cout << "1. Pin" << endl;
    cout << "2. Name" << endl;
    cout << "3. Age" << endl;
    cout << "4. Back" << endl;
}