/**************************************************************
* Name     :  ex10-1-4.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年5月6日
**************************************************************/



/*
example 10.4 : constant expressions
    example 10.4.1 :
    example 10.4.2 :
    example 10.4.3 :
    example 10.4.4 :
    example 10.4.5 :
*/


#include <iostream>

using namespace std;


int x1 = 7;
constexpr int x2 = 7;
// error : initializer is not a constant expression
constexpr int x3 = x1;
// ok
constexpr int x4 = x2;

void f()
{
    // error : initializer is not a constant expression
    constexpr int y3 = x1;
    // ok
    constexpr int y4 = x2;
    // ...
}


constexpr int isqrt_helper(int sq, int d, int a)
{
    return sq <= a ? isqrt_helper(sq + d, d + 2, a) : d;
}

constexpr int isqrt(int x)
{
    return isqrt_helper(1, 3, x) / 2 - 1;
}

// s1 becomes 3
constexpr int s1 = isqrt(9);
constexpr int s2 = isqrt(1234);


// section 10.4.2 : consts in const expressions
const int x = 7;
const string s = "asdf";
const int y = sqrt(x);
// ok
constexpr int xx = x;
// error : s is not a constant expression
constexpr string ss = s;
// error : sqrt(x) is not a constant expression
constexpr int yy = y;



// section 10.4.3 : literal types
struct Point {
    int x, y, z;
    constexpr Point up(int d) { return {x, y, z + d}; }
    constexpr Point move(int dx, int dy) { return { x + dx, y + dy}; }
    // ...
};

constexpr Point origo {0, 0};
constexpr int z = origo.x;
constexpr Point a[] = {
    origo,
    Point {1, 1},
    Point {2, 2},
    origo.move(3, 3)
};
// x becomes 1
constexpr int x = a[1].x;
// error : sqrt(2) is not a constant expression
constexpr Point xy {0, sqrt(2)};


constexpr int square(int x)
{
    return x * x;
}

constexpr int radial_distance(Point p)
{
    return isqrt(square(p.x) + square(p.y) +square(p.z));
}

// the default constructor is constexpr
constexpr Point p1 {10, 20, 30};
// Point::up() is constexpr
constexpr Point p2 {p1.up(20)};
constexpr int dist = radial_distance(p2);




// section 10.4.4 : reference arguments
template<>
class complex<double> {
public :
    constexpr complex(double re = 0.0, double im = 0.0);
    constexpr complex(const complex<float>&);
    explicit constexpr complex(const complex<long double>&);
    // read the real part
    constexpr double real();
    // set the real part
    void real(double);
    // read the imaginary part
    constexpr double imag();
    // set the imaginary part
    void imag(double);
    complex<double>& operator=(double);
    complex<double>& operator+=(double);
    // ...
//
};


// note : <float> not <double>
constexpr complex<float> z1 {1, 2};
constexpr double re = z1.real();
constexpr double im = z1.imag();
// z2 becomes a copy of z1
constexpr conplex<double> z2 {re, im};
// z3 becomes a copy of z1
constexpr complex<double> z3 {z1};



// section 10.4.5 address constant expressions
constexpr const char* p1 = "asdf";
// ok
constexpr const char* p2 = p1;
// error : the compiler does not know the value of p1
constexpr const char* p3 = p1 + 2;
// ok : c == 'd'; the compiler knows the value pointed to by p1
constexpr cha c = p1[2];
