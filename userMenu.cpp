#include "userMenu.h"

UserMenu::UserMenu()
{
    initializeClassVariables();
    collectNewUserInfo();
}

void UserMenu::initializeClassVariables()
{
    menuUserSelection = 0;
    accountTypeDoesNotExist = false;
}

void UserMenu::collectNewUserInfo()
{
    cout << endl << "Thank you for choosing Hannah's Bank!" << endl << endl;
    
    myInfo.requestUserName();
    myInfo.requestUserPin();

    myInfo.createUserFile();

    cout << endl << "Now we'll need to know some information about you!" << endl;

    myInfo.requestFirstName();
    myInfo.requestLastName();
    myInfo.requestAge();

    //myInfo.setAccountPointers(myChecking, mySavings);

    mainMenu();
}

UserMenu::UserMenu(string userID, string userPin)
{
    initializeClassVariables();

    if (!myInfo.readUserInfoFromFile(userID, userPin)) return;

    //myInfo.setAccountPointers(myChecking, mySavings);

    mainMenu();
}

UserMenu::~UserMenu()
{
    myInfo.writeUserInfoToFile();
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
    /*cout << endl << "Which account type would you like to access?";
    menuUserSelection = inputErrorCatcher.chooseAccountType();

    if (menuUserSelection == 1) 
    {
        myChecking.accessAccounts("checking");
    }

    else if (menuUserSelection == 2) 
    {
        mySavings.accessAccounts("savings");
    }*/
}

void UserMenu::createAnAccountMenuOption()
{
    /*cout << endl << "Which type of account would you like to create?";
    menuUserSelection = inputErrorCatcher.chooseAccountType();

    if (menuUserSelection == 1) 
    {
        myChecking.createAccount(myInfo.getId());
    }

    else if (menuUserSelection == 2) 
    {
        mySavings.createAccount(myInfo.getId());
    }*/

}

void UserMenu::requestTotalBalanceMenuOption()
{
    /*cout << fixed << setprecision(2);

    cout << endl << "Your total balance for all accounts is: $" 
         << myChecking.getTotalMoneyForAllAccounts() + mySavings.getTotalMoneyForAllAccounts() 
         << endl;*/
}

void UserMenu::editUserInfoMenuOption()
{
    myInfo.displayUserInfo();

    do {

        displayMenuEditOptions();
        validateUserInput(4);

        switch(menuUserSelection)
        {
            case 1:
                myInfo.requestUserPin();
                break;
            case 2:
                myInfo.requestFullName();
                break;
            case 3:
                myInfo.requestAge();
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
    cout << "1. Pin" << endl;
    cout << "2. Name" << endl;
    cout << "3. Age" << endl;
    cout << "4. Back" << endl;
}