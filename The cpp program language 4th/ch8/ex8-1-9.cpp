/**************************************************************
* Name     :  ex8-1-9.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年5月3日
**************************************************************/


/*
example 8.3 : unions
*/


#include <iostream>

using namespace std;


enum Type {
    str, num
};

struct Entry {
    char* name;
    Type t;
    // use s if t == str
    char* s;
    // use i if t == num
    int i;
};


void f(Entry* p)
{
    if (p->t == str) {
        cout p->s;
    }   // end if
    // ...
}   // end function


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

void funion(Entry_union* p)
{
    if (p->t == str) {
        cout << p->v.s;
    }
    // ...
}   // end function


//
union Fudge {
    int i;
    int* p;
};

// convert int to int*
int* cheat(int i)
{
    Fudge a;
    a.i = i;
    //bad use
    return a.p;
}   // end function

//
int* cheat2(int i)
{
    // obviously ugly and dangerous
    return reinterpret_cast<int*>(i);
}   // end function
