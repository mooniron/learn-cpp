/**************************************************************
* Name     :  ex26-1-3.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年7月17日
**************************************************************/



/*
example 26.3 : name binding
*/


bool tracing;
template<typename T>
T sum(std::vector<T>& v)
{
    T t {};
    if (tracing) {
        cerr << "sum(" << &v << ")\n";
    }
    for (int i = 0; i != v.size(); i++) {
        t = t + v[i];
    }
    return t;
}
// ...

#include<quad.h>
void f(std::vector<Quad>& v)
{
    Quad c = sum(v);
}


// section 26.3.1 : dependent names
template<typename T>
T f(T a)
{
    // ok : a is a dependent name and therefore so is g
    return g(a);
}

class Quad { /* ... */ };
void g(Quad);
// f's g is bound to g(Quad)
int z = f(Quad{2});

template<typename T>
T ff(T a)
{
    // error : no gg() in scope and gg(Quad{1}) doesn't depend on T
    return gg(Quad{1});
}

int gg(Quad);

int zz = ff(Quad{2});

template<typename Container>
void fct(Container& c)
{
    // syntax error : value_type is assumed to be a non-type name
    Container::value_type v1 = c[7];
    // ok : value_type assumed to name a type
    typename Comtainer::value_type v2 = c[9];
    // ok : let the compiler figure it out
    auto v3 = c[11];
    // ...
}

template<typename T>
using Value_type<T> = typename T::value_type;

template<typename Container>
void fct2(Container& c)
{
    // ok
    Value_type<Container> v1 = c[7];
    // ...
}


// some allocator
class Pool {
public :
    template<typename T> T* get();
    template<typename T> void release(T*);
    // ...
};

template<typename Alloc>
void f(Alloc& all)
{
    // syntax error : get is assumed to name a non-template
    int* p1 = all.get<int>();
    // ok : get() is assumed to be a template
    int* p2 = all.template get<int>();
    // ...
}

void user(Pool& pool)
{
    f(pool);
     // ...
}


// section 26.3.2 : point-of-definition binding
int x;

template<typename T>
T f(T a)
{
    // ok : x is in scope
    ++x;
    // error : no y in sopce, and y doesn't depend on T
    ++y;
    // ok : a is dependent
    return a;
}

int y;

int z = f(2);

void g(double);
void g2(double);

template<typename T>
int ff(T a)
{
    // call g2(double)
    g2(2);
    // error : no g3() in scope
    g3(2);
    // call g(double), g(int) is in scope
    g(2);
    // ...
}

void g(int);
void g3(int);

int x = ff(a);


// 26.3.3 : point-of-instantiation binding
void g(int);

template<typename T>
void f(T a)
{
    // g is bound at a point of instantiation
    g(a);
}

void h(int i)
{
    extern void g(double);

    f(i);
}    // point of declaration for f<int>


void g(int);

template<typename T>
void f(T a)
{
    // g is bound at a point of instantiation
    g(a);
    if (i) {
        // h is bound at a point of instantiation
        h(a - 1);
    }
}

void h(int i)
{
    extern void g(double);
    f(i);
}   // point of declaration for f<int>


template<typename T>
class Container {
    // elements
    vector<T> v;
public :
    // sort elements
    void sort();
    // ...
};  // point of instantiation of Container<int>

void f()
{
    // point of use
    Container<int> c;
    c.sort();
}

void fff()
{
    struct S { int a, b; };
    vector<S> vs;
    // ...
}


template<typename T>
void print_sorted(vector<T>& v)
{
    sort(v.begin(), v.end9));
    for (const auto T& x : v) {
        cout << x << '\n';
    }
}

void use(vector<string>& vec)
{
    // ...
    // sort using std::sort, then print using std::cout
    print_sorted(vec);
}

template<typename T, typename S>
void print_sorted(vector<T>& v, S sort, ostream& os)
{
    sort(v.begin(), v.end());
    for (const auto T& x : v) {
        os << x << '\n';
    }
}

void fct(vector<string>& vec)
{
    // ...
    // vec's iterator type
    using Iter = decltype(vs.begin);
    //
    print_sorted(some_vec, std::sort<Iter>, std::cout);
}


