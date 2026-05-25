#include "user.h"
#include "helpers.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdexcept>
#include <ctime>
using namespace std;

void user::load_users(vector<user> &users)//sending the reference of the vector object 
{
    users.clear();              // clear the vector of user which is in library class
    ifstream file("users.txt"); // inputs the data from file into vector
    if (file.is_open())
    {
        user u; // temporary obj
        while (file >> u.userID >> u.name >> u.email >> u.password >> u.balance >> u.no_of_borrowedBooks)
        {                                                    // read data from file to temporary user object u and then push it to the vector of users in library class
            replace(u.name.begin(), u.name.end(), '_', ' '); // replaces the _ with space in the name of user while loading from file to vector because we saved the name with _ instead of space to avoid issues with reading from file
            users.push_back(u);
        }
        file.close();
    }
}

void user::load_borrowing_history(vector<user> &users)
{ 
    // load the borrowing history of each user into vector of history which is in user class
    ifstream file("history.txt");
    if (file.is_open())
    { // temp userID and h
        int userID;
        borrowing_history h;
        while (file >> userID >> h.bookTitle >> h.isbn >> h.borrowDate >> h.dueDate >> h.returnDate >> h.returned)
        {
            replace(h.bookTitle.begin(), h.bookTitle.end(), '_', ' ');

            for (int i = 0; i < users.size(); i++)
            {
                user &u = users[i]; // reference to the user object in the vector of users in library class
                if (u.userID == userID)
                {
                    u.history.push_back(h);
                    if (!h.returned) // if book is not returned then push the isbn of that book into the borrowedBooksISBN vector of user class to keep track of currently borrowed books by the user
                    {
                        u.borrowedBooksISBN.push_back(h.isbn);
                    }
                    break;
                }
            }
        }
        file.close();
    }
}

void user::registerSelf() // over-riding the method of person class
{
    cout << "\n===== REGISTER AS USER =====\n";
    cin.ignore();
    while (true)
    {
        cout << "Enter name: ";
        getline(cin, name);
        if (hasDigit(name))
        {
            try
            {
                throw invalid_argument("Name must not contain any numbers! Example: Ali Hassan");
            }
            catch (const invalid_argument &e)
            {
                cout << "Error: " << e.what() << endl;
            }
        }
        else
        {
            break;
        }
    }
    cout << "Enter email: ";
    cin >> email;
    while (true)
    {
        cout << "Enter password (8 characters minimum): ";
        cin >> password;
        if (password.length() < 8)
        {
            try
            {
                throw invalid_argument("Password must be at least 8 characters long!");
            }
            catch (const invalid_argument &e)
            {
                cout << "Error: " << e.what() << endl;
            }
        }
        else
        {
            break;
        }
    }
    while (true)
    {
        string balanceInput;
        cout << "Enter balance: ";
        cin >> balanceInput;
        if (!isNumber(balanceInput))
        {
            try
            {
                throw invalid_argument("Balance must be a number! Example: 500");
            }
            catch (const invalid_argument &e)
            {
                cout << "Error: " << e.what() << endl;
            }
        }
        else
        {
            int bal = stoi(balanceInput); // balanceinput is a string and converted to int using stoi
            if (bal < 0)
            {
                try
                {
                    throw invalid_argument("Balance must be zero or greater!");
                }
                catch (const invalid_argument &e)
                {
                    cout << "Error: " << e.what() << endl;
                }
            }
            else
            {
                balance = bal;
                break;
            }
        }
    }
}

void user::register_user(vector<user> &users)
{ // the objective of this func is only to check wether a user name already exists
    load_users(users);
    user u;
    u.registerSelf();
    for (int i = 0; i < users.size(); i++)
    {
        if (users[i].name == u.name)
        {
            try
            {
                throw invalid_argument("A user with this name already exists! Please choose a different name.");
            }
            catch (const invalid_argument &e)
            {
                cout << "Error: " << e.what() << endl;
                cout << "Registration cancelled. Please try again.\n";
                return;
            }
        }
    }
    u.userID = users.size() + 1; // users.size()+1 is the new user id and userID is assigned to every new user
    users.push_back(u);
    save_users(users);
    cout << "User registered successfully!\n";
}

