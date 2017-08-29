/**************************************************************
* Name     :  ex6-1-10.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年4月25日
**************************************************************/



/*
example 6.3 : declarations
    6.3.4 : scope
*/


#include <iostream>
#include <vector>
#include <string>
#include <complex>

using namespace std;


// global x
int x;

void f()
{
    // local x hides global x
    int x;
    // assign to local x
    x = 1;
    {
        // hides first local x
        int x;
        // assign to second local x
        x = 2;
    }
    // assign to first local x to 3
    x = 3;
}

// take address of global x
int* p = &x;

// a hidden global name can be referred to using the scope resolution operator, ::
void f2()
{
    // hide global x
    int x = 1;
    // assign to global x
    ::x = 2;
    // assign to local x
    x = 2;
    // ...
}


void f3()
{
    // perverse : initialize x with its own (uninitialized) value
    int x = x;
}


int x = 11;

// perverse : use of two different objects both called x in a single scope
void f4()
{
    // use global x : y = 11
    int y = x;
    // hide global x
    int x = 22;
    // use local x : y = 22
    y = x;
}


// arguments are considered declared in the outermost block of a function
void f5(int x)
{
    // error : x is defined twice int the same scope function f5
    int x;
}


void f6(vector<string>& v, list<int>& lst)
{
    for (const auto& x : v)
    {
        cout << x << '\n';
    }
    for (auto x : lst)
    {
        cout << x << '\n';
    }
    for (int i = 0; i != v.size(); ++i)
    {
        cout << v[i] << '\n';
    }
    for (auto i : {1, 2, 3, 4, 5, 6, 7})
    {
        cout << i << '\n';
    }
}
