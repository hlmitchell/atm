#include "userInfo.h"

UserInfo::UserInfo()
{
    pin = id = firstName = lastName = "";
    age = 0;
}



void UserInfo::displayUserInfo()
{
    cout << endl;
    cout << "User ID: " << id << endl 
         << "User Pin: " << pin << endl
         << "Name: " << firstName << " " << lastName << endl 
         << "Age: " << age << endl;
}

string UserInfo::getId()
{
    return id;
}


void UserInfo::requestUserName()
{
    cout << "Please enter a username: ";
    setUserName();
}

void UserInfo::setUserName()
{
    getline(cin, id); 
    inputErrorCatcher.checkForValidIDEntry(id);
}

void UserInfo::requestUserPin()
{
    cout << "Choose a 4 digit pin: ";
    setPin();
}

void UserInfo::setPin()
{
    getline(cin, pin);
    inputErrorCatcher.checkForValidPinEntry(pin);
}

void UserInfo::requestFullName()
{
    requestFirstName();
    requestLastName();
}

void UserInfo::requestFirstName()
{
    cout << "What is your first name? ";
    setFirstName();
}

void UserInfo::setFirstName()
{
    getline(cin, firstName);
    inputErrorCatcher.removeExtraWhiteSpaceFromString(firstName);
}

void UserInfo::requestLastName()
{
    cout << "What is your last name? ";
    setLastName();
}

void UserInfo::setLastName()
{
    getline(cin, lastName);
    inputErrorCatcher.removeExtraWhiteSpaceFromString(lastName);
}

void UserInfo::requestAge()
{
    cout << "Please enter your age: ";
    setAge();
}

void UserInfo::setAge()
{
    cin >> age;
    inputErrorCatcher.checkForValidUserInput(age, 16, 125);
    inputErrorCatcher.clearKeyboardBuffer();
}



/*void UserInfo::setAccountPointers(Checking &myCheck, Savings &mySave)
{
    myChecking = &myCheck;
    mySavings = &mySave;
}*/



void UserInfo::createUserFile()
{
    txtFileName = id + ".txt";
    userInfoFile.open(txtFileName.c_str(), ios::out);
    userInfoFile.close();
}

bool UserInfo::readUserInfoFromFile(string userID, string userPin)
{
    openUserFile(userID);
    downloadUserInfo();

    if (!checkIfUserPinValid(userPin)) return false;

    downloadAccountNamesFromFile();
    userInfoFile.close();

    cout << endl << "Welcome Back " << firstName << "!" << endl;
    return true;
}

void UserInfo::openUserFile(string id)
{
    txtFileName = id;
    userInfoFile.open(txtFileName.c_str(), ios::in);
}

void UserInfo::downloadUserInfo()
{
    userInfoFile >> pin;
    userInfoFile >> id;
    userInfoFile >> firstName;
    userInfoFile >> lastName;
    userInfoFile >> age;
}

bool UserInfo::checkIfUserPinValid(string userPin)
{
    if (userPin != pin)
    {
        cout << "Incorrect Pin." << endl;
        userInfoFile.close();
        return false;
    }
    return true;
}

void UserInfo::downloadAccountNamesFromFile()
{
    string accountName;
    
    while (userInfoFile >> accountName) 
    {
        accountFileNames.push_back(accountName);
    }

    categorizeAccountNames();
}

void UserInfo::categorizeAccountNames()
{
    /*for (int i = 0; i < accountFileNames.size(); i++)
    {
        if (accountFileNames[i][0] == 'C')
            myChecking->downloadExistingAccounts(accountFileNames[i]);
        else if (accountFileNames[i][0] == 'S')
            mySavings->downloadExistingAccounts(accountFileNames[i]);
    }*/

    accountFileNames.clear();
}



void UserInfo::writeUserInfoToFile()
{
    userInfoFile.open(txtFileName.c_str(), ios::out);

    uploadUserInfoToFile();
    getAccountFileNames();

    userInfoFile.close();
}

void UserInfo::uploadUserInfoToFile()
{
    userInfoFile << pin << endl;
    userInfoFile << id << endl;
    userInfoFile << firstName << endl;
    userInfoFile << lastName << endl;
    userInfoFile << age << endl;
}

void UserInfo::getAccountFileNames()
{
    /*accountFileNames = myChecking->getAccountFileNames();
    writeAccountNamesToFile();

    accountFileNames = mySavings->getAccountFileNames();
    writeAccountNamesToFile();*/
}

void UserInfo::writeAccountNamesToFile()
{
    for (int i = 0; i < accountFileNames.size(); i++) 
        userInfoFile << accountFileNames[i] << endl;
}