#ifndef USERFILE_H
#define USERFILE_H

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>

#include "userInfo.h"
#include "accounts.h"

using namespace std;

class UserFile
{
private:
    AccountsTree myAccounts;
    UserInfo myInfo;
    InputError inputErrorCatcher;
    
    int menuUserSelection;
    fstream userInfoFile;
    string userFileName;

    //new user methods
    void initializeClassVariables();
    void createUserFile();

    //returning user methods
    void downloadAccountNamesFromFile();

    //destructor methods
    void writeUserInfoToFile();
    void writeAccountFileNamesToUserFile();
    
    //menu methods
    void displayMainMenu();
    void displayMenuOptions();
    void validateUserInput(int);
    void editUserInfoMenuOption();
    void displayMenuEditOptions();
    
public:
    UserFile();
    UserFile(string, string);
    ~UserFile();
};

#endif
