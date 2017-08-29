/**************************************************************
* Name     :  ex3-1-2.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年4月7日
**************************************************************/


/*
example 3.2.1.1 : concrete type class
    arithmatic type
*/


#include <iostream>

using namespace std;


class complex {
    // representation : two double;
    double re, im;
public :
    // construct complex from two scalars
    complex(double r, double i) : re {r}, im {i} {}
    // construct complex from one scalar
    complex(double r) : re {r}, im {0} {}
    // default complex {0, 0}
    complex() : re {0}, im {0} {}
    // return real number
    double real() const { return re; }
    //
    void real(double d) { re = d; }
    //
    double imag() const { return im; }
    //
    void imag(double d) { im = d; }
    // add to re and im, and return the result
    complex& operator+=(complex z) { re += z.re, im += z.im; return *this; }
    // subtract to re and im, and return the result
    complex& operator-=(complex z) { re -= z.re, im -= z.im; return *this; }
    complex& operator*=(complex)    // defined out_of_class somewhere
    complex& operator*=(complex)    // defined out_of_class somewhere
    complex operator+(complex a, complex b) { return a += b; }
    complex operator-(complex a, complex b) { return a -= b; }
    complex operator-(complex a) { return {-a.real(), -a.imag()}; }
    complex operator*(complex a, complex b) { return a *= b; }
    complex operator/(complex a, complex b) { return a /= b; }
    // ==
    bool operator==(complex a, complex b) {
        return a.real() == b.real() && a.imag() == b.imag();
        }   // end operator ==
    // not equal ！=
    bool operator!=(complex a, complex b) {
        return !(a == b);
        }
    complex sqrt(complex);
    // ...
    };


// class complex can be used like this
void f(complex z) {
    complex a {2.3};
    complex b {1/a};
    complex c {a + z * {1, 2.3}};
    // ...
    if (c != b) {
        c = -(b / a) + 2 * b;
        }
    }   // end function f
