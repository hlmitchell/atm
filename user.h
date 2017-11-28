#ifndef USER_H
#define USER_H

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

#include "checking.h"
#include "savings.h"

using namespace std;

struct userInfo {
    string pin;
    string id;
    string first;
    string last;
    int age;
};

class User : public Input
{
    protected:
        int userSelection;
        bool transfer;

        userInfo myInfo;

        string fileName;
        fstream myFile;

        Checking myChecking;
        Savings mySavings;

    public:
        User();
        User(string, string);
        ~User();
        void mainMenu();
        void editUserInfo();
        void transferHandler(bool);
};

//Gathers user information for a new user
User::User() : Input()
{
    userSelection = 0;
    transfer = false;

    //collect basic information from user
    cout << endl << "Thank you for choosing Hannah's Bank!" << endl << endl;
    cout << "Please enter a username: ";
    getline(cin, myInfo.id);
    //check if username already exists
    checkID(myInfo.id);

    //Create file
    fileName = myInfo.id + ".txt";
    myFile.open(fileName.c_str(), ios::out);
    myFile.close();
    
    //get pin
    cout << "Choose a 4 digit pin: ";
    getline(cin, myInfo.pin);
    //check for valid input for pin
    checkPin(myInfo.pin);

    //get user info
    cout << endl << "Now we'll need to know some information about you!" << endl;
    cout << "What is your last name? ";
    getline(cin, myInfo.last);
    cout << "What is your first name? ";
    getline(cin, myInfo.first);

    cout << "Please enter your age: ";
    cin >> myInfo.age;
    //check for valid input for age
    boundsCheck(myInfo.age, 16, 125);
    clearField();

    mainMenu();
}

//uploads user information from a previous user
User::User(string name, string pin) : Input()
{
    userSelection = 0;
    transfer = false;
    
    //reopen file for editting with binary
    fileName = name;
    myFile.open(fileName.c_str(), ios::in|ios::binary);

    //read userInfo using binary
    myFile.read(reinterpret_cast<char *>(&myInfo), sizeof(myInfo));
    myFile.close();

    if (pin == myInfo.pin)
    {
        cout << endl << "Welcome Back " << myInfo.first << "!" << endl;
        mainMenu();
    }
    else cout << "Incorrect Pin." << endl;
}

//uploads user contents to file
User::~User()
{
    //reopen file in binary
    myFile.open(fileName.c_str(), ios::out|ios::binary);

    //write to file using binary
    myFile.write(reinterpret_cast<char *>(&myInfo), sizeof(myInfo));
    
    myFile.close();
}

void User::mainMenu()
{
    do {
        //main menu
        cout << endl << "*** Main Menu ***" << endl << endl;
        cout << "1. Select an Account" << endl;
        cout << "2. Create an Account" << endl;
        cout << "3. Edit User Information" << endl;
        cout << "4. Log Out" << endl;

        //validate input
        cin >> userSelection;
        boundsCheck(userSelection, 1, 4);
        clearField();

        switch(userSelection)
        {
            case 1:
                //Menu requesting checking or savings account
                cout << endl << "Which account type would you like to access?" << endl;
                userSelection = chooseAccountType();
                //check for existing checking accounts
                if (userSelection == 1)
                {
                    //allows access to checking file******************************
                    myChecking.setFileName(myInfo.id);

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

                        //check for transfer selection in account options menu
                        transfer = myChecking.accountOptionsMenu();
                        if (transfer == true) transferHandler(true);
                    }
                }
                //check for existing savings accounts****************************
                else if (userSelection == 2)
                {
                    //allows access to savings file
                    mySavings.setFileName(myInfo.id);

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

                        //check for transfer selection in account options menu
                        transfer = mySavings.accountOptionsMenu();
                        if (transfer == true) transferHandler(false);                  
                    }
                }

                //reset transfer variable
                transfer = false;
                break;

            case 2:
                //Menu requesting checking or savings account
                cout << endl << "Which type of account would you like to create?" << endl;
                userSelection = chooseAccountType();

                //create node for checking in class Checking
                if (userSelection == 1) myChecking.createAccount();
                //create node for savings in class savings
                else if (userSelection == 2) mySavings.createAccount();
                break;
            case 3:
                editUserInfo();
                break;
            default:
                break;
        }

    } while (userSelection != 4);
}

void User::editUserInfo()
{
    //menu for ammending user information
    do {
        cout << endl << "Which of the following would you like to edit: " << endl;
        cout << "1. Pin" << endl;
        cout << "2. Name" << endl;
        cout << "3. Age" << endl;
        cout << "4. Back" << endl;

        //check input selection
        cin >> userSelection;
        boundsCheck(userSelection, 1, 4);
        clearField();

        switch(userSelection)
        {
            case 1:
                //request and store new pin
                cout << "Enter New Pin: ";
                getline(cin, myInfo.pin);
                checkPin(myInfo.pin);
                cout << endl << "New Pin set to " << myInfo.pin << "!" << endl;
                break;
            case 2:
                //request and store new name
                cout << "Enter First Name: ";
                cin.ignore();
                getline(cin, myInfo.first);
                cout << "Enter Last Name: ";
                getline(cin, myInfo.last);
                cout << endl << "New Name set to " << myInfo.first << " " 
                     << myInfo.last << "!" << endl;
                break;
            case 3:
                //request and store new age
                cout << "Enter New Age: ";
                cin >> myInfo.age;
                boundsCheck(myInfo.age, 16, 125);
                clearField();
                cout << endl << "New Age set to " << myInfo.age << "!" << endl;
                break;
            default:
                break;
        }
    
    } while (userSelection != 4);
    
    mainMenu();

}

void User::transferHandler(bool t)
{
    //placeholders for checking and savings accounts
    accountNode *savings;
    accountNode *checking;
    double num;

    if (t == true)
    {
        //establish checking account
        checking = myChecking.getSelectedAccount();

        //check to see if savings accounts exist
        if (!mySavings.getHead())
        {
            cout << endl << "You have not created a savings account yet!" << endl;
            return;
        }
        //display and select savings accounts
        mySavings.displayAccounts();
        mySavings.selectAccount();
        savings = mySavings.getSelectedAccount();

        //get transfer amount
        cout << "How much money would you like to transfer from " << checking->accountName
             << " to " << savings->accountName << "? ";
        cin >> num;
        boundsCheck(num, 0.0, checking->total);

        //ammend account totals
        checking->total -= num;
        savings->total += num;
    }

     else if (t == false)
    {
        //establish checking account
        savings = mySavings.getSelectedAccount();

        //check to see if savings accounts exist
        if (!myChecking.getHead())
        {
            cout << endl << "You have not created a savings account yet!" << endl;
            return;
        }
        //display and select savings accounts
        myChecking.displayAccounts();
        myChecking.selectAccount();
        checking = myChecking.getSelectedAccount();

        //get transfer amount
        cout << "How much money would you like to transfer from " << savings->accountName
             << " to " << checking->accountName << "? ";
        cin >> num;
        boundsCheck(num, 0.0, savings->total);

        //ammend account totals
        savings->total -= num;
        checking->total += num;
    }

    cout << endl << "Successfully transfered $" << num << "!" << endl;
    cout << "New " << checking->accountName << " total is $" << checking->total << endl;
    cout << "New " << savings->accountName << " total is $" << savings->total << endl;
}

#endif