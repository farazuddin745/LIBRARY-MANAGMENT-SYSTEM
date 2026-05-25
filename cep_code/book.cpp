#include "book.h"
#include "helpers.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdexcept>
using namespace std;

bool book::operator==(const book &other) const
{
    return isbn == other.isbn;//other.isbn is the isbn of the book object which is passed as parameter to compare with the isbn of the current book object,if they are same then return true else return false
}

bool book::operator!=(const book &other) const
{
    return isbn != other.isbn;//isbn is of current book object and other.isbn is the one being compared 
}

ostream &operator<<(ostream &out, const book &b)//used in functions like view_books and search_book to print the details of book object in a formatted way 
{
    out << "Title: " << b.title << endl;
    out << "Author: " << b.author << endl;
    out << "ISBN: " << b.isbn << endl;
    out << "Genre: " << b.category << endl;
    out << "Publication Year: " << b.publicationYear << endl;
    out << "Available Copies: " << b.availableCopies << endl;
    out << "Status: " << (b.availability ? "Available" : "Not Available") << endl;
    return out;// return the output stream after printing the details of book object b in a formatted way s and allows chaining
}

istream &operator>>(istream &in, book &b)
{
    in >> b.title >> b.author >> b.isbn >> b.publicationYear >> b.availableCopies >> b.category >> b.availability;
    return in;
}

void book::load_books(vector<book> &books)//send the vector of books in library class by reference to load the data of books from file into that vector and it is static because we want to call this function without creating an object of book class
{
    books.clear();
    ifstream file("books.txt");
    if (file.is_open())
    {
        book b;
        while (file >> b.title >> b.author >> b.isbn >> b.publicationYear >> b.availableCopies >> b.category >> b.availability)
        {
            replace(b.title.begin(), b.title.end(), '_', ' ');
            replace(b.author.begin(), b.author.end(), '_', ' ');
            books.push_back(b);
        }
        file.close();
    }
}

void book::save_books(const vector<book> &books)
{
    ofstream file("books.txt");
    for (int i = 0; i < books.size(); i++)
    {
        const book &b = books[i];
        string titleToSave = b.title;
        string authorToSave = b.author;
        replace(titleToSave.begin(), titleToSave.end(), ' ', '_');
        replace(authorToSave.begin(), authorToSave.end(), ' ', '_');

        file << titleToSave << " "
             << authorToSave << " "
             << b.isbn << " "
             << b.publicationYear << " "
             << b.availableCopies << " "
             << b.category << " "
             << b.availability << "\n";
    }
    file.close();
}

void book::view_books(vector<book> &books)
{
    load_books(books);
    if (books.empty())
    {
        cout << "\nNo books available.\n";
        return;
    }
    cout << endl
         << "================ AVAILABLE BOOKS ================" << endl;
    int count = 1;
    for (int i = 0; i < books.size(); i++)
    {
        book &b = books[i];
        if (b.availability)
        {
            cout << "\nBook " << count++ << endl;
            cout << b;//operator overloading used here to print the details of book object b in a formatted way by overloading the << operator for book class and it takes the book object as parameter and prints the details of that book in a formatted way
        }
    }
}

void book::search_book(vector<book> &books)
{
    load_books(books);
    string keyword;
    cout << "\nEnter title / author / ISBN: ";
    cin.ignore();
    getline(cin, keyword);

    string keywordLower = toLower(keyword);

    bool found = false;
    for (int i = 0; i < books.size(); i++)
    {
        book &b = books[i];
        if (toLower(b.title) == keywordLower ||
            toLower(b.author) == keywordLower ||
            toLower(b.isbn) == keywordLower)
        {
            found = true;
            cout << "\nBook Found!\n";
            cout << b;
        }
    }
    if (!found)
    {
        cout << "No matching book found!\n";
    }
}

void book::search_by_genre(vector<book> &books)
{
    load_books(books);
    string genre;
    cout << "\nEnter genre: ";
    cin >> genre;

    string genreLower = toLower(genre);

    bool found = false;
    for (int i = 0; i < books.size(); i++)
    {
        book &b = books[i];
        if (toLower(b.category) == genreLower)
        {
            found = true;
            cout << "\nTitle: " << b.title << endl;
            cout << "Author: " << b.author << endl;
            cout << "ISBN: " << b.isbn << endl;
            cout << "Available Copies: " << b.availableCopies << endl;
        }
    }
    if (!found)
    {
        cout << "No books found in this genre!\n";
    }
}

