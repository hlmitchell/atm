#include "userInfo.h"

UserInfo::UserInfo()
{
    pin = id = firstName = lastName = "";
    age = 0;
}

void UserInfo::displayUserInfo()
{
    cout << endl 
         << "User ID: " << id << endl 
         << "User Pin: " << pin << endl
         << "Name: " << firstName << " " << lastName << endl 
         << "Age: " << age << endl;
}

void UserInfo::requestNewUserInfo()
{
    cout << endl << "Thank you for choosing Hannah's Bank!" << endl << endl;
    
    requestUserName();
    requestUserPin();

    cout << endl << "Now we'll need to know some information about you!" << endl;

    requestFirstName();
    requestLastName();
    requestAge();
}

void UserInfo::requestUserName()
{
    cout << "Please enter a username: ";
    getline(cin, id); 
    inputErrorCatcher.checkForValidIDEntry(id);
}

void UserInfo::requestUserPin()
{
    cout << "Choose a 4 digit pin: ";
    getline(cin, pin);
    inputErrorCatcher.checkForValidPinEntry(pin);
}

void UserInfo::requestFirstName()
{
    cout << "What is your first name? ";
    getline(cin, firstName);
    inputErrorCatcher.removeExtraWhiteSpaceFromString(firstName);
}

void UserInfo::requestLastName()
{
    cout << "What is your last name? ";
    getline(cin, lastName);
    inputErrorCatcher.removeExtraWhiteSpaceFromString(lastName);
}

void UserInfo::requestAge()
{
    cout << "Please enter your age: ";
    cin >> age;
    inputErrorCatcher.checkForValidUserInput(age, 16, 125);
    inputErrorCatcher.clearKeyboardBuffer();
}

void UserInfo::downloadUserInfoFromFile(fstream &userInfoFile)
{
    userInfoFile >> pin;
    userInfoFile >> id;
    userInfoFile >> firstName;
    userInfoFile >> lastName;
    userInfoFile >> age;
}
