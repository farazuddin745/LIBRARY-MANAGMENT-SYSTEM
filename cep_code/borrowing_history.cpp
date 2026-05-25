#include "borrowing_history.h"
#include <iostream>
#include <ctime>
using namespace std;

void borrowing_history::fine(int &balance)
{
    if (returned && returnDate > dueDate)
    {
        balance -= 10;//operator overloading used here to deduct fine of Rs.10 from the balance of user if the book is returned late
    }
}

bool borrowing_history::operator==(const borrowing_history &other) const
{
    return isbn == other.isbn && borrowDate == other.borrowDate;//other.isbn and other.borrowDate are the isbn and borrowDate of the borrowing_history object which is passed as parameter to compare with the isbn and borrowDate of the current borrowing_history object currently logged in and if they are same then return true else return false
}

ostream &operator<<(ostream &out, const borrowing_history &h)//it is used in user.cpp user::view_history function to print the borrowing history of the user in a readable format by overloading the << operator for borrowing_history class and it takes the borrowing_history object as parameter and prints the details of that borrowing history in a readable format and returns the output stream
{
    out << "Book: " << h.bookTitle << endl;
    out << "ISBN: " << h.isbn << endl;
    out << "Borrow Date: " << ctime(&h.borrowDate);
    out << "Due Date: " << ctime(&h.dueDate);

    if (h.returned)
    {
        out << "Return Date: " << ctime(&h.returnDate);
    }
    else
    {
        out << "Not Returned Yet\n";
    }

    return out;
}
