//ATM MACHINE
//Hannah Mitchell
//CS M10B
//December 11th 2017

#include "userMenu.h"

//Gathers user information for a new user
UserMenu::UserMenu()
{
    //set variables
    menuUserSelection = 0;
    crossAccountTypeTransfer = false;
    
    //temp vars for passing input to class userInfo
    string tempStr;
    int tempInt;

    //collect basic information from user
    cout << endl << "Thank you for choosing Hannah's Bank!" << endl << endl;
    cout << "Please enter a username: ";
    getline(cin, tempStr);
    //check if username already exists
    inputErrorCatcher.checkForValidIDEntry(tempStr);
    myInfo.setId(tempStr);

    //Create file
    txtFileName = myInfo.getId() + ".txt";
    userInfoFile.open(txtFileName.c_str(), ios::out);
    userInfoFile.close();
    
    //get pin
    cout << "Choose a 4 digit pin: ";
    getline(cin, tempStr);
    //check for valid input for pin
    inputErrorCatcher.checkForValidPinEntry(tempStr);
    myInfo.setPin(tempStr);

    //get name and check for errors
    cout << endl << "Now we'll need to know some information about you!" << endl;
    cout << "What is your first name? ";
    getline(cin, tempStr);
    inputErrorCatcher.removeExtraWhiteSpaceFromString(tempStr);
    myInfo.setFirst(tempStr);
    cout << "What is your last name? ";
    getline(cin, tempStr);
    inputErrorCatcher.removeExtraWhiteSpaceFromString(tempStr);
    myInfo.setLast(tempStr);

    //get age
    cout << "Please enter your age: ";
    cin >> tempInt;
    //check for valid input for age
    inputErrorCatcher.boundsCheck(tempInt, 16, 125);
    myInfo.setAge(tempInt);
    inputErrorCatcher.clearKeyboardBuffer();

    displayMainMenu();
}

//uploads user information from a previous user
UserMenu::UserMenu(string userID, string userPin)
{
    //set variables
    menuUserSelection = 0;
    crossAccountTypeTransfer = false;

    //temp vars for reading data
    string tempStr;
    int tempInt;
    
    //open file to extract user info
    txtFileName = userID;
    userInfoFile.open(txtFileName.c_str(), ios::in);

    //read user pin from file and send to user info
    userInfoFile >> tempStr;
    myInfo.setPin(tempStr);
    userInfoFile >> tempStr;
    myInfo.setId(tempStr);
    userInfoFile >> tempStr;
    myInfo.setFirst(tempStr);
    userInfoFile >> tempStr;
    myInfo.setLast(tempStr);
    userInfoFile >> tempInt;
    myInfo.setAge(tempInt);

    //if pin is incorrect, return to login screen
    if (userPin != myInfo.getPin())
    {
        cout << "Incorrect Pin." << endl;
        userInfoFile.close();
        return;
    }

    //read out file names and store them in vector
    string vecTemp;
    while (userInfoFile >> vecTemp) accountFileNames.push_back(vecTemp);

    //send account names to correct account class type
    for (int i = 0; i < accountFileNames.size(); i++)
    {
        if (accountFileNames[i][0] == 'C')
            myChecking.setAccountFileNames(accountFileNames[i]);
        else mySavings.setAccountFileNames(accountFileNames[i]);
    }

    //welcome message and main menu
    userInfoFile.close();
    cout << endl << "Welcome Back " << myInfo.getFirst() << "!" << endl;
    displayMainMenu();
}

//uploads user contents to file
UserMenu::~UserMenu()
{
    //open file
    userInfoFile.open(txtFileName.c_str(), ios::out);
    //write to file
    userInfoFile << myInfo.getPin() << endl;
    userInfoFile << myInfo.getId() << endl;
    userInfoFile << myInfo.getFirst() << endl;
    userInfoFile << myInfo.getLast() << endl;
    userInfoFile << myInfo.getAge() << endl;

    //delete file names in vector
    accountFileNames.clear();

    //temp vector for holding file names
    vector<string> tempAccountNamesHolder;

    //reaquire checking file names and fill vector
    tempAccountNamesHolder = myChecking.getAccountFileNames();
    for (int i = 0; i < tempAccountNamesHolder.size(); i++) accountFileNames.push_back(tempAccountNamesHolder[i]);
    //reaquire savings file names and fill vector
    tempAccountNamesHolder = mySavings.getAccountFileNames();
    for (int i = 0; i < tempAccountNamesHolder.size(); i++) accountFileNames.push_back(tempAccountNamesHolder[i]);

    //add file names to user info file
    for (int i = 0; i < accountFileNames.size(); i++) userInfoFile << accountFileNames[i] << endl;

    //close
    userInfoFile.close();
}

