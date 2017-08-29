/**************************************************************
* Name     :  ex12-1-8.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年5月18日
**************************************************************/



/*
example 12.2 : argument passing
    section 12.2.5 : default arguments
*/


class complex {
    double re, im;
public :
    // construct complex from two scalars
    complex(double r, double i) : re{r}, im{i} { }
    // construct complex from one scalar
    complex(double r) : re{r}, im{0} { }
    // default complex : {0, 0}
    complex() : re{0}, im{0} { }
    // ...
};


// default arguments
complex::complex(couble r = {}, double i = {}) : re{r}, im{i} { }

class X {
public :
    static int def_arg;
    void f(int = def_arg);
    // ...
};

int X::def_arg = 7;

void g(X& a)
{
    // maybe f(7)
    a.f();
    a.def_arg = 9;
    // f(9)
    a.f();
}


// trailing arguments only
// ok
int f(int, int = 0, char* = nulptr);
// error
int g(int = 0, int = 0, char*);
// error
int h(int = 0, int, char* = nullptr);
// syntax error
int nasty(char*=nullptr);

void f(int x = 7);
// error : cannot repeat default argument
void f(int x = 7);
// error : different default arguments
void f(int = 8);

void g()
{
    // ok : this declaration hides the outer one
    void f(int x = 9);
    // ...
}
