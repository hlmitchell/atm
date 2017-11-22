//error list
    //starting pin with 0
    //pin being all 0

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
    int pin;
    string id;
    string first;
    string last;
    int age;
};

class User
{
    protected:
        int userSelection;

        userInfo myInfo;

        string fileName;
        fstream myFile;

        Checking myChecking;
        Savings mySavings;

    public:
        User();
        User(string);
        ~User();
        void mainMenu();
        void advancedOptionsMenu();
        void editUserInfo();
        void chooseAccountType();
        
        //input error checking functions
        void checkPin(int&);

        template <class T>
        void boundsCheck(T&, const T, const T);

        template <class T>
        void cinFail(T&);

        void clearField();
};

//Gathers user information for a new user
User::User()
{
    //collect basic information from user
    cout << "Thank you for choosing the People's Bank!" << endl;
    cout << "Please enter a username: ";
    cin.ignore();
    getline(cin, myInfo.id);

    cout << "Choose a 4 digit pin: ";
    cin >> myInfo.pin;
    //check for valid input for pin
    checkPin(myInfo.pin);
    clearField();

    cout << endl << "Now we'll need to know some information about you!" << endl;
    cout << "What is your last name? ";
    cin.ignore();
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
User::User(string name)
{
    //reopen file for editting with binary
    fileName = name;
    myFile.open(name.c_str(), ios::in|ios::binary);

    //read userInfo using binary
    myFile.read(reinterpret_cast<char *>(&myInfo), sizeof(myInfo));

    cout << endl << "Welcome Back " << myInfo.first << "!" << endl;

    mainMenu();
}

//uploads user contents to file
User::~User()
{
    //close and reopen file in binary
    myFile.close();
    myFile.open(fileName.c_str(), ios::out|ios::binary);

    //write to file using binary
    myFile.write(reinterpret_cast<char *>(&myInfo), sizeof(myInfo));
    
    myFile.close();
}

void User::mainMenu()
{
    do {
        //main menu
        cout << endl << "*** Main Menu ***" << endl;
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
                chooseAccountType();
                //check for existing checking accounts
                if (userSelection == 1)
                {
                    if (!myChecking.getHead()) //if no account exists then break
                        {
                            cout << endl << "You have not created a checking account yet!" << endl;
                            break;
                        }
                    else
                        myChecking.displayAccounts();   //else display all checking accounts
                }
                //check for existing savings accounts
                else
                {
                    if (!mySavings.getHead())   //if no account exists then break
                        {
                            cout << endl << "You have not created a checking account yet!" << endl;
                            break;
                        }
                    else
                        mySavings.displayAccounts();    //else display all savings accounts
                }
            
                //after an account is selected
                advancedOptionsMenu();
                break;

            case 2:
                //Menu requesting checking or savings account
                cout << endl << "Which type of account would you like to create?" << endl;
                chooseAccountType();

                //create node for checking in class Checking
                if (userSelection == 1)
                    {myChecking.createAccount();}
                //create node for savings in class savings
                else
                    {mySavings.createAccount();}
                break;
            case 3:
                editUserInfo();
                break;
            default:
                break;
        }

    } while (userSelection != 4);
}

void User::advancedOptionsMenu()
{
    do {
        //advanced options
        cout << endl << "*** Advanced Options ***" << endl;
        cout << "1. Withdraw" << endl;
        cout << "2. Deposit" << endl;
        cout << "3. Merge Accounts" << endl;
        cout << "4. Transfer Money" << endl;
        cout << "5. Delete Account" << endl;
        cout << "6. Back" << endl;

        //validate input
        cin >> userSelection;
        boundsCheck(userSelection, 1, 6);
        clearField();

        switch(userSelection)
        {
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            default:
                break;
        }

    } while (userSelection != 6);
    
    //return to main menu
    mainMenu();
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
                cin >> myInfo.pin;
                checkPin(myInfo.pin);
                clearField();
                cout << endl << "New Pin set to " << myInfo.pin << "!" << endl;
                break;
            case 2:
                //request and store new name
                cout << "Enter First Name: ";
                cin >> myInfo.first;
                cout << "Enter Last Name: ";
                cin >> myInfo.last;
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

}

//choose account type for menu options
void User::chooseAccountType()
{   
    //display part of menu and check bounds
    cout << "1. Checking" << endl;
    cout << "2. Savings" << endl;
    cout << "3. Back" << endl;
    cin >> userSelection;
    boundsCheck(userSelection, 1, 3);
}


//ERROR GARBAGE

void User::checkPin(int &p)
{
    int copy = p;          //copy of p
    int length = 0;        //length of 

    while(cin.fail() || length != 4)
    {
        //cin.fail input error check
        cinFail(copy);

        //find length of pin
        while (copy > 0)
        {
            copy /= 10;
            length++;
        }
        //reinitialize copy
        copy = p;

        //if pin length isn't 4 then reprompt
        if (length != 4)
        {
            cout << "Invalid Entry. Please try again: ";
            cin >> copy;
            length = 0;
        }
        //if pin is 4 then continue
        else {p = copy;}

    }
}

template <class T>
void User::boundsCheck(T &var, const T lower, const T upper)
{
    while (cin.fail() || var < lower || var > upper)
    {
        //cin.fail input error check
        cinFail(var);

        //check for in bounds
        while (var < lower || var > upper || var)
        {
            cout << "Invalid Entry. Please try again: ";
            cin >> var;
        }
    }
}

template <class T>
void User::cinFail(T &var)
{
    while (cin.fail())
    {
        clearField();

        cout << "Invalid Entry. Please try again: ";
        cin >> var;
    }
}

/*********************************/
//function clear input field
/*********************************/
void User::clearField()
{
    cin.clear();
    cin.ignore(1000, '\n');
}

#endif