#ifndef accounts_h
#define accounts_h

#include <string>
#include <vector>
#include <iostream>
#include "inputError.h"

using namespace std;

class AccountNode
{
public:
    bool accountType;   //true is checking, false is savings
    string accountName;
    double accountFunds;
    //history
    
    AccountNode *leftChild, *rightChild;
    
    AccountNode(bool AT, string AN)
    { accountType = AT; accountName = AN; accountFunds = 0;
        leftChild = NULL; rightChild = NULL;}
};

class AccountsTree
{
public:
    AccountsTree() {mRoot = NULL;}
    ~AccountsTree() {clearAccounts(mRoot);}
    
    //interface
    void createAnAccount();
    void selectAnAccount();
    void displayAccountMenuOptions();
    vector<string> &getFileNames(vector<string> &);
    void accessAccountFile(const string&);
    
    // for exception throwing
    class EmptyTreeException {};
    class NotFoundException {};
    
private:
    AccountNode *mRoot;
    InputError inputErrorCatcher;
    
    bool insert(const bool, const string);
    bool remove(const string);
    bool contains(const string);
    const string &find(const string);
    void uploadAccountData(AccountNode *&);
    string convertToFileName(const string &);
    
    void splay(AccountNode *&, const string);
    void rotateWithLeftChild(AccountNode *&);
    void rotateWithRightChild(AccountNode *&);
    
    //recursive methods
    void clearAccounts(AccountNode *&);
    void printNames(AccountNode *&);
    void getFileNames(AccountNode *&, vector<string>&);
};

#endif /* FHsplayTree_h */
