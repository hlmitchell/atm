//Hannah Mitchell
//CS M10B
//December 5th 2017

#ifndef USERMENU_H
#define USERMENU_H

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>

#include "userInfo.h"
#include "checking.h"
#include "savings.h"

using namespace std;

//prototype for overloaded stream operator
ostream &operator << (ostream &, UserInfo &);

class UserMenu
{
    private:
        int userSelection;      //user input from menus
        bool transfer;          //returned from accounts menu, signals transferHandler()

        UserInfo myInfo;             //instance of userInfo class holding user data
        InputError errorCatcher;          //catches user input errors
        vector<string> accountData;  //list of all account file names

        string fileName;        //user file name with '.txt'
        fstream myFile;         //user file and account names

        Checking myChecking;    //instance of Checking class
        Savings mySavings;      //instance of Savings class

    public:
        //constructor and destructor
        UserMenu();
        UserMenu(string, string);
        ~UserMenu();

        //user manipulators
        void mainMenu();
        void editUserInfo();
        void transferHandler(bool); 

        //friend
        friend ostream & operator << (ostream &, UserInfo &);  
};

//Gathers user information for a new user
UserMenu::UserMenu()
{
    //set variables
    userSelection = 0;
    transfer = false;
    
    //temp vars for passing input to class userInfo
    string tempStr;
    int tempInt;

    //collect basic information from user
    cout << endl << "Thank you for choosing Hannah's Bank!" << endl << endl;
    cout << "Please enter a username: ";
    getline(cin, tempStr);
    //check if username already exists
    errorCatcher.checkID(tempStr);
    myInfo.setId(tempStr);

    //Create file
    fileName = myInfo.getId() + ".txt";
    myFile.open(fileName.c_str(), ios::out);
    myFile.close();
    
    //get pin
    cout << "Choose a 4 digit pin: ";
    getline(cin, tempStr);
    //check for valid input for pin
    errorCatcher.checkPin(tempStr);
    myInfo.setPin(tempStr);

    //get user info
    cout << endl << "Now we'll need to know some information about you!" << endl;
    cout << "What is your first name? ";
    getline(cin, tempStr);
    myInfo.setFirst(tempStr);
    cout << "What is your last name? ";
    getline(cin, tempStr);
    myInfo.setLast(tempStr);

    cout << "Please enter your age: ";
    cin >> tempInt;
    //check for valid input for age
    errorCatcher.boundsCheck(tempInt, 16, 125);
    myInfo.setAge(tempInt);
    errorCatcher.clearField();

    mainMenu();
}

//uploads user information from a previous user
UserMenu::UserMenu(string name, string pin)
{
    //set variables
    userSelection = 0;
    transfer = false;

    //temp vars for reading data
    string tempStr;
    int tempInt;
    
    //open file to extract user info
    fileName = name;
    myFile.open(fileName.c_str(), ios::in);

    //read user pin from file
    myFile >> tempStr;
    myInfo.setPin(tempStr);
    myFile >> tempStr;
    myInfo.setId(tempStr);
    myFile >> tempStr;
    myInfo.setFirst(tempStr);
    myFile >> tempStr;
    myInfo.setLast(tempStr);
    myFile >> tempInt;
    myInfo.setAge(tempInt);

    //if pin is incorrect, return to login screen
    if (pin != myInfo.getPin())
    {
        cout << "Incorrect Pin." << endl;
        myFile.close();
        return;
    }

    //read out file names and store them in vector
    string vecTemp;
    while (myFile >> vecTemp) accountData.push_back(vecTemp);

    //create nodes for existing accounts
    for (int i = 0; i < accountData.size(); i++)
    {
        if (accountData[i][0] == 'C')
            myChecking.setAccountFileNames(accountData[i]);
        else mySavings.setAccountFileNames(accountData[i]);
    }

    //welcome message and main menu
    myFile.close();
    cout << endl << "Welcome Back " << myInfo.getFirst() << "!" << endl;
    mainMenu();
}

//uploads user contents to file
UserMenu::~UserMenu()
{
    //open file
    myFile.open(fileName.c_str(), ios::out);
    //write to file
    myFile << myInfo.getPin() << endl;
    myFile << myInfo.getId() << endl;
    myFile << myInfo.getFirst() << endl;
    myFile << myInfo.getLast() << endl;
    myFile << myInfo.getAge() << endl;

    //delete file names in vector
    accountData.clear();

    //reaquire checking file names and fill vector
    vector<string> temp;
    temp = myChecking.getAccountFileNames();
    for (int i = 0; i < temp.size(); i++) accountData.push_back(temp[i]);
    //reaquire savings file names and fill vector
    temp = mySavings.getAccountFileNames();
    for (int i = 0; i < temp.size(); i++) accountData.push_back(temp[i]);

    //add file names to user info file
    for (int i = 0; i < accountData.size(); i++) myFile << accountData[i] << endl;

    //close
    myFile.close();
}

