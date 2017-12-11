#include "inputError.h"

InputError::InputError()
{
    userSelection = 0;
}

//choose account type for menu options
int InputError::chooseAccountType()
{   
    cout << endl;
    //display part of menu and check bounds
    cout << endl;
    cout << "1. Checking" << endl;
    cout << "2. Savings" << endl;
    cout << "3. Back" << endl;
    cin >> userSelection;
    boundsCheck(userSelection, 1, 3);
    return userSelection;
}

//checks that pin is length of 4 and valid
void InputError::checkPin(string &p)
{
    bool valid = true;

    do
    {
        //make sure characters are all ints
        for (int i = 0; i < p.length(); i++)
        {
            if (p[i] < '0' || p[i] > '9')
                valid = false;
        }

        //if pin length isn't 4 then reprompt
        if (p.length() != 4 || valid == false)
        {
            cout << "Invalid Entry. Please try again: ";
            getline(cin, p);

            valid = true;
            for (int i = 0; i < p.length(); i++)
            {
                if (p[i] < '0' || p[i] > '9')
                    valid = false;
            }
        }
    } while(p.length() != 4 || valid == false);
}

//checks for new user ID
void InputError::checkID(string &name)
{
    ofstream tempFile;
    checkString(name);

    //converts to file name
    string fileName = name + ".txt";

    //check to see if open, otherwise change id
    tempFile.open(fileName.c_str(), ios::in);
    
    //while file opens successfully, ask for a different username
    while (!tempFile.fail())
    {
        tempFile.close();
        cout << "Username has already been taken! Please try again: ";
        getline(cin, name);
        checkString(name);
        fileName = name + ".txt";
        tempFile.open(fileName.c_str());
    }

    tempFile.close();
}

//checks string for input and white space
void InputError::checkString(string &words)
{
    while (words == "")
    {
        cout << "Nothing submitted! Please try again: ";
        getline(cin, words);
    }

    //temp words2
    string tempStrBackward, tempStrForward;

    //delete right white space
    for (int i = words.length() - 1; i >= 0; i--)
    {
        if (words[i] != ' ')
        {
            for (int j = i; j >= 0; j--)
            {
                tempStrBackward += words[j];
            }
            break;   
        }
    }

    //delete left white space
    for (int i = tempStrBackward.length() - 1; i >= 0; i--)
    {
        if (tempStrBackward[i] != ' ')
        {
            for (int j = i; j >= 0; j--)
            {
                tempStrForward += tempStrBackward[j];
            }
            break;   
        }
    }
    
    words = tempStrForward;
}

//clears field to prevent menu skipping
void InputError::clearField()
{
    //clears field to prevent menu skipping
    cin.clear();
    cin.ignore(1000, '\n');
}

//validates yes or no input
void InputError::yesNo(char &x)
{
    clearField();
    
    //change lower case to upper
    if (x == 'y') x = 'Y';
    else if (x == 'n') x = 'N';

    //if user has entered y or n then reprompt
   while ((x != 'Y') && (x != 'N'))
    {
        cout << "Invalid Entry. Please try again: ";
        cin >> x;
        if (x == 'y') x = 'Y';
        else if (x == 'n') x = 'N';
        clearField();
    }
}

