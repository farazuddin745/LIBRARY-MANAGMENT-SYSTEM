#include "admin.h"
#include "helpers.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdexcept>
using namespace std;

// ---- Operator Overloading ----

bool admin::operator==(const admin &other) const
{
    return adminID == other.adminID;
}

// ---- registerSelf ----

void admin::registerSelf()//over-ridede function
{
    cout << "\n===== REGISTER AS ADMIN =====\n";

    cin.ignore();

    while (true)
    {
        cout << "Enter name: ";
        getline(cin, name);

        if (hasDigit(name))
        {
            try
            {
                throw invalid_argument("Name must not contain any numbers! Example: Sara Ahmed");
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
}

// ---- showMenu ----

void admin::showMenu()
{
    cout << "\n===== ADMIN MENU =====\n";

    cout << "1. View Books\n";
    cout << "2. Add Book\n";
    cout << "3. Remove Book\n";
    cout << "4. Update Book\n";
    cout << "5. View All Users\n";
    cout << "6. View Borrowing Reports\n";
    cout << "7. View Issued Books\n";
    cout << "8. Logout\n";
}

// ---- Load / Save Admins ----

void admin::load_admins(vector<admin> &admins)
{
    admins.clear();
    ifstream file("admins.txt");
    if (file.is_open())
    {
        admin a;
        while (file >> a.adminID >> a.name >> a.email >> a.password)
        {
            replace(a.name.begin(), a.name.end(), '_', ' ');
            admins.push_back(a);
        }
        file.close();
    }
}

void admin::save_admins(const vector<admin> &admins)
{
    ofstream file("admins.txt");
    for (int i = 0; i < admins.size(); i++)
    {
        const admin &a = admins[i];
        string nameToSave = a.name;
        replace(nameToSave.begin(), nameToSave.end(), ' ', '_');

        file << a.adminID << " "
             << nameToSave << " "
             << a.email << " "
             << a.password
             << "\n";
    }
    file.close();
}

// ---- Register Admin ----

void admin::register_admin(vector<admin> &admins)
{
    load_admins(admins);

    admin a;

    a.registerSelf();

    for (int i = 0; i < admins.size(); i++)
    {
        if (admins[i].name == a.name)
        {
            try
            {
                throw invalid_argument("An admin with this name already exists! Please choose a different name.");
            }
            catch (const invalid_argument &e)
            {
                cout << "Error: " << e.what() << endl;
                cout << "Registration cancelled. Please try again.\n";
                return;
            }
        }
    }

    a.adminID = admins.size() + 1;

    admins.push_back(a);

    save_admins(admins);

    cout << "Admin registered successfully!\n";
}

// ---- Admin Session ----

void admin::admin_session(vector<book> &books, vector<user> &users)
{
    while (true)
    {
        showMenu();

        int choice;

        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            book::view_books(books);
            break;

        case 2:
            book::add_book(books);
            break;

        case 3:
            book::remove_book(books);
            break;

        case 4:
            book::update_book(books);
            break;

        case 5:
            user::view_users(users);
            break;

        case 6:
            user::borrowing_report(users);
            break;

        case 7:
            user::issued_books(users);
            break;

        case 8:
            cout << "Logging out...\n";
            return;

        default:
            cout << "Invalid choice!\n";
        }
    }
}

// ---- Admin Login ----

bool admin::admin_login(vector<admin> &admins, vector<book> &books, vector<user> &users)
{
    load_admins(admins);

    string email;
    string password;

    cout << "\n================ LOGIN AS ADMIN ================\n";

    cout << "Enter admin email: ";
    cin >> email;

    cout << "Enter admin password: ";
    cin >> password;

    for (int i = 0; i < admins.size(); i++)
    {
        admin &a = admins[i];

        if (a.email == email &&
            a.password == password)
        {
            cout << "Admin login successful!\n";

            a.admin_session(books, users);

            return true;
        }
    }

    cout << "Invalid credentials!\n";

    return false;
}
