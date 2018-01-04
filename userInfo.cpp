//ATM MACHINE
//Hannah Mitchell
//CS M10B
//December 11th 2017

#include "userInfo.h"

//sets all variables to NULL
UserInfo::UserInfo()
{
    pin = id = firstName = lastName = "";
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
void UserInfo::setFirstName(string f)
{
    firstName = f;
}

//set Last name
void UserInfo::setLastName(string l)
{
    lastName = l;
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
string UserInfo::getFirstName()
{
    return firstName;
}

//return last name
string UserInfo::getLastName()
{
    return lastName;
}

//return age
int UserInfo::getAge()
{
    return age;
}