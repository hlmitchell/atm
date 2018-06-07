#include "inputError.h"

void InputError::checkForValidPinEntry(string &pinEntry)
{
    bool pinIsAllInts = true;

    do
    {
        //make sure characters are all ints
        for (int i = 0; i < pinEntry.length(); i++)
        {
            if (pinEntry[i] < ZERO || pinEntry[i] > NINE)
                pinIsAllInts = false;
        }

        //if pin length isn't 4 then reprompt
        if (pinEntry.length() != PIN_LENGTH || pinIsAllInts == false)
        {
            cout << "Invalid Entry. Please try again: ";
            getline(cin, pinEntry);

            pinIsAllInts = true;
            for (int i = 0; i < pinEntry.length(); i++)
            {
                if (pinEntry[i] < ZERO || pinEntry[i] > NINE)
                    pinIsAllInts = false;
            }
        }
    } while(pinEntry.length() != PIN_LENGTH || pinIsAllInts == false);
}

void InputError::checkForValidIDEntry(string &idEntry)
{
    ofstream tempFile;

    removeExtraWhiteSpaceFromString(idEntry);
    string fileName = idEntry + ".txt";

    //check to see if open, otherwise change id
    tempFile.open(fileName.c_str(), ios::in);
    
    //while file opens successfully, ask for a different username
    while (!tempFile.fail())
    {
        tempFile.close();
        cout << "Username has already been taken! Please try again: ";
        getline(cin, idEntry);
        removeExtraWhiteSpaceFromString(idEntry);
        fileName = idEntry + ".txt";
        tempFile.open(fileName.c_str());
    }

    tempFile.close();
}

//checks string for input and white space
void InputError::removeExtraWhiteSpaceFromString(string &userEntry)
{
    while (userEntry == "")
    {
        cout << "Nothing submitted! Please try again: ";
        getline(cin, userEntry);
    }

    //temporary holders for string as it will be reversed and then reversed again to remove white space
    string tempStrBackward, tempStrForward;

    //delete right white space
    for (int i = userEntry.length() - 1; i >= 0; i--)
    {
        if (userEntry[i] != ' ')
        {
            for (int j = i; j >= 0; j--)
            {
                tempStrBackward += userEntry[j];
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
    
    userEntry = tempStrForward;
}

//clears field to prevent menu skipping
void InputError::clearKeyboardBuffer()
{
    //clears field to prevent menu skipping
    cin.clear();
    cin.ignore(1000, '\n');
}

//validates yes or no input
void InputError::yesOrNoValidator(char &yORn)
{
    clearKeyboardBuffer();
    
    //change lower case to upper
    if (yORn == 'y') yORn = 'Y';
    else if (yORn == 'n') yORn = 'N';

    //if user has not entered y or n then reprompt
   while ((yORn != 'Y') && (yORn != 'N'))
    {
        cout << "Invalid Entry. Please try again: ";
        cin >> yORn;
        if (yORn == 'y') yORn = 'Y';
        else if (yORn == 'n') yORn = 'N';
        clearKeyboardBuffer();
    }
}

