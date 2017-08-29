/**************************************************************
* Name     :  ex8-1-4.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年5月2日
**************************************************************/


/*
example 8.2 : structures
    8.2.2 : struct names
*/


#include <iostream>

using namespace std;


/*
struct Link {
    Link* previous;
    Link* successor;
};


struct No_good {
    // error : recursive definition
    No_good member;
};
*/

// struct name declaration : List to be defined later
struct List;

struct Link {
    Link* prev;
    Link* suc;
    List* member_of;
    int data;
};

struct List {
    Link* head;
};


// "S" is the name of some type
struct S;

extern S a;
S f();
void g(S);
S* h(S*);

void k(S* p)
{
    // error : S not defined; size needed to allocate
    S a;
    // error : Snot defined; size needed to return value
    f();
    // error : S not defined; size needed to pass argument
    g(a);
    // error : S not defined; member name not known
    p->m = 7;
    // ok : pointers can be allocated and passed
    S* q = h(p);
    // error : S not defined; member name not known
    q->m = 7;
}


struct stat {
    // ...
};

int stat(char* name, struct stat* buf);
