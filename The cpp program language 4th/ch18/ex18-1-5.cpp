/**************************************************************
* Name     :  ex18-1-5.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年6月18日
**************************************************************/



/*
example 18.4 : type conversion
*/


// secgtion 18.4.1 : conversion operators
class Tiny {
    char v;
    void assign(int i)
    {
        if (i & ~077) {
            throw Bad_range();
        }
        v = i;
    }
public :
    class Bad_range { };
    Tiny(int i) { assign(i); }
    Tiny& operator=(int i)
    {
        assign(i);
        return *this;
    }
    // conversion to int function
    operator int() const { return v; }
};


int main()
{
    Tiny c1 = 2;
    Tiny c2 = 62;
    // c3 = 60
    Tiny c3 = c2 - c1;
    // no range check (not necessary)
    Tiny c4 = c3;
    // i = 64
    int i = c1 + c2;
    // range error : c1 cna't be 64
    c1 = c1 + c2;
    // i = -4
    i = c3 -64;
    // range error : c2 can't be -4
    c2 = c3 -64;
    // no range check (not necessary)
    c3 = c4;
}


int operator+(Tiny, Tiny);

void f(Tiny t, int i)
{
    // error, amiguous : "operator+(t, Tiny(i))" or "int(t) + i"?
    t + i;
}



// section 18.4.2 : explicit conversion operators
template<typename T, typename D = default_delete<T>>
class unique_ptr {
public :
    // ...
    // does *this hold a pointer (that is not nullptr)?
    explicit operator bool() const noexcept;
    // ...
};

void use(unique_ptr<Record> p, unique_ptr<int> q)
{
    // ok : we ant this use
    if (!p) {
        throw Invalid_unique_ptr();
    }
    // error : suspicious use
    bool b = p;
    // error : we definitly don't want this
    int x = p + q;
}



// section 18.4.3 : ambiguities
class X {
    /* ... */
    X(int);
    X(const char*);
};
class Y {
    /* ... */
    Y(int);
};
class Z {
    /* ... */
    Z(X);
};

X f(X);
Y f(Y);
Z g(Z);

void k1()
{
    // error : ambiguous : f(X(1)) or f(Y(1))
    f(1);
    // OK
    f(X(1));
    // OK
    f(Y(1));
    // error : two user-defined conversions needed; g(Z{X{"Mack"}}) not tried
    g("Mack");
    // ok : g(Z{X{"Doc"}})
    g(X{"Doc"});
    // ok : g(Z{X{"Suzy"}})
    g(Z{"Suzy"});
}


class XX {
    /* ... */
    XX(int);
};

void h(double);
void h(XX);

void f2()
{
    // h(doubl{1}) or h(XX{1})? h(double{1})!
    h(1);
}


class Quad {
public :
    Quad(double);
    // ...
};

Quad operator+(Quad, Quad);

void f(double a1, double a2)
{
    // double-precision floating-point add
    Quad r1 = a1 + a2;
    // force quad arithmetic
    Quad r2 = Quad{a1} + a2;
}


class Real {
public :
    operator double();
    operator int();
    // ...
};

void g(Real a)
{
    // d = a.double()
    double d = a;
    // i = a.int()
    int i = a;
    // d = a.double();
    d = a;
    // i = a.int();
    i = a;
}


