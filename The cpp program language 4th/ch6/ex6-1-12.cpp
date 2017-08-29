/**************************************************************
* Name     :  ex6-1-12.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年4月25日
**************************************************************/



/*
example 6.3 : declarations
    6.3.6 : deducing a type : auto and decltype
*/


#include <iostream>
#include <vector>
#include <string>
#include <complex>

using namespace std;


template<class T>
void f1(vector<T>& arg)
{
    for (vector<T>::iterator p = arg.begin(); p != arg.end(); ++p)
    {
        *p = 7;
    }
    for (auto p = arg.begin(); p != arg.end(); ++p)
    {
        *p = 7;
    }
}

int a1 = 123;
char a2 = 123;
// the type of a3 is "int"
auto a3 = 123;


// using auto can delay the detection of type errors
void f(double d)
{
    constexpr auto max = d + 7;
    // error : array bound not an integer
    int a[max];
}


// decorate a deduced type with specifiers and modifiers
void f2(vector<int>& v)
{
    // x is a const int&
    for (const auto& x : v)
    {
        // ...
    }
}

void f3(int& v)
{
    // x is an int type not int&
    auto x = v;
    // y is an int&
    auto& y = v;
}


/*  section 6.3.6.2 : auto and {}-list  */
// 12345 is an int
char v1 = 12345;
// 'c' is a char
int v2 = 'c';
T v3 = f();
// error : narrowing
char v1 {12345};
// fine : implicit char->int conversion
int v2 {'c'};
// works if and only if the type of f() can be implicitly converted to a T
T v3 {f()};
// v1 is an int
auto v1 = 12345;
// v2 is a char
auto v2 = 'c';
// v3 is of some appropriate type
auto v3 = f();

// v1 is a list of int
auto v1 {12345};
// v2 is a list of char
auto v2 {'c'};
// v3 is a list of some appropriate type
auto v3 {f()};
// error : can not deduce a type
auto x0 {};
// list of int with one element
auto x1 {1};
// list of int with two elements
auto x2 {1, 2};
// list of int with three elements
auto x3 {1, 2, 3};



/*  section 6.3.6.3 : decltype  */
// add two different element-type Matrixes
template<class T, class U>
auto operator+(const Matrix<T>& a, const Matrix<U>& b) -> Matrix<decltype(T{} + U{})>;

template<class T, class U>
auto operator+(const Matrix<T>& a, const Matrix<U>& b) -> Matrix<decltype(T{} + U{})>
{
    Matrix<decltype(T{} + U{})> res;
    for (int i = 0; i != a.rows(); ++i)
    {
        for (int j = 0; j != a.cols(); ++j)
        {
            res(i, j) += a(i, j) + b(i, j);
        }
    }

    return res;
}
