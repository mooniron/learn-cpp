/**************************************************************
* Name     :  ex4-1-6.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年4月18日
**************************************************************/


/*
example 4.3 : stream I/O
    4.3.2 : input
*/

#include <iostream>
#include <string>

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


/*  main test  */
int main()
{
    // read from cin into ee
    for (Entry ee; cin >> ee;) {
        // write ee to cout
        cout << ee << '\n';
        }   // end for

    //
    return 0;
}