void book::add_book(vector<book> &books)
{
    load_books(books);

    book b;

    cin.ignore();

    cout << "\nEnter title: ";
    getline(cin, b.title);

    while (true)
    {
        cout << "Enter author: ";
        getline(cin, b.author);

        if (hasDigit(b.author))
        {
            try
            {
                throw invalid_argument("Author name must not contain numbers!");
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
        cout << "Enter ISBN: ";
        cin >> b.isbn;

        bool isbnExists = false;

        for (int i = 0; i < books.size(); i++)
        {
            if (books[i].isbn == b.isbn)
            {
                isbnExists = true;
                break;
            }
        }

        if (isbnExists)
        {
            try
            {
                throw invalid_argument("A book with this ISBN already exists!");
            }
            catch (const invalid_argument &e)
            {
                cout << "Error: " << e.what() << endl;
            }
        }
        else if (!isNumber(b.isbn))
        {
            try
            {
                throw invalid_argument("ISBN must contain only numbers!");
            }
            catch (const invalid_argument &e)
            {
                cout << "Error: " << e.what() << endl;
            }
        }
        else if (b.isbn.length() != 10 && b.isbn.length() != 13)
        {
            try
            {
                throw invalid_argument("ISBN must be 10 or 13 digits long!");
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
        string yearInput;

        cout << "Enter publication year: ";
        cin >> yearInput;

        if (!isNumber(yearInput))
        {
            try
            {
                throw invalid_argument("Publication year must be a number!");
            }
            catch (const invalid_argument &e)
            {
                cout << "Error: " << e.what() << endl;
            }
        }
        else
        {
            b.publicationYear = stoi(yearInput);
            break;
        }
    }

    while (true)
    {
        string copiesInput;

        cout << "Enter available copies: ";
        cin >> copiesInput;

        if (!isNumber(copiesInput))
        {
            try
            {
                throw invalid_argument("Available copies must be a number!");
            }
            catch (const invalid_argument &e)
            {
                cout << "Error: " << e.what() << endl;
            }
        }
        else
        {
            b.availableCopies = stoi(copiesInput);
            break;
        }
    }

    while (true)
    {
        cout << "Enter genre: ";
        cin >> b.category;

        if (isNumber(b.category))
        {
            try
            {
                throw invalid_argument("Genre must not be a number!");
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

    b.availability = (b.availableCopies > 0);

    books.push_back(b);

    save_books(books);

    cout << "Book added successfully!\n";
}

void book::remove_book(vector<book> &books)
{
    load_books(books);
    string isbn;
    cout << "Enter ISBN of book to remove: ";
    cin >> isbn;
    for (int i = 0; i < books.size(); i++)
    {
        if (books[i].isbn == isbn)
        {
            books.erase(books.begin() + i);//start in books vector and move i positions to erase the book object at index i from the vector of books in library class
            save_books(books);
            cout << "Book removed successfully!\n";
            return;
        }
    }

    cout << "Book not found!\n";
}

void book::update_book(vector<book> &books)
{
    load_books(books);

    string isbn;

    cout << "\nEnter ISBN of book to update: ";
    cin >> isbn;

    for (int i = 0; i < books.size(); i++)
    {
        if (books[i].isbn == isbn)
        {
            cin.ignore();

            cout << "\n===== UPDATE BOOK =====\n";

            cout << "Enter new title: ";
            getline(cin, books[i].title);

            while (true)
            {
                cout << "Enter new author: ";
                getline(cin, books[i].author);

                if (hasDigit(books[i].author))
                {
                    try
                    {
                        throw invalid_argument("Author name must not contain numbers!");
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
                string yearInput;

                cout << "Enter new publication year: ";
                cin >> yearInput;

                if (!isNumber(yearInput))
                {
                    try
                    {
                        throw invalid_argument("Publication year must be a number!");
                    }
                    catch (const invalid_argument &e)
                    {
                        cout << "Error: " << e.what() << endl;
                    }
                }
                else
                {
                    books[i].publicationYear = stoi(yearInput);
                    break;
                }
            }

            while (true)
            {
                string copiesInput;

                cout << "Enter new available copies: ";
                cin >> copiesInput;

                if (!isNumber(copiesInput))
                {
                    try
                    {
                        throw invalid_argument("Available copies must be a number!");
                    }
                    catch (const invalid_argument &e)
                    {
                        cout << "Error: " << e.what() << endl;
                    }
                }
                else
                {
                    books[i].availableCopies = stoi(copiesInput);
                    break;
                }
            }

            while (true)
            {
                cout << "Enter new genre: ";
                cin >> books[i].category;

                if (isNumber(books[i].category))
                {
                    try
                    {
                        throw invalid_argument("Genre must not be a number!");
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

            books[i].availability = (books[i].availableCopies > 0);//

            save_books(books);

            cout << "\nBook updated successfully!\n";

            return;
        }
    }

    cout << "Book not found!\n";
}
