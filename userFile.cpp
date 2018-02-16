#include "userFile.h"

UserFile::UserFile()
{
    collectNewUserInfo();
}

void UserFile::collectNewUserInfo()
{
    myInfo.requestNewUserInfo();
    createUserFile();

    UserMenu myMenu(myChecking, mySavings, myInfo);
}

void UserFile::createUserFile()
{
    textFileName = myInfo.getId() + ".txt";
    userInfoFile.open(textFileName.c_str(), ios::out);
    userInfoFile.close();
}



UserFile::UserFile(string userID, string userPin)
{
    openUserFile(userID);
    myInfo.downloadUserInfoFromFile(userInfoFile);

    if (userPin != myInfo.getPin())
    {
        cout << "Incorrect Pin." << endl;
        userInfoFile.close();
        return;
    }

    downloadAccountNamesFromFile();
    userInfoFile.close();

    cout << endl << "Welcome Back " << myInfo.getFirstName() << "!" << endl;
    
    UserMenu myMenu(myChecking, mySavings, myInfo);
}

void UserFile::openUserFile(string id)
{
    textFileName = id;
    userInfoFile.open(textFileName.c_str(), ios::in);
}

void UserFile::downloadAccountNamesFromFile()
{
    string stringSetter;
    
    while (userInfoFile >> stringSetter) 
    {
        accountFileNames.push_back(stringSetter);
    }

    categorizeAccountNames();
}

void UserFile::categorizeAccountNames()
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



UserFile::~UserFile()
{
    userInfoFile.open(textFileName.c_str(), ios::out);

    writeUserInfoToFile();
    getAndWriteAccountFileNames();

    userInfoFile.close();
}

void UserFile::writeUserInfoToFile()
{
    userInfoFile << myInfo.getPin() << endl;
    userInfoFile << myInfo.getId() << endl;
    userInfoFile << myInfo.getFirstName() << endl;
    userInfoFile << myInfo.getLastName() << endl;
    userInfoFile << myInfo.getAge() << endl;
}

void UserFile::getAndWriteAccountFileNames()
{
    getCheckingAccountFileNames();
    writeAccountNamesToFile();

    getSavingsAccountFileNames();
    writeAccountNamesToFile();
}

void UserFile::getCheckingAccountFileNames()
{
    accountFileNames = myChecking.getAccountFileNames();
}

void UserFile::getSavingsAccountFileNames()
{
    accountFileNames = mySavings.getAccountFileNames();
}

void UserFile::writeAccountNamesToFile()
{
    for (int i = 0; i < accountFileNames.size(); i++) 
        userInfoFile << accountFileNames[i] << endl;
}