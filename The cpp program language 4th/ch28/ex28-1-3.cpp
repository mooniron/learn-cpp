/**************************************************************
* Name     :  ex28-1-3.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年7月19日
**************************************************************/



/*
example 28.3 : control structures
*/



// section 28.3.1 : selection

// section 28.3.1.1 : selecting between two types
// general template
template<bool C, typename T, typename F>
struct conditional {
    using type = T;
};

// specialization for false
template<typename T, typename F>
struct conditional<false, T, F> {
    using type = F;
};

template<bool B, typename T, typename F>
using Condtidional = typename std::conditional<B, T, F>::type;

Conditional<(Is_polymorphic<T>()), X, Y> z;


// section 28.3.1.2 : compile time vs run time
struct Square {
    constexpr int operator(){int i} { return i * i; }
};

struct Cube {
    constexpr int operator()(int i) { return i * i * i; }
};

if (My_cond<T>()) {
    // error : declaration as if-statement branch
    using Type = Square;
}
else {
    // error : declaration as if-statement branch
    using Type = Cube;
}

// error : Type is not in scope
Type x;


// error : Square and Cube are types, not an expression
(My_cond<T>() ? Square : Cube){}(99);
// error : not an expression
(My_cond<T>() ? Square{} : Cube{})(99);
// ok : a function is an expression
(My_cond<T>() ? Square{}(99) : Cube{}(99));


// section 28.3.1.3 : selecting among several types
class Nil {};

template<int I, typename T1 = Nil, typename T2 = Nil, typename T3 = Nil, typename T4 = Nil>
struct select;

template<int I, typename T1 = Nil, typename T2 = Nil, typename T3 = Nil, typename T4 = Nil>
using Select = typename select<I, T1, T2, T3, T4>::type;

// specializations for 0-3
// specialization for N == 0
template<typename T1, typename T2, typename T3, typename T4>
struct select<0, T1, T2, T3, T4> { using type = T1; };

template<typename T1, typename T2, typename T3, typename T4>
struct select<1, T1, T2, T3, T4> { using type = T2; };

template<typename T1, typename T2, typename T3, typename T4>
struct select<2, T1, T2, T3, T4> { using type = T3; };

template<typename T1, typename T2, typename T3, typename T4>
struct select<3, T1, T2, T3, T4> { using type = T4; };

template<int N, typename T1, typename T2, typename T3, typename T4>
Select<N, T1, 2, T3, T4> get(Tuple<T1, T2, T3, T4>& t);

// assume that t is a tuple
auto x = get<2>(t);

// general case; never instantiated
template<unsigned N, typename... Cases>
struct select;

//
template<unsigned N, typename T, typename... Cases>
struct select<N, T, Cases...> : select<N-1, Cases...> {
};

// final case : N == 0
template<typename T, typename... Cases>
struct select<0, T, Cases...> {
    using type = T;
};

template<unsigned N, typename... Cases>
using Select = typename select<N, Cases...>::type;


// section 28.3.2 : iteration and recursion
template<int N>
constexpr int fac()
{
    return N * fac<N-1>();
}

template<>
constexpr int fac<1>()
{
    return 1;
}

constexpr int x5 = fac<5>();

constexpr int fac(int i)
{
    return (i<2) ? 1 : i * fac(i-1);
}

constexpr int x6 = fac(6);


// sectionn 28.3.2.1 : recursion using classes
template<int N>
struct Fac {
    static const int value = N * Fac<N-1>::value;
};

template<>
struct Fac<1> {
    static const int value = 1;
};

constexpr int x7 = Fac<7>::value;


// section 28.3.3 : when to use metaprogramming
// ugly macros
#define IF(c, x, y) typename std::conditional<(c), x, y>::type

IF(cond, Cube, Square) z;
typename std::conditional<(cond), Cube, Square>::type z;

