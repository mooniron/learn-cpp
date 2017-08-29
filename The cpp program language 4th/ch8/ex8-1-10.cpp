/**************************************************************
* Name     :  ex8-1-10.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年5月3日
**************************************************************/


/*
example 8.3 : unions
    8.3.1 : unions and classes
*/


#include <iostream>

using namespace std;


// union version
union Value {
    char* s;
    int i;
};

struct Entry_union {
    char* name;
    Type t;
    // use v.s if t == str, use v.i if t == num
    Value v;
};


void f(Entry a)
{
    Entry b = a;
}   // end function


// a complicated union
union U {
    int m1;
    // complex has a constructor
    complex<double> m2;
    // string has a constructor (maintaining a serious invariant)
    string m3;
};

void f2(U x)
{
    // error : which default constructor?
    U u;
    // error : which copy constructor?
    U u2 = x;
    // assign to int member
    u.m1 = 1;
    // disaster : read from string member, the stored value is an int
    string s = u.m3;
    // error : which destructors are called for x, u, and u2
    return;
}


// a default initializer
union U2 {
    int a;
    const char* p {""};
};

// default initialized to x1.p == ""
U2 x1;
// x2.a == 7
U2 x2 {7};
