#include "userInfo.h"

UserInfo::UserInfo()
{
    pin = id = firstName = lastName = "";
    age = 0;
}

void UserInfo::setPin(string p)
{
    pin = p;
}

void UserInfo::setId(string i)
{
    id = i;
}

void UserInfo::setFirstName(string f)
{
    firstName = f;
}

void UserInfo::setLastName(string l)
{
    lastName = l;
}

void UserInfo::setAge(int a)
{
    age = a;
}   

string UserInfo::getPin()
{
    return pin;
}

string UserInfo::getId()
{
    return id;
}

string UserInfo::getFirstName()
{
    return firstName;
}

string UserInfo::getLastName()
{
    return lastName;
}

int UserInfo::getAge()
{
    return age;
}

void UserInfo::displayUserInfo()
{
    cout << endl 
         << "User ID: " << id << endl 
         << "User Pin: " << pin << endl
         << "Name: " << firstName << " " << lastName << endl 
         << "Age: " << age << endl;
}