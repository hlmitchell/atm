#ifndef USERFILE_H
#define USERFILE_H

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>

#include "userInfo.h"
#include "userMenu.h"
#include "accountTree.h"

using namespace std;

class UserFile
{
    private:
        //AccountTree myAccounts;
                
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

        void writeUserInfoToFile();
        void writeAccountNamesToFile();
        
    public:
        UserFile();
        UserFile(string, string);
        ~UserFile();
};

#endif