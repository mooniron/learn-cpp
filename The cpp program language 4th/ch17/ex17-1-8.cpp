/**************************************************************
* Name     :  ex17-1-8.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年6月10日
**************************************************************/



/*
example 17.6 : generating default operations
*/


// section 17.6.1 : explicit defaults
class gslice {
    valarray<size_t> size;
    valarray<size_t> stride;
    valarray<size_t> d1;
public :
    gslice() = default;
    ~gslice() = default;
    gslice(const gslice&) = default;
    gslice(gslice&&) = default;
    gslice& operator=(const gslice&) = default;
    gslice& operator=(gslice&&) = default;
    // ...
};

class gslice {
    valarray<size_t> size;
    valarray<size_t> stride;
    valarray<size_t> d1;
public :
    // ...
};

class gslice {
    valarray<size_t> size;
    valarray<size_t> stride;
    valarray<size_t> d1;
public :
    // ...
    gslice(const gslice& a);
};

gslice::gslice(const gslice& a)
    : size {a.size}, stride {a.stride}, d1 {a.d1}
{
}


// section 17.6.2 : default operations
struct S {
    string a;
    int b;
};

S f(S arg)
{
    // default struction {"", 0}
    S s0 {};
    // copy construction
    S s1 {s0};
    // copy assignment
    s1 = arg;
    // move construction
    return s1;
}


// section 17.6.3 : using default operations
// section 17.6.3.1 : default constructors
struct X {
    // require an int to initialize an X
    X(int);
};

// OK
X a {1};
// error : no default constructor
X b {};

struct Y {
    string s;
    int n;
    // initialize Y with a string
    Y(const string& s);
    // allow default initialization with the default meaning
    Y() = default;
};


// section 17.6.3.2 : maintaining invariants
struct Z {
    // invariant :
    // my_favorite is the index of my favorite element of elem
    // the largest points to the element with the highest value in elem
    vector<int> elem;
    int my_favorite;
    int* largest;
};

// no initialization  (oops! possibility of undefined values)
Z v0;
// ok but ugly and error-prone
Z val {{1, 2, 3}, 1, &val[2]};
// copies v2 .largest points into val
Z v2 = val;
// moves val.elem becomes empty; val.my_favorite is out of range
z v3 = move(val);


// section 17.6.3.3 : resource invariants
template<class T>
class Handle {
    T* p;
public :
    Handle(T* pp) : p {pp} { }
    T& operator*() { return *p; }
    ~Handle() { delete p; }
};

vid f1()
{
    Handle<int> h {new int {99}};
    // ...
}

void f2()
{
    // error : no default constructor
    Handle<int> h;
    // ...
}

void f3()
{
    Handle<int> h1 {new int {7}};
    // error : no copy constructor
    Handle<int> h2 {h1};
    // ...
}

template<class T>
class Handle {
    // ...
    // clone
    Handle(const T& a) : p {new T {*a.p}} { }
};


// section 17.6.3.4 : partially specified invariants
class Tic_tac_toe {
public :
    // always 9 positions
    Tic_tac_toe() : pos(9) { }
    // default copy constructor
    Tic_tac_toe& operator=(const Tic_tac_toe& arg)
    {
        for (int i = 0; i < 9; ++i) {
            pos.at(i) = arg.pos.at(i);
        }
        return *this;
    }
    // ... other operations ...
    enum State {empty, nought, cross};
private :
    vector<State> pos;
};

// section 17.6.3.4 : partially specified invariants
class Tic_tac_toe {
public :
    // always 9 positions
    Tic_tac_toe() : pos(9) { }
    // default copy constructor
    Tic_tac_toe(const Tic_tac_toe&) = default;
    // copy assignment
    Tic_tac_toe& operator=(const Tic_tac_toe& arg) = default;
    ~Tic_tac_toe() = default;
    // ... other operations ...
    enum State {empty, nought, cross};
private :
    vector<State> pos;
};


// section 17.6.3.4 : partially specified invariants
class Tic_tac_toe {
public :
    // ... other operations ...
    enum State {empty, nought, cross};
private :
    // always 9 positions
    vector<State> pos {vector<State> (9)};
};



// section 17.6.4 : deleted functions
class Base {
    // ...
    // disallow copying
    Base& operator=(const Base&) = delete;
    Base(const Base&) = delete;
    // disallow moving
    Base& operator=(Base&&) = delete;
    Base(Base&&) = delete;
};

Base x1;
// error : no copy constructor
Base x2 {x1};


template<class T>
// return copy of *p
T* clone(T* p)
{
    return new T {*p};
}

// don't try to clone a Foo
Foo* clone(Foo*) = delete;

void f(Shape* ps, Foo* pf)
{
    // fine
    Shape* ps2 = clone(ps);
    // error : clone(Foo*) deleted
    Foo* pf2 = clone(pf);
}


// eliminate an undesired conversion
struct Z {
    // ...
    // can initialize with a double
    Z(double);
    // but not with an integer
    Z(int) = delete;
};

void f()
{
    // error : Z(int) deleted
    Z z1 {1};
    // ok
    Z z2 {1.0};
}


class Not_on_stack {
    // ...
    ~Not_on_stack() = delete;
};

class Not_on_free_store {
    // ...
    void* operator new(size_t) = delete;
};

void f()
{
    // error : can't destroy
    Not_on_stack v1;
    // ok
    Not_on_free_store v2;
    // ok
    Not_on_stack* p1 = new Not_on_stack;
    // error : can't allocate
    Not_on_free_sore* p2 = new Not_on_free_store;
}
