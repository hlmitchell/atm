#ifndef accounts_h
#define accounts_h

#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include "inputError.h"
#include "history.h"

using namespace std;

class AccountNode
{
public:
    bool accountType;   //true is checking, false is savings
    string accountName;
    double accountFunds;
    History myHistory;
    
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
    
    //account specific interface
    void displayAccountMenuOptions();
    void displayMenuInterface(int &);
    void withdrawFunds();
    void depositFunds();
    void transferFunds();
    void deleteAccount();
    void selectTransferAccount(const AccountNode *&);
    
    //tree splaying methods
    void splay(AccountNode *&, const string);
    void rotateWithLeftChild(AccountNode *&);
    void rotateWithRightChild(AccountNode *&);
    
    //recursive methods
    void clearAccounts(AccountNode *&);
    void printAllNames(AccountNode *&);
    void printSelectNames(AccountNode *&, const string&);
    void getFileNames(AccountNode *&, vector<string>&);
};

#endif /* FHsplayTree_h */