//display main menu and switch
void UserMenu::displayMainMenu()
{
    do {
        //main menu
        cout << endl << "*** Main Menu ***" << endl << endl;
        cout << "1. Select an Account" << endl;
        cout << "2. Create an Account" << endl;
        cout << "3. Edit User Information" << endl;
        cout << "4. Request Total Balance" << endl;
        cout << "5. Log Out" << endl;

        //validate input
        cin >> menuUserSelection;
        inputErrorCatcher.boundsCheck(menuUserSelection, 1, 5);
        inputErrorCatcher.clearKeyboardBuffer();

        switch(menuUserSelection)
        {
            case 1:
                //Menu requesting checking or savings account
                cout << endl << "Which account type would you like to access?";
                menuUserSelection = inputErrorCatcher.chooseAccountType();
                //check for existing checking accounts
                if (menuUserSelection == 1)
                {
                    do {
                        crossAccountTypeTransfer = myChecking.selectAnAccount("checking");

                        //calls transfer between account types function
                        if (crossAccountTypeTransfer == true) crossAccountTypeTransferHandler(true);
                    } while (crossAccountTypeTransfer == true);
                }

                //check for existing savings accounts
                else if (menuUserSelection == 2)
                {
                    do {
                        crossAccountTypeTransfer = mySavings.selectAnAccount("savings");

                        //calls transfer between account types function
                        if (crossAccountTypeTransfer == true) crossAccountTypeTransferHandler(false); 
                    } while (crossAccountTypeTransfer == true);                 
                }
                //reset transfer variable
                crossAccountTypeTransfer = false;

                break;
            case 2:
                //Menu requesting checking or savings account
                cout << endl << "Which type of account would you like to create?";
                menuUserSelection = inputErrorCatcher.chooseAccountType();

                //create node for checking
                if (menuUserSelection == 1) myChecking.createAccount(myInfo.getId());
                //create node for savings
                else if (menuUserSelection == 2) mySavings.createAccount(myInfo.getId());

                break;
            case 3:
                editUserInfo();
                break;
            case 4:
                //formatting
                cout << fixed << setprecision(2);
                //display total balance across acounts
                cout << endl << "Your total balance for all accounts is: $" 
                     << myChecking.getTotals() + mySavings.getTotals() << endl;
            default:
                break;
        }
    } while (menuUserSelection != 5);

    //reset variable
    menuUserSelection = 0;
}

//edits user information
void UserMenu::editUserInfo()
{
    //output original file info
    cout << myInfo;

    //temp vars for input
    string tempStr;
    int tempInt;

    //menu for ammending user information
    do {
        //menu
        cout << endl << "Which of the following would you like to edit: " << endl;
        cout << "1. Pin" << endl;
        cout << "2. Name" << endl;
        cout << "3. Age" << endl;
        cout << "4. Back" << endl;

        //check input selection
        cin >> menuUserSelection;
        inputErrorCatcher.boundsCheck(menuUserSelection, 1, 4);
        inputErrorCatcher.clearKeyboardBuffer();

        switch(menuUserSelection)
        {
            case 1:
                //request and store new pin
                cout << "Enter New Pin: ";
                getline(cin, tempStr);
                inputErrorCatcher.checkForValidPinEntry(tempStr);
                myInfo.setPin(tempStr);
                cout << endl << "New Pin set to " << myInfo.getId() << "!" << endl;
                break;
            case 2:
                //request and store new name
                cout << "Enter First Name: ";
                getline(cin, tempStr);
                inputErrorCatcher.removeExtraWhiteSpaceFromString(tempStr);
                myInfo.setFirst(tempStr);
                cout << "Enter Last Name: ";
                getline(cin, tempStr);
                inputErrorCatcher.removeExtraWhiteSpaceFromString(tempStr);
                myInfo.setLast(tempStr);
                cout << endl << "New Name set to " << myInfo.getFirst() << " " 
                     << myInfo.getLast() << "!" << endl;
                break;
            case 3:
                //request and store new age
                cout << "Enter New Age: ";
                cin >> tempInt;
                inputErrorCatcher.boundsCheck(tempInt, 16, 125);
                myInfo.setAge(tempInt);
                inputErrorCatcher.clearKeyboardBuffer();
                cout << endl << "New Age set to " << myInfo.getAge() << "!" << endl;
                break;
            default:
                break;
        }
    
    } while (menuUserSelection != 4);

    //reset variable
    menuUserSelection = 0;
}

