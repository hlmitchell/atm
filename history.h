//Hannah Mitchell
//CS M20
//December 5th 2017

#ifndef HISTORY_H
#define HISTORY_H

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <ctime>

using namespace std;

struct accountHistory
{
    string action;                  //action that occured
    double amount;                  //amount of money moved
    double total;                   //new account total after move
    string date;                    //date and time of transaction
    struct accountHistory *next;    //pointer to next accountHistory node
};

class History
{
    protected:
        accountHistory *top;    //top of linked list stack of account history
        time_t rawTime;         //time stamp holder

    public:
        History();
        ~History();

        void push(string, double, double);
        void display();
};

//constructor sets top to NULL
History::History()
{
    top = NULL;
}

//destructor deletes linked list
History::~History()
{
    //temp pointers
    accountHistory *nodePtr;
    accountHistory *nextNode;

    //position nodePtr at top
    nodePtr = top;

    //while nodePtr is not at the end of the list
    while (nodePtr != NULL)
    {
        //save a pointer to the next node
        nextNode = nodePtr->next;
        //delete current node
        delete nodePtr;
        //move nodePtr to next node
        nodePtr = nextNode;
    }
}

//pushes new history node onto top of stack
void History::push(string type, double num, double t)
{
    accountHistory *newNode;    //pointer to new node

    //get time
    time (&rawTime);

    //allocate new node and store arguments there
    newNode = new accountHistory;
    newNode->action = type;
    newNode->amount = num;
    newNode->total = t;
    newNode->date = ctime(&rawTime);;

    //if stack is empty, assign new node to top
    if (top == NULL)
    {
        top = newNode;
        top->next = NULL;
    }
    //otherwise set new node to top and push others down stack
    else
    {
        newNode->next = top;
        top = newNode;
    }    
}

//display account history
void History::display()
{
    accountHistory *tempPtr;    //temp pointer
    tempPtr = top;              //set temp pointer to top of stack

    //if top is NULL, there is no history available
    if (tempPtr == NULL) 
    {
        cout << endl << "There seems to be nothing here!" << endl;
        return;
    }

    //header message
    cout << endl << "***Transaction History***" << endl;

    //if top isn't NULL, go through list and display accounts
    while (tempPtr)
    {
        //formatting
        cout << fixed << setprecision(2);
        cout << endl << tempPtr->action;
        cout << " of $" << tempPtr->amount;
        cout << " for new total of $" << tempPtr->total;
        cout << " on " << tempPtr->date << endl;
        //move to next node
        tempPtr = tempPtr->next;
    }

    //footer message
    cout << endl << "***End Transaction History***" << endl;
    return;
}

#endif