//ATM MACHINE
//Hannah Mitchell
//CS M10B
//December 11th 2017

#include "userMenu.h"

UserMenu::UserMenu()
{
    initializeClassVariables();
    collectNewUserInfo();
}

void UserMenu::initializeClassVariables()
{
    menuUserSelection = 0;
    crossAccountTypeTransfer = false;
    accountTypeDoesNotExist = false;
}

void UserMenu::collectNewUserInfo()
{
    cout << endl << "Thank you for choosing Hannah's Bank!" << endl << endl;
    
    requestUserName();
    requestUserPin();

    createUserFile();

    cout << endl << "Now we'll need to know some information about you!" << endl;

    requestFirstName();
    requestLastName();
    requestAge();

    mainMenu();
}

void UserMenu::requestUserName()
{
    cout << "Please enter a username: ";
    getline(cin, stringSetter); 

    inputErrorCatcher.checkForValidIDEntry(stringSetter);
    myInfo.setId(stringSetter);
}

void UserMenu::createUserFile()
{
    txtFileName = myInfo.getId() + ".txt";
    userInfoFile.open(txtFileName.c_str(), ios::out);
    userInfoFile.close();
}

void UserMenu::requestUserPin()
{
    cout << "Choose a 4 digit pin: ";
    getline(cin, stringSetter);
    validateUserPin();
}

void UserMenu::validateUserPin()
{
    inputErrorCatcher.checkForValidPinEntry(stringSetter);
    myInfo.setPin(stringSetter);
}

void UserMenu::requestFirstName()
{
    cout << "What is your first name? ";
    getline(cin, stringSetter);

    inputErrorCatcher.removeExtraWhiteSpaceFromString(stringSetter);
    myInfo.setFirstName(stringSetter);
}

void UserMenu::requestLastName()
{
    cout << "What is your last name? ";
    getline(cin, stringSetter);

    inputErrorCatcher.removeExtraWhiteSpaceFromString(stringSetter);
    myInfo.setLastName(stringSetter);
}

void UserMenu::requestAge()
{
    cout << "Please enter your age: ";
    cin >> intSetter;
    
    inputErrorCatcher.checkForValidUserInput(intSetter, 16, 125);
    myInfo.setAge(intSetter);
    inputErrorCatcher.clearKeyboardBuffer();
}



UserMenu::UserMenu(string userID, string userPin)
{
    initializeClassVariables();

    openUserFile(userID);
    readUserInfoFromFile();

    if (userPin != myInfo.getPin())
    {
        cout << "Incorrect Pin." << endl;
        userInfoFile.close();
        return;
    }

    readAccountNamesFromFile();
    userInfoFile.close();

    cout << endl << "Welcome Back " << myInfo.getFirstName() << "!" << endl;
    mainMenu();
}

void UserMenu::openUserFile(string id)
{
    txtFileName = id;
    userInfoFile.open(txtFileName.c_str(), ios::in);
}

void UserMenu::readUserInfoFromFile()
{
    userInfoFile >> stringSetter;
    myInfo.setPin(stringSetter);

    userInfoFile >> stringSetter;
    myInfo.setId(stringSetter);

    userInfoFile >> stringSetter;
    myInfo.setFirstName(stringSetter);

    userInfoFile >> stringSetter;
    myInfo.setLastName(stringSetter);

    userInfoFile >> intSetter;
    myInfo.setAge(intSetter);
}

void UserMenu::readAccountNamesFromFile()
{
    while (userInfoFile >> stringSetter) 
    {
        accountFileNames.push_back(stringSetter);
    }

    categorizeAccountNames();
}

void UserMenu::categorizeAccountNames()
{
    for (int i = 0; i < accountFileNames.size(); i++)
    {
        if (accountFileNames[i][0] == 'C')
            myChecking.downloadExistingAccounts(accountFileNames[i]);
        else if (accountFileNames[i][0] == 'S')
            mySavings.downloadExistingAccounts(accountFileNames[i]);
    }

    accountFileNames.clear();
}



UserMenu::~UserMenu()
{
    userInfoFile.open(txtFileName.c_str(), ios::out);

    writeUserInfoToFile();
    getAndWriteAccountFileNames();

    userInfoFile.close();
}