bool user::user_login(vector<user> &users, vector<book> &books)
{
    load_users(users);
    load_borrowing_history(users);
    string email;
    string password;
    cout << endl << "================ LOGIN AS USER ================" << endl;
    cout << "Enter email: ";
    cin >> email;
    cout << "Enter password: ";
    cin >> password;
    for (int i = 0; i < users.size(); i++)
    {
        user &u = users[i]; // temp object
        if (u.email == email && u.password == password)     
        {
            cout << "Login successful!\n";
            user_session(u, books, users);
            return true; // if email and password true then return true and end the func
        }
    }
    cout << "Invalid credentials!\n";
    return false; // return false means login failed and true means login successful and user session started
}

void user::showMenu()
{
    cout << "\n===== USER MENU =====\n";

    cout << "1. View Available Books\n";
    cout << "2. Search Book\n";
    cout << "3. Search By Genre\n";
    cout << "4. Borrow Book\n";
    cout << "5. Return Book\n";
    cout << "6. View Borrowing History\n";
    cout << "7. View Balance\n";
    cout << "8. Update Balance\n";
    cout << "9. Logout\n";
}

void user::user_session(user &u, vector<book> &books, vector<user> &users)
{
    while (true)
    {
        u.showMenu();
        int choice;
        cout << "Enter choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            book::view_books(books);
            break;
        case 2:
            book::search_book(books);
            break;
        case 3:
            book::search_by_genre(books);
            break;
        case 4:
            u.borrow_book(books, users);
            break;
        case 5:
            u.return_book(books, users);
            break;
        case 6:
            u.view_history(users);
            break;
        case 7:
            cout << "Current Balance: Rs. "
                 << u.balance
                 << endl;
            break;
        case 8:
            u.update_balance(users);
            break;
        case 9:
            cout << "Logging out...\n";
            return;
        default:
            cout << "Invalid choice!\n";
        }
    }
}

// ---- Operator Overloading ----

user &user::operator-=(int fine) // return type is user&
{
    balance -= fine;
    return *this; // return *this is returning the object which is a user object with updated balance
}

ostream &operator<<(ostream &out, const user &u)
// it is used in functions like view_users and borrowing_report to print the details of user object in a formatted way
// ostream& out is the output object like cout and const user& u is the user object we want to print
// ostream& is the object that will be outputted after combining out object with the user object u and return it to allow chaining of output operations like cout << user1 << user2;
// the reason it is not member of user class is ebcause ostream&out is object of ostream class and we cant modify a built in class like ostream
{
    out << "Name: " << u.name << endl;
    out << "Email: " << u.email << endl;
    out << "User ID: " << u.userID << endl;
    out << "Balance: " << u.balance << endl;
    out << "Borrowed Books: " << u.no_of_borrowedBooks << endl;
    return out;// return the output stream after printing the details of user object u in a formatted way
}
/*ostream &operator<<(ostream &out, const user &u)
ostream is the class and ostream& is the return type  and out is the reference of ostream object passed which is in this case cout on the left of << and the parameter name was out and u is the reference to the object of class user*/


void user::update_balance(vector<user> &users)
{

    string amountInput;
    cout << "\nCurrent Balance: Rs. " << balance << endl;

    while (true)
    {

        cout << "Enter amount to add: ";
        cin >> amountInput;

        if (!isNumber(amountInput))
        {
            try
            {
                throw invalid_argument("Amount must be a number!");
            }
            catch (const invalid_argument &e)
            {
                cout << "Error: " << e.what() << endl;
            }
        }
        else
        {
            int amount = stoi(amountInput);

            if (amount <= 0)
            {
                try
                {
                    throw invalid_argument("Amount must be greater than zero!");
                }
                catch (const invalid_argument &e)
                {
                    cout << "Error: " << e.what() << endl;
                }
            }
            else
            {
                balance += amount;

                for (int i = 0; i < users.size(); i++)
                {
                    if (users[i].userID == userID) // checks if the userID of currently logged in user matches any of the id in the vector
                    {
                        users[i].balance = balance;
                        break;
                    }
                }

                save_users(users);

                cout << "\nBalance updated successfully!\n";
                cout << "New Balance: Rs. " << balance << endl;

                return;
            }
        }
    }
}

