/**************************************************************
* Name     :  ex3-1-3.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年4月7日
**************************************************************/


/*
example 3.2.1.2 : concrete type class
    a container
*/


#include <iostream>

using namespace std;


class Vector {
private :
    // elem : pointer to an array of sz doubles
    double* elem;
    int sz;
public :
    // constructor : acquire resources
    Vector(int s) : elem {new double[s]}, sz {s} {
        // exception
        if (s < 0) {
            throw length_error {};
            }
        // initialize elements
        for (int i = 0; i != s; ++i) {
            elem[i] = 0;
            }   // end for
        }
    // destructor : release resources
    ~Vector() { delete[] elem; }
    //
    double& operator[](int i);
    //
    //int size() const;
    int size() const { return sz; }
};


void fct(int n) {
    Vector v(n);

    // ... use v
    {
        Vector v2(2 * n);
        // ... use v and v2

        }   // v2 is destroyed here
    // ... use v
    }   // v is destroyed here    // end function fct
