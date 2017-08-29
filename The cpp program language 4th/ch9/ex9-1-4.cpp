/**************************************************************
* Name     :  ex9-1-4.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年5月6日
**************************************************************/



/*
example 9.5 : iteration statements
*/


#include <iostream>
#include <string>
#include <vector>


using namespace std;


int sum(vector<int>& v)
{
    int s = 0;
    for (int x : v) {
        s += x;
    }   // end for

    return s;
}   // end function

int sum2(vector<int>& v)
{
    int s = 0;
    for (auto p = begin(v); p != end(v); ++p) {
        s += *p;
    }   // end for

    return s;
}


void incr(vector<int>& v)
{
    for (int& x : v) {
        ++x;
    }   // end for
}   // end function


//
template<class T>
T accum(vector<T>& v)
{
    T sum = 0;
    for (const T& x : v) {
        sum += x;
    }   // end for

    return sum;
}   // end function


void f(int v[], int max)
{
    for (int i = 0; i != max; ++i) {
        v[i] = i * i;
    }   // end for
}   // end function


void f2(int v[], int max)
{
    // introduce loop variable
    int i = 0;
    // test termination condition
    while (i != max) {
        // execute the loop body
        v[i] = i * i;
        // increment loop variable
        ++i;
    }   // while
}   // end function



for (string s; cin >> s; ) {
    v.push_back(s);
}   // end for

// forever
for ( ; ; ) {
    // ...
}   // end for

// forever
while (true) {
    // ...
}   // end while


//
template<class Iter,, class Value>
Iter find(Iter first, Iter last, Value val)
{
    while (first != last && *first != val) {
        ++first;
    }   // end while
    return first;
}   // end function


// i must be positive
void print_backwards(char a[], int i)
{
    cout << '{';
    do {
        cout << a[--i];
    } while (i);
    cout << '}';
}


//
void f(vector<string>& v, string terminator)
{
    char c;
    string s;
    while (cin >> c) {
        // ...
        if (c == '\n') {
            break;
        }
        // ...
    }   // end while
}   // end function


//
void find_prime(vector<string>& v)
{
    for (int i = 0; i != v.size(); ++i) {
        if (!prime(v[i])) {
            continue;
        }   // end if
        return v[i];
    }   // end for

}


// section 9.6 goto
// do something to a two-dimensional matrix called mn
void do_something(int i, int j)
{
    for (i = 0; i != n; ++i) {
        for (j = 0; j != m; ++j) {
            if (nm[i][j] == a) {
                goto found;
            }
            // not found
            // ...
        }   // end for
    }   // end for

    // nm[i][j] == a
    found :
        // ..
}   // end funtion
