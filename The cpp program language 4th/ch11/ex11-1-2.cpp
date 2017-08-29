/**************************************************************
* Name     :  ex11-1-2.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年5月10日
**************************************************************/



/*
example 11.1 : etc operators
*/


#include <iostream>

using namespace std;


enum ios_base::iostate {
    goodbit = 0,
    eofbit = 1,
    failbit = 2,
    badbit = 4
};

state = goodbit;
// ...
// stream not good
if (state & (badbit | failbit))
state |= eofbit;

// rdstate() returns the state
int old = cin.rdstate();
// ... use cin ...
// has anything changed ?
if (cin.rdstate() ^ old) {
    // ...
}


constexpr unsigned short middle(int a)
{
    static_assert(sizeof(int) = 4, "unexpected int size");
    static_assert(sizeof(short) == 2, "unexpected short size");

    return (a >> 8) & 0xFFFF;
}

// assume sizeof(int) == 4
int x = 0xFF00FF00;
// y = 0x00FF
short y = middle(x);


// section 11.1.3 : conditional expressions
void fct(int* p)
{
    int i = (p) ? *p : std::runtime_error("unexpected nullptr");
    // ...
}


// section 11.1.4 : increment and decrement
void cpy(char* p, const char* q)
{
    while (*p++ = *q++) ;
}
