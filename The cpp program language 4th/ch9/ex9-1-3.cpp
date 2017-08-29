/**************************************************************
* Name     :  ex9-1-3.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年5月6日
**************************************************************/



/*
example 9.4 : selection statements
*/


#include <iostream>
#include <string>
#include <vector>


using namespace std;


enum E1 { a, b };
enum class E2 { a, b };

void f(E1 x, E2 y)
{
    // ok
    if (x)
    // ...
    // error : no conversion to bool
    if (y)
    // ...
    // ok
    if (y == E2::a)
    // ...
}   // end function


int max(int a, int b)
{
    return (a > b) ? a : b;
}   // end function


void f2(int i)
{
    if (i) {
        int x = i + 2;
        ++x;
        //...
    }
    else {
        // error : x is not in scope
        ++x;
    }
    // error : x is not in scope
    ++x;
}   // end function


void f1(int i)
{
    if (i) {
        // error : declaration of if-statement branch
        int x = i + 2;
    }

}   // end function



/*  section : 9.4.2 switch  */
void f(int i)
{
    switch (i) {
        // error : floating point uses for case
        case 2.7 : // ...
        case 2 : // ...
        // error : 2 used twice in case labels
        case 4 - 2 : // ...
        // ...
    }   // end switch
}   // end function


// all cases will be executed
swich (val) {
    case 1 :
        cout << "case 1\n";
    case 2 :
        cout << "case 2\n";
    case default :
        cout << "case default\n";
}


// handle (action, value) pair
switch (action)
{
    // no break : fall through to print
    case do_and_print :
        act(value);
    case print :
        print(value);
        break;
    // ...
}


enum class Vessel { cup, glass, goblet, chalice };

void problematic(Vessel v)
{
    switch (v) {
        case Vessel::cup :
            break;
        case Vessel::glass :
            break;
        case Vessel::goblet :
            break;
        //
    }   // end switch

}   // end function


// declarations in cases
void f(int i)
{
    switch (i) {
        case 0 :
            // uninitialized
            int x;
            // error : declaration can be bypassed (explicitly initialized)
            int y = 3;
            // error : declaration can be bypassed (implicitly initialized)
        case 1 :
            // error : use of uninitialized object
            ++x;
            ++y;
            s = "nasty!";
        //
    }   // end switch

}   // end function


// declarations in conditions
if (double d = prim(true)) {
    left /= d;
    break;
}


double d;
// ...
// oops!
d2 = d;
// ...
if (d = prim(true)) {
    left /= d;
    break;
}
// ...
// two unrelated uses of d
d = 2.0;
