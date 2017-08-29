/**************************************************************
* Name     :  ex8-1-11.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年5月3日
**************************************************************/


/*
example 8.3 : unions
    8.3.2 : anonymous unions
*/


#include <iostream>

using namespace std;


// to alternative representations represented as an union
class Entry2 {
private :
    enum class Tag { number, text };
    // discriminant
    Tag type;
    // representation
    // anonymous union is an object
    union {
        int i;
        // string has default constructor, copy operation and destructor
        string s;
    };
public :
    // use for exceptions
    struct Bad_entry { };
    string name;
    // destructor
    ~Entry2();
    // necessary because string variaint
    Entry2& operator=(const Entry2&);
    // constructor
    Entry2(const Entry2&);
    // ...
    // read access
    int number() const;
    string text() const;
    // write access
    void set_number(int n);
    void set_text(const string&);
    // ...
};


// read access functions
int Entry2::number() const
{
    if (type != Tag::number) {
        throw Bad_entry {};
    }   // end if
    return i;
}   // end function


// read access text
string Entry2::text() const
{
    if (type != Tag::text) {
        throw Bad_entry {};
    }   // end if
    return s;
}   // end function


// write access
void Entry2::set_number(int n)
{
    if (type == Tag::text) {
        // explicitly destroy string
        s.~string();
        type = Tag::number;
    }   // end if
    i = n;
}


// write access string
void Entry2::set_text(const string& ss)
{
    if (type == Type::text) {
        s = ss;
    }
    else {
        // placement new explicitly construct string
        new(&s) string {ss};
        type = Tag::text;
    }
}   // end function


// operator =, necessary because of the string variant
Entry2& Entry2::operator=(const Entry2& e)
{
    if (type == Tag::text && e.type == Tag::text) {
        // usual string assignment
        s = e.s;
        return *this;
    }

    // e.type == Tag::number
    if (type == Tag::text) {
        // explicit destroy s
        s.~string();
    }   // end if

    switch(e.type) {
        case Tag::number :
            i = e.i;
            break;
        case Tag::text :
            // placement new explicit construct
            new(&s) (e.s);
            break;
    }

    type = e.type;
    return *this;
}   // end function


// destructor
Entry2::~Entry2()
{
    if (type == Tag::text) {
        // explicit destroy
        s.~string();
    }
}   // end function
