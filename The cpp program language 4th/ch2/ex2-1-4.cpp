/**************************************************************
* Name     :  ex2-1-4.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年4月7日
**************************************************************/

/*
* example 2.2.2:
    types, variables, and arithmetic
*/

#include <iostream>

using namespace std;

int main ()
{
    cout << "hello world!\n";
    double d = 3.14;    // initialize a float-point number
    int i = 7;      // initialize an integer number

    d = d + i;      // assign d + i to d
    i = d * i;      // assign truncating product of d and i to integer i
    cout << "d = " << d << "\ti = " << i << endl;

    double d1 = 2.3;
    double d2 {2.3};
    complex<double> z1 = 1;      // a complex number with double-precision floating-point scalars
    complex<double> z2 {d1, d2};     //
    complex<double> z3 = {1, 2};        // "=" is optional
    vector<int> v1 {1, 2, 3, 4, 5, 6};      // a vector of ints

    int i1 = 2.3;
    int i2 {2.3};       // error: floating-point to integer conversion
    int i3 = {3.2};     // error: floating-point to integer conversion, '=' is redundant

    // auto, deduce type from initializer, use '=' because there is no type conversion;
    auto b = true;      // a bool
    auto ch = 'x';      // a char
    auto i5 = 123;       // an int
    auto d4 = 1.2;      // a double
    auto a = sqart(x);      // a type whatever sqrt(x) return

    // more arithmetic
    x += y;     // x = x + y;    ++x;
    ++x;        // x increment 1
    x -= y;     // x = x - y;
    --x;        // x decrement 1
    x *= y;     // x = x * y;
    x /= y;     // x = x / y;
    x %= y;     // x = x % y;

    return 0;
}
