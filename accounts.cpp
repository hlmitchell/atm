#include "accounts.h"

// public interface-------------------------------------------
void AccountsTree::createAnAccount()
{
    int menuSelector;
    string name;
    
    cout << "\nWhat type of account would you like to create?" << endl << endl;
    cout << "1. Checking" << endl;
    cout << "2. Savings" << endl;
    cout << "3. Back" << endl;
    
    cin >> menuSelector;
    inputErrorCatcher.checkForValidUserInput(menuSelector, 1, 3);
    inputErrorCatcher.clearKeyboardBuffer();
    if (menuSelector == 3) return;
    
    cout << "\nWhat would you like to name the account?" << endl;
    
    do {
        getline(cin, name);
        inputErrorCatcher.removeExtraWhiteSpaceFromString(name);
        
        if (contains(name))
            cout << "Name already taken! Try again: ";
        
    } while (contains(name));
    
    switch (menuSelector) {
        case 1:
            insert(true, name);
            break;
        case 2:
            insert(false, name);
            break;
        default:
            return;
    }
}

void AccountsTree::selectAnAccount()
{
    if (mRoot == NULL) {
        cout << endl << "You have not created an account yet!" << endl;
        return;
    }
    
    string name;
    cout <<  "\nWhich account would you like to access?" << endl;
    
    printNames(mRoot);
    
    getline(cin, name);
    inputErrorCatcher.removeExtraWhiteSpaceFromString(name);
    
    if (contains(name)) displayAccountMenuOptions();
    else cout << "Not a valid account name!" << endl << endl;
}

void AccountsTree::displayAccountMenuOptions()
{
    int userSelection;
    
    do {
        displayMenuInterface(userSelection);
        
        switch(userSelection)
        {
            case 1:
                withdrawFunds();
                break;
            case 2:
                depositFunds();
                break;
            case 3:
                transferFunds();
                break;
            case 4:
                //pointerToActiveAccount->myHistory.displayHistory();
                break;
            case 5:
                deleteAccount();
                return;
            default:
                break;
        }
        if (mRoot == NULL) userSelection = 6;
        
    } while (userSelection != 6);
    
    userSelection = 0;
}
    
void AccountsTree::displayMenuInterface(int &userSelection)
{
    cout << endl << "Current Account: " << mRoot->accountName << endl;
    cout << "Account Type: ";
    if (mRoot->accountType == 1) cout << "Checking" << endl;
    else cout << "Savings" << endl;
    cout << "Account Funds: $" << mRoot->accountFunds << endl;
    
    cout << endl << "*** " << mRoot->accountName << " Options ***" << endl;
    cout << "1. Withdraw" << endl;
    cout << "2. Deposit" << endl;
    cout << "3. Transfer Money" << endl;
    cout << "4. Display Account History" << endl;
    cout << "5. Delete Account" << endl;
    cout << "6. Back" << endl;
    
    cin >> userSelection;
    inputErrorCatcher.checkForValidUserInput(userSelection, 1, 6);
    inputErrorCatcher.clearKeyboardBuffer();
}

void AccountsTree::withdrawFunds()
{
    double withdrawAmount;
    cout << endl << "How much would you like to withdraw? ";
    cin >> withdrawAmount;
    inputErrorCatcher.checkForValidUserInput
                                    (withdrawAmount, 0.0, mRoot->accountFunds);
    mRoot->accountFunds -= withdrawAmount;
    cout << fixed << setprecision(2);
    cout << "Successfully withdrew $" << withdrawAmount << endl;
    //history
}

void AccountsTree::depositFunds()
{
    double depositAmount;
    cout << endl << "How much would you like to deposit? ";
    cin >> depositAmount;
    inputErrorCatcher.checkForValidUserInput
                                    (depositAmount, 0.0, 100000000000.0);
    mRoot->accountFunds += depositAmount;
    cout << fixed << setprecision(2);
    cout << "Successfully deposited $" << depositAmount << endl;
    //history
}

void AccountsTree::transferFunds()
{
    string transferAccount;
    const AccountNode *currentNode = mRoot;
    double transferAmount;
    
    selectTransferAccount(currentNode);
    cout << endl << "How much would you like to transfer? ";
    cin >> transferAmount;
    inputErrorCatcher.checkForValidUserInput
                                    (transferAmount, 0.0, mRoot->accountFunds);
    mRoot->accountFunds += transferAmount;
    splay(mRoot, currentNode->accountName);
    mRoot->accountFunds -= transferAmount;
    
    cout << fixed << setprecision(2);
    cout << "Successfully transfered $" << transferAmount << endl;
    //history
}

