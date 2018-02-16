#ifndef USERFILE_H
#define USERFILE_H

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>

#include "userInfo.h"
#include "userMenu.h"

using namespace std;

class UserFile
{
    private:
        Checking myChecking;    
        Savings mySavings;
                
        UserInfo myInfo;
        InputError inputErrorCatcher;          
        
        fstream userInfoFile;
        vector<string> accountFileNames;       
        string textFileName;

        void initializeClassVariables();
        void collectNewUserInfo();
        void createUserFile();

        void openUserFile(string);
        void downloadAccountNamesFromFile();
        void categorizeAccountNames();

        void writeUserInfoToFile();
        void getAndWriteAccountFileNames();
        void getCheckingAccountFileNames();
        void getSavingsAccountFileNames();
        void writeAccountNamesToFile();
        
    public:
        UserFile();
        UserFile(string, string);
        ~UserFile();
};

#endif