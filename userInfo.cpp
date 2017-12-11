//ATM MACHINE
//Hannah Mitchell
//CS M10B
//December 11th 2017

#include "userInfo.h"

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