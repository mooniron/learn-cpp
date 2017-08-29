/**************************************************************
* Name     :  ex2-1-14.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年4月7日
**************************************************************/


/*
example 2.4.3.1 :
    exceptions
*/


#include <iostream>

using namespace std;

double& Vector::operator[](int i) {
    if (i < 0 || size() <= i) {
        throw out_of_range {"Vector::operator[]"};
        }   // end if

    return elem[i];
    }   // end function operator[]


void f(Vector& v) {
    // ...

    // exceptions here are handled by the hander defined below
    try {
        // try to access beyond the end of v
        v[v.size()] = 7;
        }
    // oops : out_of_range error
    catch(out_of_range) {
        // ... handle range error
        }

    // ...
    }   // end function f
