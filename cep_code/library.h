#ifndef LIBRARY_H//Header guard to prevent multiple copies of the same class being compliled and cause function redefinition errors. It checks if LIBRARY_H is not defined, and if so, it defines it and includes the contents of the file. If LIBRARY_H is already defined, it skips the contents of the file.
#define LIBRARY_H

#include "book.h"
#include "user.h"
#include "admin.h"
#include <vector>
using namespace std;

class library
{
private:
//it shows aggregation relationship between library and book,user,admin classes as library class contains vector of book,user and admin objects,even if library is destroyed but the book,user and admin objects will still exist
    vector<book> books;     // A vector to store the collection of books in the library.
    vector<user> users;//same objective as above
    vector<admin> admins;//same objective as above

public:
    library();
    void displayMenu();
    ~library();
};

#endif