void user::save_users(const vector<user> &users)
{
    ofstream file("users.txt");
    for (int i = 0; i < users.size(); i++)
    {
        const user &u = users[i];
        string nameToSave = u.name;
        replace(nameToSave.begin(), nameToSave.end(), ' ', '_');
        file << u.userID << " "
             << nameToSave << " "
             << u.email << " "
             << u.password << " "
             << u.balance << " "
             << u.no_of_borrowedBooks
             << "\n";
    }
    file.close();
}

void user::save_borrowing_history(const vector<user> &users)
{
    ofstream file("history.txt");
    for (int i = 0; i < users.size(); i++)
    {
        const user &u = users[i];
        for (int j = 0; j < u.history.size(); j++)
        { 
            const borrowing_history &h = u.history[j];
            string titleToSave = h.bookTitle;
            replace(titleToSave.begin(), titleToSave.end(), ' ', '_');

            file << u.userID << " "
                 << titleToSave << " "
                 << h.isbn << " "
                 << h.borrowDate << " "
                 << h.dueDate << " "
                 << h.returnDate << " "
                 << h.returned
                 << "\n";
        }
    }
    file.close();
}

// ---- Borrow Book ----

void user::borrow_book(vector<book> &books, vector<user> &users)
{
    book::load_books(books);
    borrowedToday = 0;
    time_t currentTime = time(0);
    for (int i = 0; i < history.size(); i++)
    {
        borrowing_history &h = history[i];
        double seconds = difftime(currentTime, h.borrowDate);
        if (seconds <= 86400)
        {
            borrowedToday++;
        }
    }
    if (borrowedToday >= 2)
    {
        cout << "\nYou cannot borrow more than 2 books in one day!\n";
        return;
    }
    string keyword;
    cout << "\nEnter title / ISBN to borrow: ";
    cin.ignore();
    getline(cin, keyword);
    string keywordLower = toLower(keyword);
    for (int i = 0; i < books.size(); i++)
    {
        book &b = books[i];
        if ((toLower(b.title) == keywordLower ||
             toLower(b.isbn) == keywordLower) &&
            b.availableCopies > 0)
        {
            b.availableCopies--;

            if (b.availableCopies == 0)
            {
                b.availability = false;
            }

            no_of_borrowedBooks++;

            borrowedBooksISBN.push_back(b.isbn);

            borrowing_history h;

            h.bookTitle = b.title;
            h.isbn = b.isbn;

            h.borrowDate = time(0);
            h.dueDate = h.borrowDate + (7 * 24 * 60 * 60);
            h.returned = false;

            history.push_back(h);

            for (int j = 0; j < users.size(); j++)
            {
                user &usr = users[j]; //

                if (usr.userID == userID)
                {
                    usr = *this;//replaces the old user usr with *this , the current updated object 
                    break;
                }
            }

            book::save_books(books);
            save_users(users);
            save_borrowing_history(users);

            cout << "\nBook borrowed successfully!\n";

            return;
        }
    }

    cout << "Book not available!\n";
}

// ---- Return Book ----