void UserMenu::writeUserInfoToFile()
{
    userInfoFile << myInfo.getPin() << endl;
    userInfoFile << myInfo.getId() << endl;
    userInfoFile << myInfo.getFirstName() << endl;
    userInfoFile << myInfo.getLastName() << endl;
    userInfoFile << myInfo.getAge() << endl;
}

void UserMenu::getAndWriteAccountFileNames()
{
    getCheckingAccountFileNames();
    writeAccountNamesToFile();

    getSavingsAccountFileNames();
    writeAccountNamesToFile();
}

void UserMenu::getCheckingAccountFileNames()
{
    accountFileNames = myChecking.getAccountFileNames();
}

void UserMenu::getSavingsAccountFileNames()
{
    accountFileNames = mySavings.getAccountFileNames();
}

void UserMenu::writeAccountNamesToFile()
{
    for (int i = 0; i < accountFileNames.size(); i++) 
        userInfoFile << accountFileNames[i] << endl;
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
    cout << endl << "Which account type would you like to access?";
    menuUserSelection = inputErrorCatcher.chooseAccountType();

    if (menuUserSelection == 1) 
    {
        selectCheckingAccount();
    }

    else if (menuUserSelection == 2) 
    {
        selectSavingsAccount();
    }

    crossAccountTypeTransfer = false;
}

void UserMenu::selectCheckingAccount()
{
    do {
        //convulated way of displaying and selecting checking accounts
        crossAccountTypeTransfer = myChecking.selectAccountForCrossTransfer("checking");

        //calls transfer between account types function
        if (crossAccountTypeTransfer == true) crossAccountTypeTransferHandler(true);

    } while (crossAccountTypeTransfer == true);
}

void UserMenu::selectSavingsAccount()
{
    do {
        //convulated way of displaying and selecting checking accounts
        crossAccountTypeTransfer = mySavings.selectAccountForCrossTransfer("savings");

        //calls transfer between account types function
        if (crossAccountTypeTransfer == true) crossAccountTypeTransferHandler(false);

    } while (crossAccountTypeTransfer == true);
}

void UserMenu::createAnAccountMenuOption()
{
    cout << endl << "Which type of account would you like to create?";
    menuUserSelection = inputErrorCatcher.chooseAccountType();

    if (menuUserSelection == 1) 
    {
        myChecking.createAccount(myInfo.getId());
    }

    else if (menuUserSelection == 2) 
    {
        mySavings.createAccount(myInfo.getId());
    }

}

void UserMenu::requestTotalBalanceMenuOption()
{
    cout << fixed << setprecision(2);

    cout << endl << "Your total balance for all accounts is: $" 
         << myChecking.getTotalMoneyForAllAccounts() + mySavings.getTotalMoneyForAllAccounts() 
         << endl;
}

