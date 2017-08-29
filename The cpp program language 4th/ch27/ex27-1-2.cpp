/**************************************************************
* Name     :  ex27-1-2.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年7月18日
**************************************************************/



/*
example 27.1 : introduction
example 27.2 : parameterization and hierarchy
*/


// interface expressed in terms of the parameter
template<typename X>
class Ct {
    X mem;
public :
    X f();
    int g();
    void h(X);
};

// specialization for A
template<>
class Ct<A> {
    // the representation can differ from that of the primary template
    A* mem;
public :
    A f();
    int ();
    void h(A);
    // added functionality
    void k(int);
};

// specialization for A
Ct<A> cta;
// specialization for B
Ct<B> ctb;


class X {
    // ...
};

// interface expressed in terms of types in scope
class Cx {
    X mem;
public :
    virtual X& f();
    virtual int g() ;
    virtual void h(X&);
};

// derived class
class DA : public Cx {
public :
    X& f();
    int g();
    void h(X&);
};

// derived class
class DB : public Cx {
    // representation can be more extensive than what the base provides
    DB* p;
public :
    X& f();
    int g();
    void h(X&);
    // added functionality
    void k(int);
};

// cxa is an interface to a DA
CX& cxa {*new DA};
// cxb is an interface to a DB
Cx& cxb {*new DB};


// SECTION 27.2.1 : generated types
class Shape {
    // ...
};

class Circle : public Shape {
    // ...
};

class Triangle : public Shape {
    // ...
};

void f(set<Shape*>& s)
{
    // ...
    s.insert(new Triangle{p1, p2, p3});
}

void g(set<Circle*>& s)
{
    // error : type mismatch s is a set<Circle*>, not a set<Shape*>
    f(s);
}

// Danger
void maul(Shape* p, int n)
{
    for (int i = 0; i != n; ++i) {
        // looks innocent, it is not
        p[i].draw();
    }
}

void user()
{
    // an image is composed of 10 Circles
    Circle image[10];
    // ...
    // "maul" Circles
    maul(image, 10);
    // ...
}


// section 27.2.2 : template conversions
// pointer to T
template<typename T>
class Ptr {
    T* p;
public :
    Ptr(T*);
    // copy constructor
    Ptr(const Ptr&);
    // convert Ptr<T> to Ptr<T2>
    template<typename T2>
    explicit operator Ptr<T2>();
    // ...
};

void f(Ptr<Circle> pc)
{
    //  should work
    Ptr<Shape> ps {pc};
    // should give error
    Ptr<Circle> pc2 {ps};
}

template<typename T>
template<typename T2>
Ptr<T>::operator Ptr<T2>()
{
    return Ptr<T2>{p};
}

void f(Ptr<Circle> pc)
{
    // ok : can convert Circle* to Shape*
    Ptr<Shape> ps {pc};
    // error : cannot convert Shape* to Circle*
    Ptr<Circle> pc2 {ps};
}

// error
template<typename T, typename T2>
Ptr<T>::operator Ptr<T2>()
{
    return Ptr<T2>(p);
}

