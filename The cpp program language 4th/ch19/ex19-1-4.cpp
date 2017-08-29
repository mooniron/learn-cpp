/**************************************************************
* Name     :  ex19-1-4.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年6月25日
**************************************************************/



/*
example 19.4 : friends
*/


// max row and column size
constexpr int rc_max {4};

class Matrix;
class Vector {
    float v[rc_max];
    // ...
    friend Vector operator*(const Matrix&, const Vector&);
};

class Matrix {
    Vector v[rc_max];
    // ...
    friend Vector operator*(const Matrix&, const Vector&);
};


Vector operator*(const Matrix& m, const Vector& v)
{
    Vector r;
    for (int i = 0; i != rc_max; i++) {
        // r[i] = m[i] * v;
        r.v[i] = 0;
        for (int j = 0; j != rc_max; j++) {
            r.v[i] += m.v[i].v[j] * v.v[j];
        }
    }
    return r;
}


class List_iterator {
    // ...
    int* next();
};

class List {
    friend int* List_iterator::next();
    // ...
};

class List {
    friend class List_iterator;
    // ...
};


template<typename T>
class X {
    friiend T;
    // redundant "class"
    friend class T;
    // ...
};


// section 19.4.1 : finding friends
// will become friend of N::C
class C1 {};
// will become friend of N::C
void f1();

namespace N {
    // will become friend of C
    class C2 {};
    // will become friend of C
    void f2();

    class C {
        int x;
    public :
        // OK (previously defined)
        friend class C1;
        friend void f1();
        // OK (defined in enclosing namespace)
        friend class C3;
        friend void f3();
        // first declared in N and assumed to be in N
        friend class C4;
        friend void f4();
    };

    // friend of C3
    class C3 {};
    // OK, friend of C
    void f3() { C x; x.x = 1; }
}   // namespace N

// not friend of N::C
class C4 {};
// error : x is private and f4() is not a friend of N::C
void f4()
{
    N::C x;
    x.x = 1;
}


void f(Matrix& m)
{
    // Matrix's friend invert()
    invert(m);
}


// no f() in this scope
class X {
    // useless
    friend void f();
    // can be found through its argument
    friend void h(const X&);
};

void g(const X& x)
{
    // no f() in scope
    f();
    // X's friend h()
    h(x);
}


// section 19.4.2 : friends and members
class X {
    // ...
    X(int);

    // member
    int m1();
    // member
    int m2() const;

    // friend, not member
    friend int f1(X&);
    friend int f2(const X&);
    friend int f3(X);
};

void g()
{
    // error : X(99).m1() not tried
    99.m1();
    // error : X(99).m2() not tried
    99.m2();
}

void h()
{
    // error : f1(X(99)) not tried : non-const X& argument
    f1(99);
    // ok
    f2(99);
    // ok : f3(X(99)) : X argument
    f3(99);
}

