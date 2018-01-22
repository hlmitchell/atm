//ATM MACHINE
//Hannah Mitchell
//CS M10B
//December 11th 2017

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

    public:
        UserInfo();

        void setPin(string);
        void setId(string);
        void setFirstName(string);
        void setLastName(string);
        void setAge(int);

        string getPin();
        string getId();
        string getFirstName();
        string getLastName();
        int getAge();
};

#endif