/**************************************************************
* Name     :  ex6-1-6.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年4月25日
**************************************************************/



/*
example 6.2 : types
    6.2.7 : void
*/


#include <iostream>

using namespace std;


int main()
{
    // error : there are no void objects
    void x;
    // error : there are no references to void
    void& r;
    // function f does not return a value
    void f();
    // pointer to object of unknown type
    void* pv;

    return 0;
}
