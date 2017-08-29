/**************************************************************
* Name     :  ex7-1-5.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年4月25日
**************************************************************/



/*
example 7.4 : pointers and arrays
    7.4.1 : navigating arrays
*/


#include <iostream>

using namespace std;


void use(char c)
{
    cout << c;
}

void fi(char v[])
{
    for (int i = 0; v[i] != 0; ++i)
    {
        use(v[i]);
    }
}


void fp(char v[])
{
    for (char* p = v; *p != 0; ++p)
    {
        use(*p);
    }   // end for
}

// a is an array, j is an integer
// a[j] == *(&a[0] + j) == *(a + j) == *(j + a) == j[a]


template<typename T>
int byte_diff(T* p, T* q)
{
    return reinterpret_cast<char*>(q) - reinterpret_cast<char*>(p);
}

void diff_test()
{
    int vi[10];
    short vs[10];
    // array pointers q - p == the number of array elements in [p, q)
    cout << vi << ' ' << &vi[1] << ' ' << &vi[1] - &vi[0] \
    << ' ' << byte_diff(&vi[0], &vi[1]) << '\n';
    cout << vs << ' ' << &vs[1] << ' ' << &vs[1] - &vs[0] \
    << ' ' << byte_diff(&vs[0], &vs[1]) << '\n';
}   // end function diff_test


int main()
{
    diff_test();
}   // end function main


void f()
{
    int z1[10];
    int z2[10];
    // i1 = 2
    int i1 = &z1[5] - &z1[3];
    // result undefined
    int i2 = &z1[5] - &z2[3];
    // p1 = &z2[2]
    int* p1 = z2 + 2;
    // *p2 undefined
    int* p2 = z2 - 2;
}   // end function f()


void fpc(char v[], int size)
{
    for (int i = 0; i != size; ++i)
    {
        // hope that v has at least size elements
        use(v[i]);
    }   // end for
    for (int x : v)
    {
        // error : range-for does not work for pointers
        use(x);
    }   // end for

    const int n = 7;
    char v2[n];
    for (int i = 0; i != n; ++i)
    {
        use(v2[i]);
    }   // end for
    for (int x : v2)
    {
        // range-for works for arrays of known size
        use(x);
    }   // end for
}   // end function fpc