void AccountsTree::displayAccountHistory()
{
    //history stuff
}

void AccountsTree::deleteAccount()
{
    char userSelection;
    const AccountNode *currentNode = mRoot;
    
    cout << "Are you sure you want to delete " << mRoot->accountName
    << "? (Y/N) ";
    cin >> userSelection;
    inputErrorCatcher.yesOrNoValidator(userSelection);
    if (userSelection == 'N') return;
    
    if (mRoot->leftChild == NULL && mRoot->rightChild == NULL)
        cout << "Successfully withdrew $" << mRoot->accountFunds << endl;

    else if (mRoot->accountFunds != 0) {
        selectTransferAccount(currentNode);
        
        cout << "Successfully transfered $" << currentNode->accountFunds
        << " to " << mRoot->accountName << endl;
        mRoot->accountFunds += currentNode->accountFunds;
    }
    
    cout << "Successfully deleted " << currentNode->accountName << endl;
    remove(currentNode->accountName);
}

void AccountsTree::selectTransferAccount(const AccountNode *&currentNode)
{
    string transferAccount;
    
    do {
        cout << endl << "To which account would you like to transfer funds?"
        << endl;
        printNames(mRoot);
        getline(cin, transferAccount);
        inputErrorCatcher.removeExtraWhiteSpaceFromString(transferAccount);
        
        if (!contains(transferAccount) ||
            transferAccount == currentNode->accountName) {
            cout << "Not a valid option!" << endl;
        }
    } while (!contains(transferAccount) ||
             transferAccount == currentNode->accountName);
}

vector<string> &AccountsTree::getFileNames(vector<string> &fileNames)
{
    fileNames.clear();
    
    if (mRoot == NULL)
        return fileNames;
    
    getFileNames(mRoot, fileNames);
    return fileNames;
}

void AccountsTree::accessAccountFile(const string &textFileName)
{
    fstream accountFile;
    bool accountType;
    string accountName;
    accountFile.open(textFileName.c_str(), ios::in);
    
    if (accountFile)
    {
        getline(accountFile, accountName);
        accountFile >> accountType;
        insert(accountType, accountName);
        accountFile >> mRoot->accountFunds;
        //history access
        
        accountFile.close();

    } else {
        cout << endl << "Problem locating " + textFileName + "..." << endl;
        cout << "Deleting..." << endl;
    }
}

//private methods---------------------------------------------
bool AccountsTree::insert(const bool type, const string name)
{
    if (mRoot == NULL)
    {
        mRoot = new AccountNode(type, name);
        return true;
    }
    
    splay(mRoot, name);
    
    if (name < mRoot->accountName)
    {
        AccountNode *newNode = new AccountNode(type, name);
        newNode->leftChild = mRoot->leftChild;
        newNode->rightChild = mRoot;
        mRoot = newNode;
        return true;
    }
    else if (mRoot->accountName < name)
    {
        AccountNode *newNode = new AccountNode(type, name);
        newNode->rightChild = mRoot->rightChild;
        newNode->leftChild = mRoot;
        mRoot = newNode;
        return true;
    }
    
    return false;
}

bool AccountsTree::remove(const string name)
{
    if (mRoot == NULL)
        return false;
    
    splay(mRoot, name);
    
    //node doesn't exist
    if (mRoot->accountName < name || name < mRoot->accountName)
        return false;
    
    AccountNode *newRoot = NULL;
    
    //move root easily if no lftChild exists
    if (mRoot->leftChild == NULL)
        newRoot = mRoot->rightChild;
    
    //if lftChild does exist
    else {
        newRoot = mRoot->leftChild;
        splay(newRoot, name);
        newRoot->rightChild = mRoot->rightChild;
    }
    
    delete mRoot;
    mRoot = newRoot;
    
    return true;
}

bool AccountsTree::contains(const string name)
{
    try {
        find(name);
    } catch (...) {
        return false;
    }
    
    return true;
}

const string &AccountsTree::find(const string name)
{
    if (mRoot == NULL)
        throw NotFoundException();
    
    splay(mRoot, name);
    
    if (mRoot->accountName < name || name < mRoot->accountName)
        throw NotFoundException();
    
    return mRoot->accountName;
}

