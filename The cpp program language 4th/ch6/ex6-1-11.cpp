/**************************************************************
* Name     :  ex6-1-11.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年4月25日
**************************************************************/



/*
example 6.3 : declarations
    6.3.5 : initialization
*/


#include <iostream>
#include <vector>
#include <string>
#include <complex>

using namespace std;


/*
X a1 {v};
X a2 = {v};
X a3 = v;
X a4(4);
*/


void f(double val1, int val2)
{
    // if val == 7.9, x2 becomes 7
    int x2 = val;
    // if val2 == 1025, c2 becomes 1
    char c2 = val2;
    // error : possible truncation
    int x3 {val1};
    // error : possible narrowing
    char c3 {val2};
    // OK : 24 can be represented exactly as a char
    char c4 {24};
    // error (assuming 8-bit chars) : 264 cannot be represented as a char
    char c5 {264};
    // error : no double to int value conversion
    int x4 {2.0};
    // ...
    // z1 is an initializer_list<int>
    auto z1 {99};
    // z2 is an int
    auto z2 = 99;
    // v1 is a vector of 1 element with the value 99
    vector<int> v1 {99};
    // v2 is a vector of 99 elements, each with the default value 0
    vector<int> v2(99);
    // v1 is a vector of 1 element with the value "hello!"
    vector<string> v1 {"hello!"};
    // error : no vector constructor takes a string literal as its arguments
    vector<string> v2("hello!");

    // x4 becomes 0
    int x4 {};
    // d4 becomes 0.0
    double d4 {};
    // p becomes nullptr
    char* p {};
    // v4 becomes the empty vector
    vector<int> v4 {};
    // s4 becomes ""
    string s4 {};
}


/*  section 6.3.5.1 : missing initializers  */
constexpr int max = 1024 * 1024;
// input buffer
char buf[max];
// read at most max characters into buf
some_stream.get(buf, max);
// initialize every char to 0, low performance
//char buf[max] {};

// means "int a {};" so that a becomes 0
int a;
// means "double d {};" so that d becomes 0.0
double d;

// local variables and objects created on the free store are not initialized by default
int f2()
{
    // x does not have a well-defined value
    int x;
    // buf[i] does not have a well-defined value
    char buf[1024];
    // *p does not have a well-defined value
    int* p {new int};
    // q[i] does not have a well-defined value
    char* q {new char[1024]};
    // s == "" because of string's default constructor
    string s;
    // v == {} because of vector's default constructor
    vector<char> v;
    // *ps is "" because of string's default constructor
    string* ps {new string};
    // ...
}


void ff()
{
    // x becomes 0
    int x {};
    // buf[i] becomes 0 for all i
    char buf[1024] {};
    // *p becomes 10
    int* p {new int {10}};
    // q[i] becomes 0 for all i
    char* q {new char[1024] {}};
    // ...
}


/*  section 6.3.5.2 : initializer lists  */
// '=' is redundant
// array initializer
int a[] = {1, 2};
// struct initializer
struct S {
    int x, string s
};
// struct initializer
S s = { 1, "Helios" };
// use constructor
complex<double> z = { 0, pi };
// use list constructor
vector<double> v = { 0.0, 1.1, 2.2, 3.3 };


// function-style argument lists
// use constructor
complex<double> z(0, pi);
// use constructor : v get 10 elements initialized to 3.3
vector<double> v(10, 3.3);
// function-style initializer
complex<double> z1(1, 2);
// function declaration
complex<double> f1();
// initialization by constructor to {1, 2}
complex<double> z2 {1, 2};
// initialization by constructor to the default value {0, 0}
complex<double> f2 {};


// x1 is an initializer_list<int>
auto x1 {1, 2, 3, 4};
// x2 is an initializer_list of <double>
auto x2 {1.0, 2.24, 3.5};
// error can not deduce the type of {1.0, 2}
auto x3 {1.0, 2};
