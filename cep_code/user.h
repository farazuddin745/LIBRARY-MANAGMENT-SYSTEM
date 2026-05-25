#ifndef USER_H
#define USER_H

#include "person.h"
#include "book.h"
#include "borrowing_history.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

class user : public person//inheritance relation between user and abstract class person 
{
public:
    int userID;
    int no_of_borrowedBooks = 0;
    int balance = 0;
    //for each element of users there isa vector of borrow history object
    vector<borrowing_history> history;      
    //the user borrow history is composition relationship as user class contains vector of borrowing_history objects and if user is destroyed the borrowing history will be destroyed too
    vector<string> borrowedBooksISBN;       //this string

    int borrowedToday = 0;

    user &operator-=(int fine);//used to add fine to the user's balance when they return a book late

    friend ostream &operator<<(ostream &out, const user &u);

    void registerSelf() override;
    void showMenu() override;

    static void user_session(user &u, vector<book> &books, vector<user> &users);//the reason it is static is because we want to call this function without creating an object of user class and it takes the user object which is currently logged in and the vector of books and users in library class to perform the operations related to borrowing and returning books and updating balance and viewing history of the logged in user

    static void load_users(vector<user> &users);
    static void save_users(const vector<user> &users);

    static void load_borrowing_history(vector<user> &users);
    static void save_borrowing_history(const vector<user> &users);
    void update_balance(vector<user> &users);
    void borrow_book(vector<book> &books, vector<user> &users);
    void return_book(vector<book> &books, vector<user> &users);
    void view_history(vector<user> &users);

    static void view_users(vector<user> &users);
    static void borrowing_report(vector<user> &users);
    static void issued_books(vector<user> &users);
    static void register_user(vector<user> &users);
    static bool user_login(vector<user> &users, vector<book> &books);
};

#endif
