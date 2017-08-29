/**************************************************************
* Name     :  ex28-1-2.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年7月19日
**************************************************************/



/*
example 28.1 : introduction
*/



// section 28.2 : type functions
if (is_polymorphic<int>::value) {
    cout << "Big surprise!";
}

enum class Axis : char { x, y, z };
enum flags {
    off, x = 1,
    y = x << 1;
    z = x << 2;
    t = x << 3;
};

// x is a char
typename std::underlying_type<Axis>::type x;
// y is probably an int
typename std::underlying_type<flags>::type y;

template<typename T, int N>
struct Array_type {
    using type = T;
    static const int dim = N;
    // ...
};

using Array = Array_type<int, 3>;

// x is an int
Array::type x;
// s = 3
constexpr int s = Array::dim;

template<int N>
struct Integer {
    using Error = void;
    using type = Select<N, Error, signed char, short, Error, int, Error, Error, Error, long>;
};

// 4-byte integer
typename Integer<4>::type i4 = 8;
// 1-byte integer
Integer<1>::type i1 = 9;

// max size of object we want on the stack
constexpr int on_stack_max = sizeof(std::string);

template<typename T>
struct Obj_holder {
    using type = typename std::conditional < (sizeof(T)<=on_stack_max), Scoped<T>, On_heap<T>>::type;
};

void f()
{
    // the double goes on the stack
    typename Obj_holder<double>::type v1;
    // the array v2 goes on the free store
    typename Obj_holder<array<double, 200>>::type v2;
    // ...
    // Scoped provides pointer-like access (* and [])
    *v1 = 7.7;
    // on-heap provides pointer-like access (* and [])
    v2[77] = 9.9;
    // ...
}

template<typename T>
struct On_heap {
    // allocate
    On_heap() : p(new T) { }
    // deallocate
    ~On_heap() { delete p; }
    T& operator*() { return *p; }
    T* operator->() { return p; }
    // prevent copying
    On_heap(const On_heap&) = delete;
    On_heap operator=(const On_heap&) = delete;
private :
    // pointer to object on the free store
    T* p;
};

template<typename T>
struct Scoped {
    T& operator*() { return x; }
    T* operator->() { return &x; }
    // prevent copying
    Scoped(const Scoped&) = delete;
    Scoped operator=(const Scoped&) = delete;
private :
    // the object
    T x;
};


// section 28.2.1 : type aliases
template<typename T>
using Holder = typename Obj_holder<T>::type;

void f2()
{
    // the double goes on the stack
    Holder<double> v1;
    // gthe array goes on the free store
    Holder<array<double, 200>> v2;
    // ...
    // Scoped provides pointer-like access
    *v1 = 7.7;
    // On+_heap provides pointer-like access
    v2[77] = 9.9;
}

template<typename C, typename T, typename F>
using Conditional = typename std::conditional<C, T, F>::type;


// section 28.2.1.1 : when not to use an alias
if (p) {
    p->f(7);
    // ...
}

conditional<
    is_integral<T>::value, make_unsigned<T>, Error<T>
>::type

Conditional<
    is_integral<T>::value, Delay<Make_unsigned, T>, Error<T>
>

template<template<typename...> class F, typename... Args>
using Delay = F<Args...>;


// section 28.2.2 : type predicates
template<typename T>
void copy(T* p, const T* q, int n)
{
    if (std::is_pod<T>::value) {
        // use optimized memory copy
        memcpy(p, q, n);
    }
    else {
        for (int i = 0; i != n; ++i) {
            // copy individual values
            p[i] = q[i];
        }
    }
}

template<typename T>
void copy(T* p, const T* q, int n)
{
    if (is_pod<T>())
    // ...
}

template<typename T>
void do_something()
{
    // error : is_pod<T>() is a type
    Conditional<is_pod<T>(), On_heap<T>, Scoped<T>> x;
    // ...
}

template<typename T>
constexpr bool Is_pod()
{
    return std::is_pod<T>::value;
}

template<typename T>
constexpr bool Is_big()
{
    return 100 < sizeof(T);
}

template<typename T>
using Obj_holder = Conditional<(Is_big<T>()), Scoped<T>, On_heap<T>>;


// section 28.2.3 : seclect a function
struct X {
    void operator()(int x)
    {
        cout << "X&" << x << "!";
    }
    // ...
};

struct Y {
    void operator()(int y)
    {
        cout << "Y" << y << "!";
    }
    // ...
};

void f()
{
    // make an X or a Y and call it
    Conditional<(sizeof(int)>4), X, Y>{}(7);
    using Z = Conditional<(Is_polymorphic<X>()), X, Y>;
    // make an X or a Y
    Z zz;
    // call an X or a Y
    zz(7);
}


// section 28.2.4 : traits
template<typename Iterator>
struct iterator_traits {
    using difference_type = typename Iterator::difference_type;
    using value_type = typename Iterator::value_type;
    using pointer = typename Iterator::pointer;
    using reference = typename Iterator::reference;
    using iterator_category = typename Iterator::iterator_category;
};

template<typename Iter>
Iter search(Iter p, Iter q, typename iterator_traits<Iter>::value_type val)
{
    typename iterator_traits<Iter>::difference_type m = q - p;
    // ...
}

template<typename T>
using Value_type = typename std::iterator_trait<T>::value_type;

template<typename T>
using Difference_type = typename std::iterator_trait<T>::difference_type;

template<typename T>
using Iterator_category = typename std::iterator_trait<T>::iterator_category;

template<typename Iter>
Iter search(Iter p, Iter q, Value_type<Iter> val)
{
    Difference_type<Iter> m = q - p;
    // ...
}

template<typename Iter, typename Val>
Iter search(Iter p, Iter q, Val val)
{
    // if we don't need to name *p's type
    auto x = *p;
    // if we don't need to name q-p's type
    auto m = q - p;
    // if we want to name *p's type
    using difference_type = decltype(*p);
    // if we want to name q-p's type
    using value_type = decltype(q-p);
    // ...
}