void user::return_book(vector<book> &books, vector<user> &users)
{
    book::load_books(books);
    if (borrowedBooksISBN.empty())
    {
        cout << "\nNo borrowed books!\n";
        return;
    }
    cout << "\n===== YOUR BORROWED BOOKS =====\n";

    for (int i = 0; i < borrowedBooksISBN.size(); i++)
    {
        cout << i + 1 << ". "
             << borrowedBooksISBN[i]
             << endl;
    }

    int choice;

    cout << "Select book number to return: ";
    cin >> choice;

    if (choice < 1 || choice > borrowedBooksISBN.size())
    {
        cout << "Invalid choice!\n";
        return;
    }

    string isbn = borrowedBooksISBN[choice - 1];

    for (int i = 0; i < books.size(); i++)
    {
        book &b = books[i];

        if (b.isbn == isbn)
        {
            b.availableCopies++;
            b.availability = true;
            no_of_borrowedBooks--;
            for (int j = 0; j < history.size(); j++)
            {
                borrowing_history &h = history[j];

                if (h.isbn == isbn && h.returned == false)
                {
                    h.returnDate = time(0); // set the return date to current time
                    h.returned = true;

                    h.fine(balance); // calculate fine if the book is returned late and update the balance of user using operator overloading -=

                    break;
                }
            }

            borrowedBooksISBN.erase(borrowedBooksISBN.begin() + choice - 1); // borrowedBooksISBN.begin() is the iterator pointing to the first element of the vector and choice-1 is the index of the book to be removed from the vector after returning it

            for (int j = 0; j < users.size(); j++)
            {
                user &usr = users[j];

                if (usr.userID == userID)
                {
                    usr = *this; // it is used to replace the user object in the vector of users in library class with the updated user object which is currently logged in user with updated balance and borrowing history after returning the book
                    break;
                }
            }
            book::save_books(books);
            save_users(users);
            save_borrowing_history(users);

            cout << "Book returned successfully!\n";

            return;
        }
    }
}

// ---- View Borrowing History ----

void user::view_history(vector<user> &users)
{
    load_users(users);
    load_borrowing_history(users);

    cout << "\n===== BORROWING HISTORY =====\n";

    bool found = false; // to check if the user has any borrowing history or not if found is false after loop then it means no borrowing history and print no borrowing history

    for (int i = 0; i < users.size(); i++)
    {
        user &usr = users[i];

        if (usr.userID == userID)
        {
            for (int j = 0; j < usr.history.size(); j++)
            {
                found = true;
                cout << "\n"
                     << usr.history[j];
            }
        }
    }

    if (!found)
    {
        cout << "No borrowing history!\n";
    }
}

// ---- View All Users (admin use) ----

void user::view_users(vector<user> &users)
{
    load_users(users);
    load_borrowing_history(users);

    if (users.empty())
    {
        cout << "\nNo users registered!\n";
        return;
    }

    cout << "\n===== USERS =====\n";

    for (int i = 0; i < users.size(); i++)
    {
        cout << "\n"
             << users[i]; // operator overlaoding used here
    }
}

// ---- Borrowing Report (admin use) ----

void user::borrowing_report(vector<user> &users)
{
    load_users(users);
    load_borrowing_history(users);

    cout << "\n===== BORROWING REPORT =====\n";

    for (int i = 0; i < users.size(); i++)
    {
        user &u = users[i];
        cout << "\nUSER: " << u.name << endl;
        for (int j = 0; j < u.history.size(); j++)
        {
            borrowing_history &h = u.history[j];

            cout << "\nBook: " << h.bookTitle << endl;

            cout << "Borrow Date: " << ctime(&h.borrowDate); // chagne the large number to a readable time format
            cout << "Due Date: " << ctime(&h.dueDate);

            if (h.returned)
            {
                cout << "Return Date: " << ctime(&h.returnDate);
                cout << "Status: Returned\n";
            }
            else
            {
                cout << "Status: Currently Borrowed\n";
            }
        }
    }
}

// ---- Issued Books (admin use) ----

void user::issued_books(vector<user> &users)
{
    load_users(users);
    load_borrowing_history(users);//load borrowing history to vector of history in user class to check which books are currently borrowed and which are overdue based on the due date and current date

    cout << "\n===== ISSUED BOOKS =====\n";

    for (int i = 0; i < users.size(); i++)
    {
        user &u = users[i];
        for (int j = 0; j < u.history.size(); j++)
        {
            borrowing_history &h = u.history[j];//h is temp reference

            if (!h.returned)
            {
                cout << "\nBook: " << h.bookTitle << endl;
                cout << "Borrowed By: " << u.name << endl;

                if (time(0) > h.dueDate)
                {
                    cout << "OVERDUE\n";
                }
            }
        }
    }
}