//display main menu and switch
void UserMenu::mainMenu()
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
        cin >> userSelection;
        errorCatcher.boundsCheck(userSelection, 1, 5);
        errorCatcher.clearField();

        switch(userSelection)
        {
            case 1:
                //Menu requesting checking or savings account
                cout << endl << "Which account type would you like to access?";
                userSelection = errorCatcher.chooseAccountType();
                //check for existing checking accounts
                if (userSelection == 1)
                {
                    //if no account exists then break
                    if (!myChecking.getHead()) 
                    {
                        cout << endl << "You have not created a checking account yet!" << endl;
                        break;
                    }
                    else
                    {
                        //else display all checking accounts
                        myChecking.displayAccounts();       
                        myChecking.selectAccount();

                        do {    //loop allows return to account options menu if cross type transfer occurs

                        //display further menu
                        myChecking.accountOptionsMenu();
                            
                        //check for transfer selection in account options menu
                        transfer = myChecking.getCrossTransfer();
                        if (transfer == true) transferHandler(true);

                        } while (transfer == true);
                    }
                }
                //check for existing savings accounts
                else if (userSelection == 2)
                {
                    //if no account exists then break
                    if (!mySavings.getHead())
                    {
                        cout << endl << "You have not created a savings account yet!" << endl;
                        break;
                    }
                    else
                    {
                        //else display all savings accounts
                        mySavings.displayAccounts();
                        mySavings.selectAccount();

                        do {    //loop allows return to account options menu if cross type transfer occurs

                        //display further menu
                        mySavings.accountOptionsMenu();

                        //check for transfer selection in account options menu
                        transfer = mySavings.getCrossTransfer();
                        if (transfer == true) transferHandler(false); 

                        } while (transfer == true);                 
                    }
                }

                //reset transfer variable
                transfer = false;
                break;
            case 2:
                //Menu requesting checking or savings account
                cout << endl << "Which type of account would you like to create?";
                userSelection = errorCatcher.chooseAccountType();

                //create node for checking
                if (userSelection == 1) myChecking.createAccount(myInfo.getId());
                //create node for savings
                else if (userSelection == 2) mySavings.createAccount(myInfo.getId());
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
    } while (userSelection != 5);

    //reset variable
    userSelection = 0;
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
        cin >> userSelection;
        errorCatcher.boundsCheck(userSelection, 1, 4);
        errorCatcher.clearField();

        switch(userSelection)
        {
            case 1:
                //request and store new pin
                cout << "Enter New Pin: ";
                getline(cin, tempStr);
                errorCatcher.checkPin(tempStr);
                myInfo.setPin(tempStr);
                cout << endl << "New Pin set to " << myInfo.getId() << "!" << endl;
                break;
            case 2:
                //request and store new name
                cout << "Enter First Name: ";
                getline(cin, tempStr);
                myInfo.setFirst(tempStr);
                cout << "Enter Last Name: ";
                getline(cin, tempStr);
                myInfo.setLast(tempStr);
                cout << endl << "New Name set to " << myInfo.getFirst() << " " 
                     << myInfo.getLast() << "!" << endl;
                break;
            case 3:
                //request and store new age
                cout << "Enter New Age: ";
                cin >> tempInt;
                errorCatcher.boundsCheck(tempInt, 16, 125);
                myInfo.setAge(tempInt);
                errorCatcher.clearField();
                cout << endl << "New Age set to " << myInfo.getAge() << "!" << endl;
                break;
            default:
                break;
        }
    
    } while (userSelection != 4);

    //reset variable
    userSelection = 0;
}

//coordinates money transfers between account types
void UserMenu::transferHandler(bool t)
{
    //placeholders for checking and savings accounts
    accountNode *savingsPtr;
    accountNode *checkingPtr;
    double num;

    if (t == true)
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
        cin >> num;
        errorCatcher.boundsCheck(num, 0.0, checkingPtr->total);

        //ammend account totals
        checkingPtr->total -= num;
        savingsPtr->total += num;

        //send to history
        myChecking.sendToHistory("Transfer Withdrawal", num, checkingPtr->total, "NULL");
        mySavings.sendToHistory("Transfer Deposit", num, savingsPtr->total, "NULL");

        //reset selected accounts
        mySavings.resetSelectedAccount();
    }

     else if (t == false)
    {
        //establish checking account
        savingsPtr = mySavings.getSelectedAccount();

        //reset crossTransfer var
        mySavings.resetCrossTransfer();

        //check to see if savings accounts exist
        if (!myChecking.getHead())
        {
            cout << endl << "You have not created a savings account yet!" << endl;
            return;
        }
        //display and select savings accounts
        myChecking.displayAccounts();
        myChecking.selectAccount();
        checkingPtr = myChecking.getSelectedAccount();

        //get transfer amount
        cout << "How much money would you like to transfer from " << savingsPtr->accountName
             << " to " << checkingPtr->accountName << "? ";
        cin >> num;
        errorCatcher.boundsCheck(num, 0.0, savingsPtr->total);

        //ammend account totals
        savingsPtr->total -= num;
        checkingPtr->total += num;

        //send to history
        myChecking.sendToHistory("Transfer Deposit", num, checkingPtr->total, "NULL");
        mySavings.sendToHistory("Transfer Withdrawal", num, savingsPtr->total, "NULL");

        //reset selected accounts
        myChecking.resetSelectedAccount();
    }

    //output success message and new totals for accounts
    cout << endl << "Successfully transfered $" << num << "!" << endl;
    cout << "New " << checkingPtr->accountName << " total is $" << checkingPtr->total << endl;
    cout << "New " << savingsPtr->accountName << " total is $" << savingsPtr->total << endl;
}

//overloaded operator
ostream &operator << (ostream &os, UserInfo &user)
{
    os << endl << user.getId() << endl << user.getPin() << endl
       << user.getFirst() << " " << user.getLast() << endl << user.getAge() << endl;
    return os;
}

#endif