#include "userFile.h"

//new user constructor and methods---------------------------------------------
UserFile::UserFile()
{
    myInfo.requestNewUserInfo();
    createUserFile();
    displayMainMenu();
}

void UserFile::createUserFile()
{
    textFileName = myInfo.id + ".txt";
    userInfoFile.open(textFileName.c_str(), ios::out);
    userInfoFile.close();
}

//returning user constructor constructor and methods---------------------------
UserFile::UserFile(string userID, string userPin)
{
    openUserFile(userID);
    myInfo.downloadUserInfoFromFile(userInfoFile);
    
    if (userPin != myInfo.pin)
    {
        cout << "Incorrect Pin." << endl;
        userInfoFile.close();
        return;
    }
    
    downloadAccountNamesFromFile();
    userInfoFile.close();
    
    cout << endl << "Welcome Back " << myInfo.firstName << "!" << endl;
    displayMainMenu();
}

void UserFile::openUserFile(string id)
{
    textFileName = id;
    userInfoFile.open(textFileName.c_str(), ios::in);
}

void UserFile::downloadAccountNamesFromFile()
{
    /*string stringSetter;
    
    while (userInfoFile >> stringSetter)
    {
        accountFileNames.push_back(stringSetter);
    }
    
    myAccounts.categorizeAccountFileNames(accountFileNames);
    accountFileNames.clear();*/
}

//main menu methods------------------------------------------------------------
void UserFile::displayMainMenu()
{
    do {
        
        displayMenuOptions();
        validateUserInput(4);
        
        switch(menuUserSelection)
        {
            case 1:
                myAccounts.selectAnAccount();
                break;
            case 2:
                myAccounts.createAnAccount();
                break;
            case 3:
                editUserInfoMenuOption();
                break;
            default:
                break;
        }
    } while (menuUserSelection != 4);
    
    menuUserSelection = 0;
}

void UserFile::displayMenuOptions()
{
    cout << endl << "*** Main Menu ***" << endl << endl;
    cout << "1. Select an Account" << endl;
    cout << "2. Create an Account" << endl;
    cout << "3. Edit User Information" << endl;
    cout << "4. Log Out" << endl;
}

void UserFile::validateUserInput(int upperBounds)
{
    cin >> menuUserSelection;
    inputErrorCatcher.checkForValidUserInput(menuUserSelection, 1, upperBounds);
    inputErrorCatcher.clearKeyboardBuffer();
}

void UserFile::editUserInfoMenuOption()
{
    do {
        
        myInfo.displayUserInfo();
        displayMenuEditOptions();
        validateUserInput(4);
        
        switch(menuUserSelection)
        {
            case 1:
                myInfo.requestUserPin();
                break;
            case 2:
                myInfo.requestFirstName();
                myInfo.requestLastName();
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

void UserFile::displayMenuEditOptions()
{
    cout << endl << "Which of the following would you like to edit: " << endl;
    cout << endl;
    cout << "1. Pin" << endl;
    cout << "2. Name" << endl;
    cout << "3. Age" << endl;
    cout << "4. Back" << endl;
}

//destructor and methods-------------------------------------------------------
UserFile::~UserFile()
{
    userInfoFile.open(textFileName.c_str(), ios::out);
    
    writeUserInfoToFile();
    writeAccountFileNamesToUserFile();
    
    userInfoFile.close();
}

void UserFile::writeUserInfoToFile()
{
    userInfoFile << myInfo.pin << endl;
    userInfoFile << myInfo.id << endl;
    userInfoFile << myInfo.firstName << endl;
    userInfoFile << myInfo.lastName << endl;
    userInfoFile << myInfo.age << endl;
}

void UserFile::writeAccountFileNamesToUserFile()
{
    vector<string> accountFileNames;
    myAccounts.getFileNames(accountFileNames);
    
    for (int i = 0; i < accountFileNames.size(); i++)
        userInfoFile << accountFileNames[i] << endl;
}
