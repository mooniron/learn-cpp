/**************************************************************
* Name     :  ex23-1-4.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年7月12日
**************************************************************/



/*
example 23.4 : class template members
*/


// section 23.4.1 data members
template<typename T>
struct X {
    int m1 = 7;
    T m2;
    X(const T& x) : m2 {x} { }
};

X<int> xi {9};
X<string> xs {"Rapperswil"};


// section 23.4.2 : member functions
template<typename T>
struct X {
    // defined in class
    void mf1() { /* ... */ };
    void mf2();
};

// defined out of class
template<typename T>
void X<T>::mf2() { /* ... */ }


// section 23.4.3 : member type aliases
template<typename T>
class Vector {
public :
    using value_type = T;
    // Vector_iter<T> is defined elsewhere
    using iterator = Vector_iter<T>;
    // ...
};


// section 23.4.4 : static members
template<typename T>
struct X {
    // Point must be a literal type
    static constexpr Point p {100, 250};
    static const int m1 = 7;
    // error : not const
    static int m2 = 8;
    static int m3;
    static void f1() { /* ... */ }
    static void f2();
};

// error : two initializers
template<typename T> int X<T>::m1 = 99;
template<typename T> int X<T>::m3 = 99;
template<typename T>
void X::<T>::f2() { /* ... */ }

template<typename T>
struct X {
    static int a;
    static int b;
};

int* p = &X<int>::a;


// section 23.4.5 : member types
template<typename T>
struct X {
    enum E1 {a, b};
    // error : underlying type not known
    enum E2;
    enum class E3;
    enum E4 : char;
    struct C1 { /* .... */ };
    struct C2;
};

// needed
template<typename T>
enum class X<T>::E3 {a, b};

// needed
template<typename T>
enum class X<T>::E4 : char {x, y};
// needed
template<typename T>
struct X<T>::C2 { /* ... */ };



// section 23.4.6 : member templates
template<typename Scalar>
class complex {
    Scalar re, im;
public :
    // default constructor
    complex() : re {}, im {} { }
    template<typename T>
    complex(T rr, T ii = 0) : re {rr}, im {ii} { }
    // copy constructor
    complex(const complex&) = default;
    template<typename T>
    complex(const complex<T>& c) : re {c.real()}, im {c.imag()} { }
    // ...
};

// default value
complex<float> cf;
// ok : uses float to double conversion
complex<double> cd {cf};
// error : no implicit double->float conversion
complex<float> cf2 {cd};
// error : no implicit double->float conversion
complex<float> cf3 {2.0, 3.0};
// ok, uses float to double conversion
complex<double> cd2 {2.0F, 3.0F};

class Quad {
    // no conversion to int
};

complex<Quad> cq;
// error : no Quad to int conversion
complex<int> ci {cq};

// old style : allow narrowing errors
template<typename Scalar>
class complex {
    Scalar re, im;
public :
    complex() : re(0), im(0) { }
    template<typename T>
    complex(T rr, T ii = 0) : re(rr), im(ii) { ]
    // copy constructor
    complex(const complex&) = default;
    template<typename T>
    complex(const complex<T>& c) : re(c.real()), im(c.imag()) { }
    // ...
};

// ouch! narrows
complex<float> cf4 {2.1, 2.9};
// ouch! narrow
complex<float> cf5 {cd};


// section 23.4.6.1 : templates and constructors
// section 23.4.6.2 : templates and virtual
class Shape {
    // ...
    // error : virtual template
    template<typename T>
    virtual bool intersect(const T&) const = 0;
};


// section 23.4.6.3 : use of nesting
template<typename T, typename Allocator>
class List {
private :
    struct Link {
        T val;
        Link* succ;
        Link* prev;
    };
    // ...
};


template<typename T, typename Allocator>
class List;

template<typename T>
class Link {
    template<typename U, typename A>
    friend class List;
    T val;
    Link* succ;
    Link* prev;
};

template<typename T, typename Allocator>
class List {
    // ...
};

template<typename T, typename Allocator>
class List {
    // ...
};

class List {
public :
    class Iterator {
        Link<T>* current_position;
    public :
        // ... usual iterator operations
    };

    Iterator<T, A> begin();
    Iterator<T, A> end();
    // ...
};

// error : List takes two arguments
void fct(List<int>::Iterator b, List<int>::Iterator e)
{
    auto p = find(b, e, 17);
    // ...
}

void user(List<int, My_allocator>& lm, List<int, Your_allocator>& ly)
{
    fct(lm.begin(), lm.end());
    fct(ly.begin(), ly.end());
}

void fct(List<int, My_allocator>::Iterator b, List<int, My_allocator>::Iterator e)
{
    auto p = find(b, e, 17);
    // ...
}

void user(List<int, My_allocator>& lm, List<int, Your_allocator>& ly)
{
    fct(lm.begin(), lm.end());
    // error : fct takes List<int, My_allocator>::Iterators
    fct(ly.begin(), ly.end());
}


template<typename T>
struct Iterator {
    Link<T>* current_position;
};

template<typename T, typename A>
class List {
public :
    Iterator<T> begin();
    Iterator<T> end();
    // ....
};



// section 23.4.7 : friends
template<typename T> class Matrix;
template<typename T>
class Vector {
    T v[4];
public :
    friend vector operator*<>(const Matrix<T>&, const vecgtor&);
    // ...
};

template<typename T>
class Matrix {
    Vector<T> v[4];
public :
    friend Vector<T> operator*<>(const Matrix&, const Vector<T>&);
    // ...
};

template<typename T>
Vector<T> operator*(const Matrix<T>& m, const Vector<T>& v)
{
    Vector<T> r;
    // use m.v[i] and v.v[i] for direct access to elements
    return r;
}


class C;
using C2 = C;

template<typename T>
class My_class {
    // ok : C is a class
    friend C;
    // ok : C2 is an alias for a class
    friend C2;
    // error : no class C3 in scope
    friend C3;
    // ok : introduces a new class C4
    friend class C4;
};

template<typename T>
class my_other_class {
    // my argument is my friend!
    friend T;
    // My_class with the corresponding argument is my friend
    friend My_class<T>;
    // error : redundant "class"
    friend class T;
};


template<typename T, typename A>
class List;

template<typename T>
class Link {
    template<typename U, typename A>
    friend class List;
    // ...
};

