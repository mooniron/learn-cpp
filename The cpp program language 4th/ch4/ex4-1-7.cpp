/**************************************************************
* Name     :  ex4-1-7.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年4月19日
**************************************************************/


/*
example 4.4 : containers
    4.4.1 : vector
*/


#include <iostream>
#include <string>
#include <vector>

using namespace std;

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


/*  example 4.4.1  */

vector<Entry> phone_book = {
    { "David Hume", 123456},
    {"Karl Popper", 234567},
    {"Bertrand Arthur William Russell", 345678}
};


void print_book(const vector<Entry>& book)
{
    for (int i = 0; i != book.size(); ++i) {
        cout << book[i] << '\n';
    }   // end for
}   // end function print_book

void print_book2(const vector<Entry>& book)
{
    // the elements of book constitute a range
    for (const auto& x : book) {
        cout << x << '\n';
    }
}


// size is 4
vector<int> v1 = {1, 2, 3, 4};
// size is 0
vector<string> v2;
// size is 23; initial element value : nullptr
//vector<Shape*> v3(23);
// size is 32, initial element value is 9.9
vector<double> v4(32, 9.9);


// initial size can be changed
void input()
{
    for (Entry e; cin >> e; ) {
        phone_book.push_back(e);
    }   // end for
}   // end function


// copy in assignments and initializations
vector<Entry> book2 = phone_book;


/*  example 4.4.1.2 : range checking  */

//
void silly(vector<Entry>& book)
{
    // book.size() is out of range
    int i = book[book.size()].number;
    // ...
}


/*  a simple range checking adaptation of vector  */
template<typename T>

class Vec : public std::vector<T> {
public :
    // use the constructors from vector (under the name Vec)
    using vector<T>::vector;

    // range check
    T& operator[](int i)
    { return vector<T>::at(i); }

    // range check const objects
    const T& operator[](int i) const
    { return vector<T>::at(i); }
};  // end class Vec


// test Vec
void checked(Vec<Entry>& book)
{
    try {
        // will throw an exception
        book[book.size()] = {"Joe", 9999999};
        // ...
    }
    catch (out_of_range) {
        cout << "range error\n";
    }
}   // end function checked


/*  main function  */
int main()
try {
    Vec<Entry> bookcheck = {
    { "David Hume", 123456},
    {"Karl Popper", 234567},
    {"Bertrand Arthur William Russell", 345678}
};
    // your code
    phone_book[phone_book.size()] = {"BRONZE LEE", 1234567890};
    //bookcheck[bookcheck.size()] = {"BRONZE LEE", 1234567890};
}
catch (out_of_range) {
    cerr << "range error\n";
}
catch (...) {
    cerr << "unknown exception thrown\n";
}

