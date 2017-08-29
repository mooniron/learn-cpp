/**************************************************************
* Name     :  ex6-1-3.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年4月25日
**************************************************************/



/*
example 6.2 : types
    6.2.2 : booleans
*/


#include <iostream>

using namespace std;


int main()
{
    // x is a floatingpoint variable
    float x {0.0};
    // y is an integer variable with the initial value 7
    int y = 7;
    // f is a function taking an argument of type int and returning a floating-point number
    float f(int);

    return 0;
}   // end function main


//
void fb(int a, int b)
{
    bool b0 {a == b};
    bool is_opened(File*);
    bool greater(int a, int b) { return a > b; }

    // b1 is true
    bool b1 = 7;
    // error : narrowing
    bool b1 {7};
    bool b2 {7 != 0};
    // i1 becomes 1
    int i1 = true;
    // i2 becomes 1
    int i2 {true};

    //
    bool a = true;
    bool b = true;
    // a + b is 2, so x becomes true
    bool x = a + b;
    // a || b is 1, so y becomes true, "||" means "or"
    bool y = a || b;
    // a - b is 0, so z becomes false
    bool z = a - b;

    // ...
}


// nullptr convert to bool fallse, a non-null pointer converts to true
void g(int* p)
{
    // narrows to true or false
    bool b = p;
    // explicit test against nullptr
    bool b2 {p != nullptr};

    // equivalent to p != nullptr
    if (p)
    {
        // ...
    }
}