void UserMenu::editUserInfoMenuOption()
{
    cout << myInfo;

    do {

        displayMenuEditOptions();
        validateUserInput(4);

        switch(menuUserSelection)
        {
            case 1:
                requestNewPin();
                break;
            case 2:
                requestNewFullName();
                break;
            case 3:
                requestNewAge();
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

void UserMenu::requestNewPin()
{
    cout << "Enter New Pin: ";
    getline(cin, stringSetter);
    
    validateUserPin();

    cout << endl << "New Pin set to " << myInfo.getId() << "!" << endl;
}

void UserMenu::requestNewFullName()
{
    requestNewFirstName();
    requestNewLastName();

    cout << endl << "New Name set to " << myInfo.getFirstName() << " " 
            << myInfo.getLastName() << "!" << endl;
}

void UserMenu::requestNewFirstName()
{
    cout << "Enter First Name: ";
    getline(cin, stringSetter);

    inputErrorCatcher.removeExtraWhiteSpaceFromString(stringSetter);
    myInfo.setFirstName(stringSetter); 
}

void UserMenu::requestNewLastName()
{
    cout << "Enter Last Name: ";
    getline(cin, stringSetter);

    inputErrorCatcher.removeExtraWhiteSpaceFromString(stringSetter);
    myInfo.setLastName(stringSetter);
}

void UserMenu::requestNewAge()
{
    cout << "Enter New Age: ";
    cin >> intSetter;

    inputErrorCatcher.checkForValidUserInput(intSetter, 16, 125);
    myInfo.setAge(intSetter);
    inputErrorCatcher.clearKeyboardBuffer();

    cout << endl << "New Age set to " << myInfo.getAge() << "!" << endl;
}

void UserMenu::crossAccountTypeTransferHandler(bool accountType)
{
    if (accountType == true) checkingTransfer();

    else if (accountType == false) savingsTransfer();

    if (accountTypeDoesNotExist) 
    {
        accountTypeDoesNotExist = !accountTypeDoesNotExist;
        return;
    }

    outputNewAccountTotals();
}

void UserMenu::checkingTransfer()
{
    checkingAccount = myChecking.callGetActiveAccount();

    myChecking.resetCrossTransfer();

    selectASavingsAccount();
    if (accountTypeDoesNotExist) return;

    getTransferAmountChecking();

    ammendAccountTotalsChecking();
    
    sendToHistory("Transfer Withdrawal", "Transfer Deposit");

    mySavings.resetActiveAccount();
}

void UserMenu::selectASavingsAccount()
{
    checkIfSavingsAccountExists();
    if (accountTypeDoesNotExist) return;

    mySavings.displayAccounts();
    mySavings.selectAccount();
    savingsAccount = mySavings.callGetActiveAccount();
}

void UserMenu::checkIfSavingsAccountExists()
{
    if (!mySavings.getHeadOfAccountList())
    {
        cout << endl << "You have not created a savings account yet!" << endl;
        accountTypeDoesNotExist = true;
    }
}

void UserMenu::getTransferAmountChecking()
{
    cout << "How much money would you like to transfer from " << checkingAccount->accountName
            << " to " << savingsAccount->accountName << "? ";
    cin >> transferAmount;
    inputErrorCatcher.checkForValidUserInput(transferAmount, 0.0, checkingAccount->totalFunds);
}

void UserMenu::ammendAccountTotalsChecking()
{
    checkingAccount->totalFunds -= transferAmount;
    savingsAccount->totalFunds += transferAmount;
}

void UserMenu::sendToHistory(string checkingAction, string savingsAction)
{
    myChecking.sendToHistory(checkingAction, transferAmount, checkingAccount->totalFunds, "NULL");
    mySavings.sendToHistory(savingsAction, transferAmount, savingsAccount->totalFunds, "NULL");
}

void UserMenu::savingsTransfer()
{
    savingsAccount = mySavings.callGetActiveAccount();

    mySavings.resetCrossTransfer();

    selectACheckingAccount();
    if (accountTypeDoesNotExist) return;

    getTransferAmountSavings();
    
    ammendAccountTotalsSavings();

    sendToHistory("Transfer Deposit", "Transfer Withdrawal");

    myChecking.resetActiveAccount();
}

void UserMenu::selectACheckingAccount()
{
    checkIfCheckingAccountExists();
    if (accountTypeDoesNotExist) return;

    myChecking.displayAccounts();
    myChecking.selectAccount();
    checkingAccount = myChecking.callGetActiveAccount();
}

void UserMenu::checkIfCheckingAccountExists()
{
    if (!myChecking.getHeadOfAccountList())
    {
        cout << endl << "You have not created a checking account yet!" << endl;
        accountTypeDoesNotExist = true;
    }
}

void UserMenu::getTransferAmountSavings()
{
    cout << "How much money would you like to transfer from " << savingsAccount->accountName
            << " to " << checkingAccount->accountName << "? ";
    cin >> transferAmount;
    inputErrorCatcher.checkForValidUserInput(transferAmount, 0.0, savingsAccount->totalFunds);
}

void UserMenu::ammendAccountTotalsSavings()
{
    savingsAccount->totalFunds -= transferAmount;
    checkingAccount->totalFunds += transferAmount;
}

void UserMenu::outputNewAccountTotals()
{
    cout << endl << "Successfully transfered $" << transferAmount << "!" << endl;
    cout << "New " << checkingAccount->accountName << " total is $" << checkingAccount->totalFunds << endl;
    cout << "New " << savingsAccount->accountName << " total is $" << savingsAccount->totalFunds << endl;
}


ostream &operator << (ostream &os, UserInfo &user)
{
    os << endl 
       << "User ID: " << user.getId() << endl 
       << "User Pin: " << user.getPin() << endl
       << "Name: " << user.getFirstName() << " " << user.getLastName() << endl 
       << "Age: " << user.getAge() << endl;
    return os;
}