// section 26.3.4 : multiple instantiation points
// here, I take care of ints
void f(int);

namespace N {
    class X {};
    char g(X, int);
}

template<typename T>
void ff(T t, double d)
{
    // f is bound to f(int)
    f(d);
    // g might be bound to g(X, int)
    return g(t, d);
}

// ff<N::X, double> may bind g to N::g(X, int) narrowing 1.1 to 1
auto x1 = ff(N::X{}, 1.1);

// reopen N to take care of doubles
namespace N {
    double g(X, double);
}

// ff<N::X, double> binds g to N::g(X, double) the best match
auto x2 = ff(N::X, 2.2);


// section 26.3.5 : templates and namespaces
namespace N {
    class A { /* ... */ };
    char f(A);
}

char f(int);

template<typename T>
char g(T t)
{
    // choose f() depending an what T is
    return f(t);
}

char f(double);

// causes N::f(N::A) to be called
char c1 = g(N::A());
// causes f(int) to be called
char c2 = g(2);
// causes f(int) to be called; f(double) not considered
// argument dependent lookup can not find a global function taking only built-in types
char c3 = g(2.1);


// section 26.3.6 : overaggressive ADL
#include <iostream>

int main()
{
    // ok : because of ADL
    std::cout << "Hello, world" << endl;
}

#include <vector>
#include <algorithm>
// ...

namespace User {
    class Customer { /* ... */ };
    using Index = std::vector<Customer*>;
    // deep or shallow copy depending on the value of deep
    void copy(const Index&, Index&, int deep);
    void algo(Index& x, Index& y)
    {
        // ...
        // error
        copy(x, y, false);
    }
}

// std
template<typename In, typename Out>
Out copy(In, In, Out);

// concept
template<typename In, typename Out>
Out copy(In p1, In p2, Out q)
{
    static_assert(Input_iterator<In>(), "copy(): In is not an input iterator");
    static_assert(Output_iterator<Out>(), "copy() : Out is not an output iterator");
    static_assert(Assignable<Value_type<Out>, Value_type<In>>(), "copy(): value type mismatch");
    // ...
}

template<typename In, typename Out,
    typename = enable_if(Input_iterator<In>() && Output_iterator<Out>())
    && Assignable<Value_type<Out>, Value_type<In>>()
>
Out copy(In p1, In p2, Out q)
{
    // ...
}

void User::algo(Index& x, Index& y)
{
    // ok
    User::copy(x, y, false);
    // ...
    // ok : only std::swap is considered
    std::swap(*x[i], *x[j]);
}


template<typename Range, typename Op>
void apply(const Range& r, Op f)
{
    using std::begin;
    using std::end;
    for (auto& x : r) {
        f(x);
    }
}


// section 26.3.7 : names from base classes
void g(int);

struct B {
    void g(char);
    void h(char);
};

// base class not depend a template argument
template<typename T>
class X : public B {
public :
    void h(int);
    void f()
    {
        // call B::g(char)
        g(2);
        // call X::h(int)
        h(2);
    }
    // ...
};

void g(int);

struct B {
    void g(char);
    void h(char);
};

// base class depending a template argument
template<typename T>
class X : public T {
public :
    void f()
    {
        // call g(int)
        g(2);
    }
    // ...
};

void h(X<B> x)
{
    x.f();
}


void g(int);
void g2(int);

struct B {
    using Type = int;
    void g(char);
    void g2(char);
};

template<typename T>
class X : public T {
public :
    // ok
    typename T::Type m;
    // error : no Type in scope
    Type m2;
    // bring T::g2() into scope
    using T::g2();
    void f()
    {
        // call T;:g
        this->g(2);
        // call ::g(int); surprise?
        g(2);
        // call T::g2
        g2(2);
    }
    // ...
};

void h(X<B> x)
{
    x.f();
}

// memory for matrices,  operations of all elements
template<typename T>
class Matrix_base {
    // ...
    int size() const { return sz; }
protected :
    // number of elements
    int sz;
    // matrix elements
    T* elem;
};

// N-dimensional matrix
template<typename T, int N>
class Matrix : public Matrix_base<T> {
    // ...
    // return pointer to element storage
    T* data()
    {
        return this->elem;
    }
};

