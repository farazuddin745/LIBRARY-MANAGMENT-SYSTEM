#ifndef BOOK_H
#define BOOK_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

class book
{
public:
    string title;
    string author;
    string isbn;
    int publicationYear;
    int availableCopies;
    string category;
    bool availability;
    bool issued = false;

    bool operator==(const book &other) const;
    bool operator!=(const book &other) const;

    friend ostream &operator<<(ostream &out, const book &b);
    friend istream &operator>>(istream &in, book &b);

    static void load_books(vector<book> &books);
    static void save_books(const vector<book> &books);
    static void view_books(vector<book> &books);
    static void search_book(vector<book> &books);
    static void search_by_genre(vector<book> &books);
    static void add_book(vector<book> &books);
    static void remove_book(vector<book> &books);
    static void update_book(vector<book> &books);
};

#endif
