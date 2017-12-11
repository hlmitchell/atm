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

#endif