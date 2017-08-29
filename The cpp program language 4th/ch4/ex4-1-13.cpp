/**************************************************************
* Name     :  ex4-1-13.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年4月19日
**************************************************************/


/*
example 4.5 : algorithms
    4.5.4 : predicates

predicates : function objects, lambda expressions
*/


#include <sting>
#include <algorithm>

using namespace std;

struct Greater_than;

// find greater than 42 value
void f(map<string, int>& m)
{
    // Greater_than is a function object
    auto p = find_if(m.begin(), m.end(), Greater_than {42});
    // ...

    // lambda expression
    int cxx = count_if(m.begin(), m.end(), \
    [](const pair<string, int>& r) { return r.second > 42});
}   // end function f


struct Greater_than {
    int val;
    // constructor
    Greater_than(int v) : val {v} { }
    // operator()
    bool operator()(const pair<string, int>& r) { return r.second > val; }
};
