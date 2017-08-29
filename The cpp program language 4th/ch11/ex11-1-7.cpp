/**************************************************************
* Name     :  ex11-1-6.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年5月14日
**************************************************************/



/*
example 11.5 : explicit type conversion
    section 11.5.1 : construction
    section 11.5.2 : named casts
    section 11.5.3 : c-style cast
*/


#include <iostream>

using namespace std;


// d1 = 2.0
auto d1 = double{2};
// d2 = 0.5
auto d2 {double{2} / 4};


void f(int);
void f(double);
void g(int i, double d)
{
    // call f(int)
    f(i);
    // error : {} doesn't do int to floating conversion
    f(double{i});
    // call f(double)
    f(d);
    // error : {} doesn't truncate
    f(int{d});
    // call f(int) with a truncated value
    f(static_cast<int>(d));
    // call f(double) with a rounded value
    f(round(d));
    // call f(int) with a rounded value
    f(static_cast<int>(lround(d)));
    // if the d is overflows the int, this still truncates
    //
}


static_assert(sizeof(int) == sizeof(double), "unexpected sizes");
// largest possible integer
int x = numeric_limits<int>::max();
double d = x;
int y = d;

// fine
double d {1234};


void g2(char* p)
{
    // error : no char* to int conversion
    int x = int{p};
    //
    using Pint = int*;
    // error : no char* to int* conversion
    int* p2 = Pint{p};
    // ...
}


template<class T> void f(const T&);

void g3()
{
    // default int value
    f(int{});
    // default complex
    f(complex<double>{});
    // ...
}



// section 11.5.2 : named casts
// device at 0Xff00
IO_device* d1 = reinterpret_cast<IO_device*>(0Xff00);


// raw memory
void* my_allocator(size_t);

void f()
{
    // new allocation used as ints
    int* p = static_cast<int*>(my_allocator(100));
    // ...
}


//
char x = 'a';
// error : no implicit char* to int* conversion
int* p1 = &x;
// error : no implicit char* to int* conversion
int* p2 = static_cast<int*>(&x);
// ok : on your head be it
int* p3 = reinterpret_cast<int*>(&x);

struct B {
    /* ... */
};
struct D : B {
    /* ... */
};

// ok : implicit conversion from D* to B*
B* pb = new D;
// error : no implicit conversion from B* to D*
D* pd = pb;
// ok
D* pd = static_cast<D>(pb);



// section 11.5.3 : c-style cast
// (T)e, T is a type, e is an expression


// section 11.5.4 : function-style cast
void f(double d)
{
    // truncate d
    int i = int(d);
    // make a complex from d
    complex z = complex(d);
    // ...
}

void f(double d, char* p)
{
    // truncates
    int a = int(d);
    // not portable
    int b = int(p);
}
