#ifndef ADMIN_H
#define ADMIN_H

#include "person.h"
#include "book.h"
#include "user.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

class admin : public person
{
public:
    int adminID;

    bool operator==(const admin &other) const;

    void registerSelf() override;
    void showMenu() override;

    static void load_admins(vector<admin> &admins);
    static void save_admins(const vector<admin> &admins);
    static void register_admin(vector<admin> &admins);

    void admin_session(vector<book> &books, vector<user> &users);

    static bool admin_login(vector<admin> &admins, vector<book> &books, vector<user> &users);
};

#endif
