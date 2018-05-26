#ifndef USERINFO_H
#define USERINFO_H

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

#include "inputError.h"

using namespace std;

class UserInfo 
{
friend class UserFile;

protected:
    string pin;
    string id;
    string firstName;
    string lastName;
    int age;

    InputError inputErrorCatcher;

    void displayUserInfo();
    void requestNewUserInfo();
    void requestUserName();
    void requestUserPin();
    void requestFirstName();
    void requestLastName();
    void requestAge();

    void downloadUserInfoFromFile(fstream&);
    
public:
    UserInfo();
};

#endif
