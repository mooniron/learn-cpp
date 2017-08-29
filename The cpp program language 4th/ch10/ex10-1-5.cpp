/**************************************************************
* Name     :  ex10-1-5.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年5月6日
**************************************************************/



/*
example 10.5 : implicit type conversion
*/


#include <iostream>

using namespace std;


// section 10.5.1 promotions


// section 10.5.2 conversions
void f(double d)
{
    // beware : double-precision floating-point to char conversion
    char c = d;
    // error : double precision floating-point to char conversion
    char c2 {d};
}


// binary 1111111111 : uc becomes binary 11111111, that is , 255
unsigned char uc = 1023;
// implementation-defined : 127 or -1
signed char sc = 1023;


// largest float value
float f = FLT_MAX;
// ok : d == f
double d = f;
// largest double value
double d2 = DBL_MAX;
// undefined if FLT_MAX < DBL_MAX
float f2 = d2;
// ok : ld = d2
long double ld = d2;
long double ld2 = numeric_limits<long double>::max();
// undefined if sizeof(long double) > sizeof(double)
double d3 = ld2;


// ok, but weird
int* p = (1 + 2) * (2 * (1 - 1));


void f(int* p, int i)
{
    // true if p != 0
    bool is_not_zero = p;
    // true if i != 0
    bool b2 = i;
}


void fi(int);
void fb(bool);

void ff(int* p, int* q)
{
    // ok
    if (p) {
        do_something(*p);
    }
    // ok but verbose
    if (q != nullptr) {
        do_something(*q);
    }
    //...
    // error : no pointer to int conversion
    fi(p);
    // ok : pointer to bool conversion (surprise!?)
    fb(p);
}


// i becomes 2
int i = 2.7;
// undefined for 8-bit chars : 2000 can not be represented as an 8-bit char
char b = 2000.7;

int i = float(1234567890);

char checked_cast(int i)
{
    // warning : not portable
    char c = i;
    if (i != c) {
        throw std::runtime_error("int-to-char check failed");
    }
    returnc;
}


void my_code(int i)
{
    char c = checked_cast(i);
    // ...
}


