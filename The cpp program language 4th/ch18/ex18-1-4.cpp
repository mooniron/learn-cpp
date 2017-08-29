/**************************************************************
* Name     :  ex18-1-4.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年6月18日
**************************************************************/



/*
example 18.3 : a complex number type
*/


void f()
{
    complex a {1, 2};
    complex b {3};
    complex c {a + 2.3};
    complex d {2 + b};
    b = c * 2 * c;
}


/// section 18.3.1 : member and nonmember operators
class complex {
    double re, im;
public :
    // needs access to representation
    complex& operator+=(complex a);
    // ...
};

complex operator+(complex a, complex b)
{
    // access representation through +=
    return a += b;
}

void f(complex x, complex y, complex z)
{
    // r1 = operator+(operator+(x, y), z)
    complex r1 {x + y + z};
    // r2 = x
    complex r2 {x};
    // r2.operator+=(y)
    r2 += y;
    // r2.operator+=(z)
    r2 += z;
}

inline complex& complex::operator+=(complex a)
{
    re += a.re;
    im += a.im;
    return *this;
}


// section 18.3.2 : mixed-mode airthmetic
class complex {
    double re, im;
public :
    complex& operator+=(complex a)
    {
        re += a.re;
        im += a.im;
        return *this;
    }
    complex& operator+=(double a)
    {
        re += a;
        return *this;
    }
    // ...
};

complex operator+(complex a, complex b)
{
    return a += b;
}

complex operator+(complex a, double b)
{
    return {a.real() + b, a.imag()};
}

complex operator+(double a, complex b)
{
    return {a + b.real(), b.imag()};
}

void f(complex x, complex y)
{
    // calls operator+(complex, complex)
    auto r1 = x + y;
    // calls operator+(complex, double)
    auto r2 = x + 2;
    // calls operator+(double, complex)
    auto r3 = 2 + x;
    // built-in integer addition
    auto r4 = 2 + 3;
}


// section 18.3.3 : conversions
// should mean b.re = 3, b.im = 0
complex b {3};

class complex {
    double re, im;
public :
    // build a complex from a double
    complex(couble r) : re {r}, im {0} { }
    // ...
};


class complex {
    double re, im;
public :
    complex() : re {0}, im {0} { }
    complex(double r) : re {r}, im {0} { }
    complex(double r, double i) : re {r}, im {i} { }
    // ...
};

class complex {
    double re, im;
public :
    complex(double r = 0, double i = 0) : re {r}, im {i} { }
    // ...
};


void f()
{
    complex z;
    complex x {1, 2};
    // y also has the value {1, 2}
    complex y {x];
    // z also has the value {1, 2}
    z = x;
}


// section 18.3.3.1 conversions of operands
bool operator==(complex, complex);

void f(complex x, complex y)
{
    // means operator==(x, y)
    x == y;
    // means operator==(x, complex(3))
    x == 3;
    // means operator==(complex(3), y)
    3 == y;
}

void g(complex z)
{
    // ok
    3 + z;
    // error : 3 is not a class object
    3.operator+=(z);
    // error : 3 is not a class object
    3 += z;
}

complex x {4, 5};
// like tmp = sqrt(x); tmp += {1, 2}
complex z {sqrt(x) += {1, 2}};



// section 18.3.4 : literals
class complex {
public :
    constexpr complex(double r = 0, double i = 0) : re {r}, im {i} { }
    // ...
};

complex z1 {1.2, 12e3};
// guaranteed compile-time initialization
constexpr complex z2 {1.2, 12e3};

// imaginary literal
constexpr complex<double> operator ""i(long double d)
{
    // complex is a literal type
    return {0, d};
}

complex z1 {1.2 + 12e3i};
complex f(double d)
{
    auto x {2.3i};
    return x + sqrt(d + 12e3i) + 12e3i;
}


// section 18.3.5 : accessor functions
class complex {
    double re, im;
public :
    constexpr double real() const { return re; }
    constexpr double imag() const { return im; }
    void real(double r) { re = r; }
    void imag(double i) { im = i; }
    // ...
};


inline bool operator==(complex a, complex b)
{
    return a.real() == b.real() && a.imag() == b.imag();
}


// section 18.3.6 : helper function
class complex {
    double re, im;
public :
    constexpr complex(double r = 0, double i = 0) : re {r}, im {i} { }
    constexpr double real() const { return re; }
    constexpr double imag() const { return im; }
    void real(double r ) { re = r; }
    void imag(double i) { im = i; }
    complex& operator+=(complex);
    complex& operator+=(double);
    // -=, *=, and /=
};

complex operator+(complex, complex);
complex operator+(complex, double);
complex operator+(double, complex);
// binary -, *, and /
// unary minus
complex operator-(complex);
// unary plus
complex operator+(complex);
bool operator==(complex, complex);
bool operator!=(complex, complex);
// input
istream& operator>>(istream&, complex&);
// output
ostream& operator<<(ostream&, complex);

complex polar(double rho, double theta);
complex conj(complex);

double abs(complex);
double arg(complex);
double norm(complex);
// for notational convenience
double real(complex);
//for notational convenience
double imag(complex);

complex acos(complex);
complex asin(complex);
complex atan(complex);
// ...


