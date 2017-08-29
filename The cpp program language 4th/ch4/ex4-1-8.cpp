/**************************************************************
* Name     :  ex4-1-8.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年4月19日
**************************************************************/


/*
example 4.4 : containers
    4.4.2 : list, doubly-linked list

vecter is more efficient than list for short sequences of small elements.

list : a list for sequences where we want to insert and delete elements without moving other elements
    access the elements of a list is not using subscripting. instead, search the list looking for
an element with a given value.  a list is a sequence.
*/


#include <list>
#include <iostream>

using std::cout; using std::cin; using std::cerr;
using std::list;

struct Entry {
    string name;
    int number;
};


ostream& operator<<(ostream& os, const Entry& e)
{
    return os << "{\"" << e.name << "\"," << e.number << "}";
}


// read {"name", number} pair. note : formatted with {"", and }
istream& operator>>(istream& is, Entry& e)
{
    //
    char c, c2;

    // start with {"
    if (is >> c && c == '{' && is >> c2 && c2 == '"') {
        // the default value of a string is an empty string ""
        string name;
        // anything before a " is part of the name
        while (is.get(c) && c != '"') {
            name += c;
            }
        if (is >> c && c == ',') {
            int number = 0;
            // read the number and a '}'
            if (is >> number >> c && c == '}') {
                // assign to the Entry
                e = {name, number};
                return is;
                }
            }
        }

    // register the failure in the stream
    //is.setf(ios_base::failbit);       // error : is.setf(ios_base::fmtflags, ...);
    is.setstate(ios_base::failbit);
    return is;
}   // end operator >>



/*  example 4.4.2 list  */

list<Entry> phone_book = {
    { "David Hume", 123456},
    {"Karl Popper", 234567},
    {"Bertrand Arthur William Russell", 345678}
};

/*  access elements of a list  */
int get_number(const string& s)
{
    for (const auto& x : phone_book) {
        if (x.name == s) {
            return x.number;
        }
    }   // end for

    // use 0 to represent "number not found"
    return 0;
}


// iterator version, less elegantly
int get_number(const string& s)
{
    for (auto p = phone_book.begin(); p != phone_book.end(); ++p) {
        if (p->name == s) {
            return p->number;
        }
    }   // end for

    // use 0 to represent "number not found"
    return 0;
}


/*  adding elements and deleteing elements  */
void f(const Entry& ee, list<Entry>::iterator p, list<Entry>::iterator q)
{
    // add ee before the element referred to by p
    phone_book.insert(p, ee);
    // remove the element referred to by q
    phone_book.erase(q);
}
