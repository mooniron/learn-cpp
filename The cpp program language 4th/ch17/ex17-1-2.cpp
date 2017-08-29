/**************************************************************
* Name     :  ex17-1-2.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年6月10日
**************************************************************/



/*
example 17.1 : introduction
*/


#include <string>

using namespace std;

// string passed by value (copied into arg)
string ident(string arg);
{
    // return string (move the value of arg out of ident() to a caller)
    return arg;
}

int main()
{
    // initialize string (construct in s1)
    string s1 {"Adams"};
    // copy s1 into ident()
    // move the result of ident(s1) into s1
    // s1's value is "Adams"
    s1 = indent(s1);
    // initialize string (construct in s2)
    string s2 {"Pratchett"};
    // copy the value of s2 into s1;
    // both s1 and s2 have the value "Pratchett"
    s1 = s2;

}


class X {
    // "ordinary constructor create an object"
    X(Sometype);
    // default constructor
    X();
    // copy constructor
    X(const X&);
    // move constructor
    X(X&&);
    // copy assignment clean up target and copy
    X& operator=(const X&);
    // move assignment : clean up target and move
    X& operator=(X&&);
    // destructor : clean up
    ~X();
    // ...
};

