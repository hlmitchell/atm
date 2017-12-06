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
#include <vector>

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
        //constructors and destructor
        History();
        ~History();

        //history manipulators
        void push(string, double, double, string);
        void display();
        void uploadHistory(fstream &);
        void downloadHistory(fstream &);
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
void History::push(string type, double num, double t, string d)
{
    accountHistory *newNode;    //pointer to new node

    //get time
    time (&rawTime);

    //allocate new node and store arguments there
    newNode = new accountHistory;
    newNode->action = type;
    newNode->amount = num;
    newNode->total = t;
    if (d == "NULL")
    {
        newNode->date = ctime(&rawTime);
        //remove '\n' from end
        newNode->date.pop_back();
    }
    else newNode->date = d;

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
    //item line description
    cout << endl << left << setw(21) << "Description" << setw(14) << "Amount" << setw(23) << "Available Balance";
    cout << setw(20) << "Posting Date" << endl;

    //if top isn't NULL, go through list and display accounts
    while (tempPtr)
    {
        //formatting
        cout << fixed << setprecision(2) << left;
        cout << endl << setw(21) << tempPtr->action;
        cout << setw(14) << tempPtr->amount;
        cout << setw(23)<< tempPtr->total;
        cout << setw(20) << tempPtr->date << endl;
        //move to next node
        tempPtr = tempPtr->next;
    }

    //footer message
    cout << endl << "***End Transaction History***" << endl;
    return;
}

//upload history into file
void History::uploadHistory(fstream &file)
{
    //temp nodes for moving through files
    accountHistory *nodePtr;
    accountHistory *prevNode;

    //set nodePtr to end of list
    nodePtr = top;
    while(nodePtr) 
    {
        if (nodePtr->next == NULL) break;
        nodePtr = nodePtr->next;
    }

    //upload files in reverse order
    do
    {
        //upload files
        file << nodePtr->action << endl;
        file << nodePtr->amount << endl;
        file << nodePtr->total << endl;
        file << nodePtr->date << endl;

        //set prevNode to node before nodePtr
        prevNode = top;
        while (prevNode)
        {
            if (prevNode->next == nodePtr || prevNode->next == NULL) break;
            prevNode = prevNode->next;
        }

        //set nodePtr to previous node then start again
        nodePtr = prevNode;
    } while (nodePtr != top);

    //upload top files
    file << top->action << endl;
    file << top->amount << endl;
    file << top->total << endl;
    file << top->date << endl;
}

//download history from file
void History::downloadHistory(fstream &file)
{
    //temp vars
    string type, date, dummy;
    double num, tot;

    //extract first history which has an extra dummy variable
    getline(file, dummy);
    getline(file, type);
    file >> num;
    file >> tot;
    getline(file, dummy);
    getline(file, date);

    push(type, num, tot, date);

    //extract rest of data and place in list in correct order
    while (file)
    {
        getline(file, type);
        file >> num;
        file >> tot;
        getline(file, dummy);
        getline(file, date);

        push(type, num, tot, date);
    }

    //delete weird extra node
    top = top->next;
}

#endif