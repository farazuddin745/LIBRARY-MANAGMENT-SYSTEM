#include "library.h"
#include <iostream>
using namespace std;

library::library()
{
    cout << "==================== WELCOME TO LIBRARY SYSTEM ====================\n";
    //load the data of users,book,admin and borrow_history from the file into the vector of users in the library class
    book::load_books(books);
    user::load_users(users);        
    admin::load_admins(admins);
    user::load_borrowing_history(users);
    displayMenu();
}

void library::displayMenu()
{
    while (true)
    {
        cout << "\n================ MENU ================\n";

        cout << "1. User Login\n";
        cout << "2. User Register\n";
        cout << "3. Admin Login\n";
        cout << "4. Admin Register\n";
        cout << "5. Exit\n";
        int choice;
        cout << "Enter choice: ";
        cin >> choice;
              
        switch (choice)
        {
        case 1:
            user::user_login(users, books);
            break;
        case 2:
            user::register_user(users);
            break;
        case 3:
            admin::admin_login(admins, books, users);
            break;
        case 4:
            admin::register_admin(admins);
            break;
        case 5:
            cout << "Exiting...\n";
            return;
        default:
            cout << "Invalid choice!" << endl;
        }
    }
}

library::~library()
{
    //save the data of users,book,admin and borrow_history from the vector in the library class into the file
    book::save_books(books);
    user::save_users(users);
    admin::save_admins(admins);
    user::save_borrowing_history(users);
}
