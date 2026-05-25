#include "helpers.h"
#include <algorithm>
#include <cctype>
using namespace std;

// Convert a string to all lowercase letters
string toLower(string s)
{
    transform(s.begin(), s.end(), s.begin(), ::tolower);
/*
    s.begin()  where to start reading from (first character)
s.end()  where to stop reading (last character)
s.begin()  where to write the result back to (same string, overwriting in place)
::tolower  the operation to apply on each character
*/
    return s;
}

// Check if a string has any digit (number) in it
bool hasDigit(const string &s)
{
    for (int i = 0; i < s.size(); i++)
    {
        if (isdigit(s[i]))
            return true;
    }
    return false;
}

// Check if a string is a valid number (all digits, no letters)
bool isNumber(const string &s)
{
    if (s.empty()) return false;
    for (int i = 0; i < s.size(); i++)
    {
        if (!isdigit(s[i]))
            return false;
    }
    return true;
}