//coordinates money transfers between account types
void UserMenu::crossAccountTypeTransferHandler(bool accountType)
{
    //placeholders for checking and savings accounts
    accountNode *savingsPtr;
    accountNode *checkingPtr;
    double transferAmount;

    if (accountType == true)
    {
        //establish checking account
        checkingPtr = myChecking.getSelectedAccount();

        //reset crossTransfer var
        myChecking.resetCrossTransfer();

        //check to see if savings accounts exist
        if (!mySavings.getHead())
        {
            cout << endl << "You have not created a savings account yet!" << endl;
            return;
        }
        //display and select savings accounts
        mySavings.displayAccounts();
        mySavings.selectAccount();
        savingsPtr = mySavings.getSelectedAccount();

        //get transfer amount
        cout << "How much money would you like to transfer from " << checkingPtr->accountName
             << " to " << savingsPtr->accountName << "? ";
        cin >> transferAmount;
        inputErrorCatcher.boundsCheck(transferAmount, 0.0, checkingPtr->total);

        //ammend account totals
        checkingPtr->total -= transferAmount;
        savingsPtr->total += transferAmount;

        //send to history
        myChecking.sendToHistory("Transfer Withdrawal", transferAmount, checkingPtr->total, "NULL");
        mySavings.sendToHistory("Transfer Deposit", transferAmount, savingsPtr->total, "NULL");

        //reset selected accounts
        mySavings.resetSelectedAccount();
    }

     else if (accountType == false)
    {
        //establish checking account
        savingsPtr = mySavings.getSelectedAccount();

        //reset crossTransfer var
        mySavings.resetCrossTransfer();

        //check to see if savings accounts exist
        if (!myChecking.getHead())
        {
            cout << endl << "You have not created a checking account yet!" << endl;
            return;
        }
        //display and select savings accounts
        myChecking.displayAccounts();
        myChecking.selectAccount();
        checkingPtr = myChecking.getSelectedAccount();

        //get transfer amount
        cout << "How much money would you like to transfer from " << savingsPtr->accountName
             << " to " << checkingPtr->accountName << "? ";
        cin >> transferAmount;
        inputErrorCatcher.boundsCheck(transferAmount, 0.0, savingsPtr->total);

        //ammend account totals
        savingsPtr->total -= transferAmount;
        checkingPtr->total += transferAmount;

        //send to history
        myChecking.sendToHistory("Transfer Deposit", transferAmount, checkingPtr->total, "NULL");
        mySavings.sendToHistory("Transfer Withdrawal", transferAmount, savingsPtr->total, "NULL");

        //reset selected accounts
        myChecking.resetSelectedAccount();
    }

    //output success message and new totals for accounts
    cout << endl << "Successfully transfered $" << transferAmount << "!" << endl;
    cout << "New " << checkingPtr->accountName << " total is $" << checkingPtr->total << endl;
    cout << "New " << savingsPtr->accountName << " total is $" << savingsPtr->total << endl;
}

//overloaded operator
ostream &operator << (ostream &os, UserInfo &user)
{
    os << endl 
       << "User ID: " << user.getId() << endl 
       << "User Pin: " << user.getPin() << endl
       << "Name: " << user.getFirst() << " " << user.getLast() << endl 
       << "Age: " << user.getAge() << endl;
    return os;
}