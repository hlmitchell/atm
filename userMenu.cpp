#include "userMenu.h"

UserMenu::UserMenu()
{
    menuUserSelection = 0;
}

UserMenu::UserMenu(AccountTree &myTree, UserInfo &myIn)
{
    myAccounts = &myTree;
    myInfo = &myIn;

    mainMenu();
}

UserMenu::~UserMenu()
{
    myAccounts = NULL;
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
    myAccounts->selectAnAccount();
}

void UserMenu::createAnAccountMenuOption()
{
    myAccounts->createAnAccount(myInfo->getId());
}

void UserMenu::requestTotalBalanceMenuOption()
{
    myAccounts->requestTotalBalance();
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