#ifndef USERINFO_H
#define USERINFO_H

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>

#include "checking.h"
#include "savings.h"

using namespace std;

class UserInfo 
{
    private:
        string pin;                 
        string id;                  
        string firstName;           
        string lastName;            
        int age;    

        vector<string> accountFileNames;       
        string txtFileName;             
        fstream userInfoFile;

        //Checking *myChecking;
        //Savings *mySavings;

        InputError inputErrorCatcher;      

        void setUserName();
        void setPin();
        void setFirstName();
        void setLastName();
        void setAge();       

    public:
        UserInfo();

        void displayUserInfo();
        string getId();

        void requestUserName();
        void requestUserPin();
        void requestFullName();
        void requestFirstName();
        void requestLastName();
        void requestAge();

        //void setAccountPointers(Checking&, Savings&);

        void createUserFile();
        bool readUserInfoFromFile(string, string);
        void openUserFile(string);
        void downloadUserInfo();
        bool checkIfUserPinValid(string);
        void downloadAccountNamesFromFile();
        void categorizeAccountNames();

        void writeUserInfoToFile();
        void uploadUserInfoToFile();
        void getAccountFileNames();
        void writeAccountNamesToFile();
};

#endif