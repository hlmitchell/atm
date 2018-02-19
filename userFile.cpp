#include "userFile.h"

UserFile::UserFile()
{
    collectNewUserInfo();
}

void UserFile::collectNewUserInfo()
{
    myInfo.requestNewUserInfo();
    createUserFile();

    //UserMenu myMenu(myAccounts, myInfo);
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
    
    //UserMenu myMenu(myAccounts, myInfo);
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

    //myAccounts.categorizeAccountFileNames(accountFileNames);
    accountFileNames.clear();
}


UserFile::~UserFile()
{
    userInfoFile.open(textFileName.c_str(), ios::out);

    writeUserInfoToFile();
    writeAccountNamesToFile();

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

void UserFile::writeAccountNamesToFile()
{
    //accountFileNames = myAccounts.getAllAccountFileNames();

    for (int i = 0; i < accountFileNames.size(); i++)
    { 
        userInfoFile << accountFileNames[i] << endl;
    }
}