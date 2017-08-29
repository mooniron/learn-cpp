/**************************************************************
* Name     :  ex2-1-8.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年4月7日
**************************************************************/


/*
example 2.3.1:
    struct
*/

#include <iostream>

using namespace std;

struct Vector {
    // number of elements
    int sz;
    // pointer to elements
    double* elem;
    };

//Vector v;

void Vector_init(Vector& v, int s) {
    // allocate an array of doubles
    v.elem = new double[s];
    v.sz = s;
    }   // end function Vector_init

// read s integer from cin and return sum; s is assumed to be positive
double read_and_sum(int s) {
    Vector v;
    // allocate s elements for v
    Vector_init(v, s);

    for (int i = 0; i != s; ++i) {
        // read into elements
        cin >> v.elem[i];
        }   // end for

    double sum = 0;
    for (int i = 0; i != s; ++i) {
        // take the sum of elements
        sum += v.elem[i];
        }   // end for

    return sum;
    }   // end function read_and_sum

void f(Vector v, Vector& rv, Vector* pv) {
    // access through name
    int i1 = v.sz;
    // access through reference
    int i2 = rv.sz;
    // access through pointer
    int i4 = pv->sz;
    }   // end function f


int main() {
    int s = 6;
    double sum = 0.0;

    sum = read_and_sum(s);
    cout << "sum is " << sum << endl;

    return 0;
    }   // end function main
