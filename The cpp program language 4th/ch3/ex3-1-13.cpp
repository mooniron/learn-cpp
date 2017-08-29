/**************************************************************
* Name     :  ex3-1-13.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年4月7日
**************************************************************/


/*
example 3.4 : templates
    3.4.4 : variadic templates

*/


#include <iostream>

using namespace std;

// declare g
template<typename T>
void g(T);

// do nothing : the terminate notation for the recursive function f
void f() {}

// variadic template : arbitrary number of arguments, arbitrary types
template<typename T, typename ... Tail>

// ... : indicates the rest of a list
void f(T head, Tail... tail)
{
    // do something to head
    g(head);
    // try again with tail
    f(tail...);
}




/*  main function  */
int main()
{
    cout << "first : ";
    f(1, 2.2, "hello");
    cout << "\nsecond : ";
    f(0.2, 'c', "yuck!", 0, 1, 2);
    cout << "\n";
}   // end function


/*  g function block  */
template<typename T>

void g(T x)
{
    cout << x << " ";
}
