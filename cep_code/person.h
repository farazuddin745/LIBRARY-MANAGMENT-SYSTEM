#ifndef PERSON_H
#define PERSON_H

#include <string>
using namespace std;

class person
{
public:
    string name;
    string email;
protected:
    string password;

    virtual void registerSelf() = 0; // pure virtual
    virtual void showMenu() = 0;     // pure virtual

    virtual ~person() {}
};

#endif
