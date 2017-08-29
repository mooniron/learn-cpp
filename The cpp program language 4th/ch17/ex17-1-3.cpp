/**************************************************************
* Name     :  ex17-1-3.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年6月10日
**************************************************************/



/*
example 17.2 : constructors and destructors
*/


#include <string>

using namespace std;


struct Tracer {
    string mess;
    Tracer(const string& s) : mess{s} { clog << mess; }
    ~Tracer() { clog << "~" << mess; }
};

void f(consgt vector<int>& v)
{
    Tracer tr {"in f()\n"};
    for (auto x : v) {
        Tracer tr {string{"v loop"} + to<string>(x) + '\n'};
        // ...
    }
}


// section 17.2.1 constructors and invariants
struct S {
    // fine
    S();
    // error : no type can be specified for a constructor
    void S(int);
    // error : the class name  must denote a constructor
    int S;
    // error : the class name must denote a constructor
    enum S { foo, bar };
};


class Vector {
public :
    Vector(int s);
    // ...
private :
    // elem points to an array of sz doubles
    double* elem;
    // sz is non-negative
    int sz;
};


Vector::Vector(int s)
{
    if (s < 0) {
        throw Bad_size {s};
    }
    sz = s;
    elem = new double[s];
}



// section 17.2.2 : destructors and resources
class Vector {
public :
    // onstructor acquire memory
    Vector(int s) : elem {new double[s]}, sz {s} { };
    // destructor : release memory
    ~Vector() { delete[] elem; }
    // ...
private :
    // elem points to an array of sz doubles
    double* elem;
    // sz is non-negative
    int sz;
};


Vector* f(int s)
{
    Vector v1(s);
    // ...
    return new Vector(s + s);
}

void g(int ss)
{
    Vector* p = f(ss);
    // ...
    delete p;
}


// section 17.2.3 base and member destructors
struct S1 {
    string s;
};

// ok : s.s is initialized to ""
S1 x;

struct X { X(int); };
struct S2 {
    X x;
};

// error
S2 x1;
// ok : x2.x is initialized with {1}
S2 x2 {1};


// section 17.2.4 : calling constructors and destructors
void C::push_back(const X& a)
{
    // ...
    // copy construct an X with the value a in address p
    new(p) X{a};
    // ...
}

void C::pop_back()
{
    // ...
    // destroy the X in address p
    p->~X();
}


class Nonlocal {
public :
    // ...
    // explicit destruction
    void destroy()
    {
        this->~Nonlocal();
    }
private :
    // ...
    // don't destroy implicitly
    ~Nonlocal();
};

void user()
{
    // error : cannot destroy a Nonlocal
    Nonlocal x;
    // ok
    X* p = new Nonlocal;
    // ...
    // error : cannot destroy a Nonlocal
    delete p;
    // ok
    p.destroy();
}


// section 17.2.5 virtual destructors
class Shape {
public :
    // ...
    virtual void draw() = 0;
    virtual ~Shape();
};

class Circle {
public :
    // ...
    void draw();
    // overrides ~Shape()
    ~Circle();
    // ...
};

void user(Shape* p)
{
    // invoke the appropriate draw()
    p->draw();
    // invoke the appropriate destructor
    delete p;
    // ...
}


