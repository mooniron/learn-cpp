/**************************************************************
* Name     :  ex11-1-4.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年5月10日
**************************************************************/



/*
example 11.3 : lists
*/


#include <iostream>

using namespace std;


struct S { int a, b; };
struct SS { double a, b; };
// f() takes an S
void f(S);

void g(S);
// g() is overloaded
void g(SS);

void h()
{
    // ok : call f(S{1, 2})
    f({1, 2});
    // error : ambiguous
    g({1, 2});
    // ok : call g(S)
    g(S{1, 2});
    // ok : call g(SS)
    g(SS{1, 2});

}


vector<double> v = {1, 2, 3.14};
// used like this
const double temp[] = {double{1}, double{2}, 3.14};
const initializer_list<double> tmp(temp, sizeof(temp) / sizeof(double));
vector<double> v(tmp);


void f()
{
    initializer_list<int> lst {1, 2, 3};
    cout << *lst.begin() << '\n';
    // error : lst is immutable
    *lst.begin() = 2;
    cout << *lst.begin() << '\n';
}


//
void f2()
{
    // direct initialization of a variable
    S v {7, 8};
    // assign using qualified list
    v = S{7, 8};
    // construct on free store using qualified list
    S* p = new S{7, 8};
}


// with one element
template<class T>
T square(T x)
{
    return x * x;
}

void f(int i)
{
    double d = square(double{i});
    complex<double> z = square(complex<double>{i});
}


// section 11.3.3 : unqualified lists
int f(double d, Matrix& m)
{
    // initializer (direct initialization)
    int v {7};
    // initializer (copy initialization)
    int v2 = {7};
    // assume m takes value pairs as subscripts
    int v3 = m[{2, 3}];
    // right-hand operand of assignment
    v = {8};
    // right-hand operand of assignment
    v += {99};
    // error : not left-hand operand of assignment
    {v} = 9;
    // error : not an operand of a non-assignment operator
    v = 7 + {10};
    // function argument
    f({10.0});
    // return value
    return {11};
}


int high_value(initializer_list<int> val)
{
    int high = numeric_traits<int>lowest();
    if (val.size() == 0) {
        return high;
    }
    for (auto x : val) {
        if (x > high) {
            high = x;
        }
    }
    return high;
}


int v1 = high_value({1, 2, 3, 4, 5, 6, 7});
int v2 = high_value({-1, 2, v1, 4, -9, 20, v1});


// error (no element type)
auto x0 = {};
// initializer_list<int>
auto x1 = {1};
// initializer_list<int>
auto x2 = {1, 2};
// initializer_list<int>
auto x3 = {1, 2, 3};
// error : nonhomogeneous deduce
auto x4 = {1, 2.0};

template<typename T>
void f(T);

// error: type of initializer is unknown
f({});
// error : an unqualified list does not match "plain T"
f({1});
// error : an unqualified list does not match "plain T"
f({1, 2});
// error : an unqualified list does not match "plain T"
f({1, 2, 3});


template<class T>
void f2(const vector<T>&);

// error : cannot deduce T
f2({1, 2, 3});
// error : cannot deduce T
f2({"Kona", "Sidney"});
// ok
f2(vector<int>{1, 2, 3});
// ok
f2(vector<string>{"Kona", "Sidney"});
