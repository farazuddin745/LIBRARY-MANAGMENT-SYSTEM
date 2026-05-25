# LIBRARY-MANAGMENT-SYSTEM
A library management system for University project in C++ based on OOP concepts,

STEPS TO RUN THE PROGRAM : 

THROUGH VS CODE :

1) Extract the file CEPG1-2.ZIP IN YOUR DESIRED FOLDER.
2) OPEN THE FOLDER CEPG1-2 .
3) OPEN THE FOLDER cep_code IN VS CODE .
4) THEN OPEN THE FILE IN VS CODE TERMINAL AND WRITE THE FOLLOWING COMMAND TO COMPILE THE CODE : 
g++ main.cpp helpers.cpp book.cpp borrowing_history.cpp user.cpp admin.cpp library.cpp -o main
Then after it has compiled write in the terminal : 
./main
5)Your Library management system program will run.

THROUGH COMMAND PROMPT : 
1)Open the folder cep_code in cmd and then run this command : 
g++ main.cpp helpers.cpp book.cpp borrowing_history.cpp user.cpp admin.cpp library.cpp -o main
2)Then write : main 


THROUGH DEV C++: 
1. Open Dev-C++
2. Go to File -> New -> Project -> Empty Project -> give it a name -> click OK
3. Go to Project -> Add to Project
4. Add ALL of the following files one by one.
5. Press F11 to Compile and Run

Note:
The program creates these files automatically to store data of user, admin, borrow history and books:
    books.txt, users.txt, admins.txt, history.txt
So please do not delete these files while the program is running

=====================================================================================================================================

OOP CONCEPTS DEMONSTRATED
 
 
1. CLASSES AND OBJECTS
Every major entity is its own class: book, user, admin, borrowing_history,library.Objects are created and used throughout the program
 
2. INHERITANCE
   'user' and 'admin' both inherit from the abstract base class 'person' and they share common attributes: name, email, password
   File: person.h, user.h, admin.h
  
3. ABSTRACT CLASS AND PURE VIRTUAL FUNCTIONS
   'person' is an abstract base class with two pure virtual functions:
       virtual void registerSelf() = 0;
       virtual void showMenu() = 0;
   Both user and admin provide their own implementations
 
4. POLYMORPHISM (Runtime / Dynamic Binding)
  registerSelf() and showMenu() are called on base class pointers.The required version of user or admin would run at runtime.
  File: user.cpp, admin.cpp
 
5. OPERATOR OVERLOADING
   1)book     : == , != , << , >>
   2)user     : += (add fine to balance) , <<
   3)admin    : ==
   4)borrowing_history : == , <<
   5)File: book.cpp, user.cpp, admin.cpp, borrowing_history.cpp
 
6. ENCAPSULATION
   - Each class owns its own data and the methods that work on that data
   - load/save functions are static members of their own class
   - File: all class files
 
7. FILE HANDLING
   Books, users, admins, and borrowing history are all saved to and loaded from .txt files so data persists between runs
 
8. EXCEPTION HANDLING
    invalid_argument exceptions are thrown and caught for all user input.
For example : 
        Author name must not contain numbers
        ISBN must be 10 or 13 digits
        Duplicate ISBN or username not allowed
        Balance must be a non-negative number
        Password must be at least 8 characters

9. VECTORS (Dynamic Arrays)
   All books, users, admins, and borrowing history records are stored in vectors instead of fixed-size arrays
   File: all class files
 
10. STATIC MEMBER FUNCTIONS
    load, save, register, login, and report functions are static so they can be called without creating an object
    File: book.h, user.h, admin.h
 
11. FRIEND FUNCTIONS
    operator<< and operator>> are declared as friend functions so they can access private/public members for clean input/output
    File: book.cpp, borrowing_history.cpp, user.cpp
 
12. SEPARATE COMPILATION (Multi-file Project)
    1)Each class is split into its own .h (header) and .cpp (implementation) file
    2)helpers.h/.cpp contains shared utility functions used across classes
    3)main.cpp only contains user_session() and main()

=====================================================================================================================================

WHAT WORKS

1)User registration and Admin registration with full input validation in which for example if you put a number in your name it will ask to write your name again , password length must be above 8 characters.
2)User login and admin login
3)Add, remove, update, view, and search books
4)Search books by category
5)Borrow book (with daily limit of 2 books per user)
6)Return book with automatic fine calculation (Rs. 10 will be charged if someone returns late)
7)View borrowing history per user
8)View balance option for every user
9)Admin can view all users, borrowing reports, and issued/overdue books
10)All data is saved to files and reloaded on next run
11)Case-insensitive search (e.g. "harry" matches "Harry Potter")
12)If a username of a user or ISBN of a book is already there it will ask to enter again

====================================================================================================================================

WHAT DOES NOT WORK / LIMITATIONS
 
1)Passwords are stored as plain text in .txt files which could be a concern
2)There is not an option for admin to reset a user's password
3)No search feature for admins to find a specific user by name or email
4)Book titles and author names with spaces are stored using underscores as a workaround (e.g. "Harry_Potter") which may look odd in the .txt files because of the reason that 
5)No graphical interface; program runs entirely in the console
