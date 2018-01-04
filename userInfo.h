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
        string pin;                 //user pin number
        string id;                  //user id
        string firstName;           //user first name
        string lastName;            //user last name
        int age;                    //user age

    public:
        //constructor
        UserInfo();

        //setters
        void setPin(string);
        void setId(string);
        void setFirstName(string);
        void setLastName(string);
        void setAge(int);

        //getters
        string getPin();
        string getId();
        string getFirstName();
        string getLastName();
        int getAge();
};

#endif