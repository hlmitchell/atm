//Hannah Mitchell
//CS M10B
//December 5th 2017

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
        string pin;             //user pin number
        string id;              //user id
        string first;           //user first name
        string last;            //user last name
        int age;                //user age

    public:
        //constructor
        UserInfo();

        //setters
        void setPin(string);
        void setId(string);
        void setFirst(string);
        void setLast(string);
        void setAge(int);

        //getters
        string getPin();
        string getId();
        string getFirst();
        string getLast();
        int getAge();
};

//sets all variables to NULL
UserInfo::UserInfo()
{
    pin = id = first = last = "";
    age = 0;
}

//set Pin
void UserInfo::setPin(string p)
{
    pin = p;
}

//set ID
void UserInfo::setId(string i)
{
    id = i;
}

//set First name
void UserInfo::setFirst(string f)
{
    first = f;
}

//set Last name
void UserInfo::setLast(string l)
{
    last = l;
}

//set age
void UserInfo::setAge(int a)
{
    age = a;
}   

//return pin
string UserInfo::getPin()
{
    return pin;
}

//return id
string UserInfo::getId()
{
    return id;
}

//return first name
string UserInfo::getFirst()
{
    return first;
}

//return last name
string UserInfo::getLast()
{
    return last;
}

//return age
int UserInfo::getAge()
{
    return age;
}

#endif