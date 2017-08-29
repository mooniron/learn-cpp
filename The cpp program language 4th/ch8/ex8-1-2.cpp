/**************************************************************
* Name     :  ex8-1-2.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年5月2日
**************************************************************/


/*
example 8.2 : structures
*/


#include <iostream>
//#include <vector>

using namespace std;



struct address {
    // "Jim Dandy"
    const char* name;
    // 61
    int number;
    // "South Street"
    const char* street;
    // "New Providence"
    const char* town;
    // 'N' 'J'
    char state[2];
    // "07974"
    const char* zip;
};  // end struct


void f()
{
    address jd;
    jd.name = "Jim Dandy";
    jd.number = 61;
    //
}


address jd = {
    "Jim Dandy",
    61,
    "South Street",
    "New Providence",
    {'N', 'J'},
    "07974"
};


void print_addr(address* p)
{
    cout << p->name << '\n' << p->number << '\n' \
    << p->street << '\n' << p->town << '\n' \
    << p->state[0] << p->state[1] << ' ' << p->zip << '\n';
}   // end function


void print_addr(const address& r)
{
    cout << r.name << '\n' \
    << r.number << '\n' << r.street << '\n' \
    << r.town << '\n' \
    << r.state[0] << r.state[1] << ' ' << r.zip << '\n';
}



address current;
address set_current(address next)
{
    address prev = current;
    current = next;
    return prev;
}   // end function set_current


int main()
{
    print_addr(&jd);
    cout << '\n';
    print_addr(jd);

    return 0;
}   // end function main