void AccountsTree::uploadAccountData(AccountNode *& accountNode)
{
    string accountFileName = convertToFileName(accountNode->accountName);
    fstream accountFile;
    accountFile.open(accountFileName.c_str(), ios::out);
    
    accountFile << accountNode->accountName << endl;
    accountFile << accountNode->accountType << endl;
    accountFile << accountNode->accountFunds << endl;
    //history
    
    accountFile.close();
}

string AccountsTree::convertToFileName(const string &accountName)
{
    string accountFileName;
    for (int i = 0; i < accountName.length(); i++)
    {
        if (accountName[i] != ' ')
            accountFileName += accountName[i];
        else
            accountFileName += '_';
    }
    accountFileName += ".txt";
    return accountFileName;
}

void AccountsTree::splay(AccountNode *&root, const string name)
{
    AccountNode *rightTree = NULL, *leftTree = NULL;
    AccountNode *rightTreeMin = NULL, *leftTreeMax = NULL;
    
    while (root != NULL)
    {
        if (name < root->accountName)
        {
            if (root->leftChild == NULL)
                break;  //x not in tree
            else if (name < root->leftChild->accountName)
            {
                //zig zig
                rotateWithLeftChild(root);
                if (root->leftChild == NULL)
                    break;  //x not in tree
            }
            
            //add root to right tree
            //update the rightTreeMin to point to this node
            if (rightTree == NULL)
            {
                rightTree = root;
                rightTreeMin = root;
            }
            else {
                rightTreeMin->leftChild = root;
                rightTreeMin = root;
            }
            
            //set mRoot to mRoot's lftChild
            mRoot = root->leftChild;
        }
        
        else if (root->accountName < name)
        {
            if (root->rightChild == NULL)
                break;  //x not in tree
            else if (root->rightChild->accountName < name)
            {
                //zig zig
                rotateWithRightChild(root);
                if (root->rightChild == NULL)
                    break;  //x not in tree
            }
            
            //add root to left tree
            //update the leftTreeMax to point to this node
            if (leftTree == NULL)
            {
                leftTree = root;
                leftTreeMax = root;
            }
            else {
                leftTreeMax->rightChild = root;
                leftTreeMax = root;
            }
            
            //set mRoot to mRoot's rtChild
            mRoot = root->rightChild;
        }
        
        else {
            break;  //found x at root
        }
    } // end of while loop
    
    //reassemble tree
    if (leftTree != NULL)
    {
        //hang root's lftChild on leftTreeMax
        leftTreeMax->rightChild = root->leftChild;
        //set root's lftChild = leftTree
        root->leftChild = leftTree;
    }
    if (rightTree != NULL)
    {
        //hang root's rtChild on rightTreeMin
        rightTreeMin->leftChild = root->rightChild;
        //set root's rtChild = rightTree
        root->rightChild = rightTree;
    }
}

void AccountsTree::rotateWithLeftChild(AccountNode *&k2)
{
    AccountNode *k1 = k2->leftChild;
    k2->leftChild = k1->rightChild;
    k1->rightChild = k2;
    k2 = k1;
}

void AccountsTree::rotateWithRightChild(AccountNode *&k2)
{
    AccountNode *k1 = k2->rightChild;
    k2->rightChild = k1->leftChild;
    k1->leftChild = k2;
    k2 = k1;
}

void AccountsTree::printNames(AccountNode *&node)
{
    if (node == NULL)
        return;
    
    printNames(node->leftChild);
    cout << node->accountName << endl;
    printNames(node->rightChild);
}

void AccountsTree::getFileNames(AccountNode *&node, vector<string> &fileNames)
{
    if (node == NULL)
        return;
    
    getFileNames(node->leftChild, fileNames);
    fileNames.push_back(convertToFileName(node->accountName));
    getFileNames(node->rightChild, fileNames);
}

void AccountsTree::clearAccounts(AccountNode * &subtreeToDelete)
{
    if (subtreeToDelete == NULL)
        return;
    
    // recurse through children and remove
    clearAccounts(subtreeToDelete->leftChild);
    clearAccounts(subtreeToDelete->rightChild);
    
    uploadAccountData(subtreeToDelete);
    
    delete subtreeToDelete;
    subtreeToDelete = NULL;
}
