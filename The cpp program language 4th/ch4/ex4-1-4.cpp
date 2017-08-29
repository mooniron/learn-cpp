/**************************************************************
* Name     :  ex4-1-4.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年4月18日
**************************************************************/


/*
example 4.3 : stream I/O
    4.3.1 : output
*/

#include <iostream>

using namespace std;


void f()
{
    cout << 10;
}

void g()
{
    int i {10};
    cout << i;
}

void h(int i)
{
    cout << "the value of i is ";
    cout << i;
    cout << '\n';
}

void h2(int i)
{
    cout << "the value of i is " << i << '\n';
}

void k()
{
    // note : char implicitly converted to int
    int b = 'b';
    char c = 'c';
    cout << 'a' << b << c;
}
