/**************************************************************
* Name     :  ex2-1-7.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年4月7日
**************************************************************/


/*
example 2.2.5 :
    pointers, arrays and loops

*/


#include <iostream>

using namespace std;

void copy_fct() {
    int v1[10] {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    // v2 : a copy of v1
    int v2[10];

    // copy elements
    for (auto i = 0; i != 10; ++i) {
        v2[i] = v1[i];
        // ...
        }   // end for
    }   // end function copy_fct

void print() {
    int v[] {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    // for each x in v
    for (auto x : v) {
        cout << x << '\n';
        }   //end for

    for (auto x : {10, 21, 32, 43, 54, 65}) {
        cout << x << '\n';
        }   // end for
    // ...
    }   // end function print

void increment() {
    int v[] {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    /*
    & : "referencing to ".
    similar to a pointer, except no need prefix to access the value referred to by the reference
    a reference can not be made to refer to different object after its initialization.
    */
    for (auto& x : v) {
        ++x;
        // ...
        cout << "x is " << x << '\n';
        }   // end for
    }   // end function increment

// count the x occurrency in p[]
// p is assumed to point to an zero-terminated array of char (or to nothing)
int count_x(char *p, char x) {
    // point to nothing
    if (p == nullptr) {
        return 0;
        }

    int count = 0;
    for ( ; *p != 0; ++p) {
        if (*p == x) {
            ++count;
            }
        }   // end for

    return count;
    }   //end function count


int main() {
    // an array of 6 characters
    char v[6];
    // pointer to character
    char* p = &v[3];
    // *p is the object of p point to
    char x = *p;


    print();
    increment();

    // declarator operators
    // T[n] : an array of n T
    T a[n];
    // T* : point to T
    T* p;
    // T& : reference to T
    T& r;
    // T(A) : function f with type A argument and return type T
    T f(A);

    double* dp = nullptr;
    // pointer to a Link to a Record
    Link<Record> lst = nullptr;
    // error : nullptr is a pointer, not an integer.
    int x = nullptr;

    return 0;
    }   // end function main
