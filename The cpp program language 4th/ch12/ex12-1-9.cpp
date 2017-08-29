/**************************************************************
* Name     :  ex12-1-9.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年5月18日
**************************************************************/



/*
example 12.3 : overloaded functions
*/


void print(double);
void print(long);

void f()
{
    // print(long)
    print(1L);
    // print(double)
    print(1.0);
    // error : ambiguous, print(long{1}) or print(double{1})
    print(1);
}


void print(int);
void print(const char*);
void print(long);
void print(double);
void print(char);

void h(char c, int i, short s, float f)
{
    // exact match : invoke print(char)
    print(c);
    // exact match : invoke print(int)
    print(i);
    // integral promotion : invoke print(int)
    print(s);
    // float to double promotion; print(double)
    print(f);
    // exact match : invoke print(char)
    print('a');
    // exact match : invoke print(int)
    print(49);
    // exact match : invoke print(int)
    print(0);
    // exact match : invoke print(const char*)
    print("a");
    // nullptr_t to const char* promotion : invoke print(const char*)
    print(nullptr);
}

void print_int(int);
void print_char(char);
void print_string(const char*);

void g(int i, char c, const char* p, double d)
{
    // ok
    print_int(i);
    // ok
    print_char(c);
    // ok
    print_string(p);
    // ok? calls print_int(int(c)), prints a numbewr
    print_int(c);
    // ok? calls print_char(char(i)), narrowing
    print_char(i);
    // error
    print_string(i);
    // ok? calls print_int(int(d)), narrowing
    print_int(d);
}


// section 12.3.2 : overloading and return type
float sqrt(float);
double sqrt(double);

void f(double da, float fla)
{
    // call sqrt(double)
    float f1 = sqrt(da);
    // call sqrt(double)
    double d = sqrt(da);
    // call sqrt(float)
    fl = sqrt(fla);
    // call sqrt(float)
    d = sqrt(fla);
}



// section 12.3.3 : overloading and scope
void f(int);

void g()
{
    void f(double);
    // call f(double)
    f(1);
}


struct Base {
    void f(int);
};

struct Derived : Base {
    void f(double);
};

void g(Derived* d)
{
    // call Derived::f(double);
    d.f(1);
}


// section 12.3.4 : resolution for multiple arguments
int pow(int, int);
double pow(double, double);
complex pow(double, complex);
complex pow(complex, int);
complex pow(complex, complex);

void k(complex z)
{
    // invoke pow(int, int)
    int i = pow(2, 2);
    // invoke pow(double, double)
    double d = pow(2.0, 2.0);
    // invoke pow(double, complex)
    complex z2 = pow(2, z);
    // invoke pow(complex, int)
    complex z3 = pow(z, 2);
    // invoke pow(complex, complex)
    complex z4 = pow(z, z);
    // error : ambiguous
    double d2 = pow(2.0, 2);
}



// section 12.3.5 : manual overload resolution
void f1(char);
void f1(long);

void f2(char*);
void f2(int*);

void k(int i)
{
    // ambiguous
    f1(i);
    // ambiguous
    f2(0);
}


inline void f1(int n) { f1(long(n)); }
f2(static_cast<int*>(0));

