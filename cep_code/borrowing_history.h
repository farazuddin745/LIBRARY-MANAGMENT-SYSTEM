#ifndef BORROWING_HISTORY_H
#define BORROWING_HISTORY_H

#include <iostream>
#include <string>
#include <ctime>
using namespace std;

class borrowing_history
{
public:
    string bookTitle;
    string isbn;
    time_t borrowDate = 0;
    time_t returnDate = 0;
    time_t dueDate = 0;

    bool returned = false;

    void fine(int &balance);

    bool operator==(const borrowing_history &other) const;

    friend ostream &operator<<(ostream &out, const borrowing_history &h);
};

#endif
