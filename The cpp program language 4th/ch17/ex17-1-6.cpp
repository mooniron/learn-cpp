/**************************************************************
* Name     :  ex17-1-6.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年6月10日
**************************************************************/



/*
example 17-5 : copy and move
*/


// section 17.5.1 : copy
template<class T>
class Matrix {
    // two dimensions
    array<int, 2> dim;
    // pointer to dim[0] * dim[1] elements of type T
    T* elem;
public :
    // simplified (no error handling)
    Matrix(int d1, int d2) : dim {d1, d2}, elem {new T [d1 * d2]} { }
    int size() const { return dim[0] * dim[1]; }
    // copy constructor
    Matrix(const Matrix&);
    // copy assignment
    Matrix& operator=(const Matrix&);
    // move constructor
    Matrix(Matrix&&);
    // move assignment
    Matrix& operator=(Matrix&&);
    // destructor
    ~Matrix() { delete[] elem; }
    // ...
};

// copy constructor
template<class T>
Matrix::Matrix(const Matrix& m)
    : dim {m.dim}, elem {new T[m.size()]}
{
    // copy elements
    uninitialized_copy(m.elem, m.elem + m.size(), elem);
}

// copy assignment
template<class T>
Matrix& Matrix::operator=(const Matrix& m)
{
    if (dim[0] != m.dim[0] || dim[1] != m.dim[1]) {
        throw runtime_error("bad size in Matrix =");
    }
    // copy elements
    copy(m.elem, m.elem + m.size(), elem);
}

// copy assignment : strong guarantee
Matrix& Matrix::operator=(const Matrix& m)
{
    // make a copy
    Matrix tmp {m};
    // swap tmp's representation with *this's
    swap(tmp, *this);
    return *this;
}


// section 17.5.1.1 : beware of default constructors
class X {
    string s;
    string s2;
    vector<string> v;

    // copy constructor
    X(const X& a)
        // probably sloppy and probably wrong
        : s {a.s}, v {a.v}
    {
    }
    // ...
};


// section 17.5.1.2 : copy of bases
struct B1 {
    B1();
    B1(const B1&);
    // ...
};

struct B2 {
    B2(int);
    B2(const B2&);
    // ...
};

struct D : B1, B2 {
    D(int i) : B1 {}, B2 {i}, m1 {}, m2 {2 * i} { }
    D(const D& a) : B1 {a}, B2 {a}, m1 {a.m1}, m2 {a.m2} { }
    B1 m1;
    B2 m2;
};

// construct with int argument
D d {1};
// copy construct
D dd {d};


//section 17.5.1.3 : the meaning of copy
struct S {
    // a pointer
    int* p;
};

S x {new int {0}};

void f()
{
    // "copy" x
    S y {x};
    // change y; affects x
    *y.p = 1;
    // change x; affects y
    *x.p = 2;
    // affects x and y
    delete y.p;
    // ok : change y; does not affect x
    y.p = new int {3};
    // oops : write to deallocated memory
    *x.p =4;
}

struct S2 {
    shared_ptr<int> p;
};

S2 x {new int {0}};

void f()
{
    // "copy" x
    S2 y {x};
    // change y, affects x
    *y.p = 1;
    // change x; affects y
    *x.p = 2;
    // change y; affects x
    y.p.reset(new int {3});
    // change x; affects y
    *x.p = 4;
}


class Image {
public :
    // copy constructor
    Image(const Image& a);
    // ...
    void write_block(Descriptor);
    // ...
privagte :
    // copy *rep
    Representation* clone();
    Representation* rep;
    bool shared;
};

// do shallow copy and prepare for copy-on-write
Image::Image(const Image& a)
    : rep {a.rep}, shared {true},
{
}

void write_block(Descriptor d)
{
    if (shared) {
        // make a copy of *rep
        rep = clone();
        // no more sharing
        shared = false;
    }
    // ... now we can safely write to our own copy of rep
}


// section 17.5.1.4 : slicing
struct Base {
    int b;
    Base(const Base&);
    // ...
};

struct Derived : Base {
    int d;
    Derived(const Derived&);
    // ...
};

void naive(Base* p)
{
    // may slice : invokes Base::Base(const Base&)
    Base b2 = *p;
    // ...
}

void user()
{
    Derived d;
    naive(&d);
    // slices : invokes Base::Base(const Base&), not Derived::Derived(const Derived&)
    Base bb = d;
    // ...
}

