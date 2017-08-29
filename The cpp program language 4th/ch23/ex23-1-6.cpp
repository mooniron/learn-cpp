/**************************************************************
* Name     :  ex23-1-6.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年7月12日
**************************************************************/



/*
example 23.6 : template aliases
*/


template<typename T, typename Allocator = alloc<T>> vector;
// both arguments are bound
using Cvec = vector<char>;
// vc is a vector<char, alloc<char>>
Cvec vc = {'a', 'b', 'c'};

// vector using my allocator (2nd argument is bound)
template<typename T>
using Vec = vector<T, My_alloc<T>>;
// fib is a vector<int, My_alloc<int>>
Vec<int> fib = {0, 1, 1, 2, 3, 5, 8, 13};
// vc2 and vc are of the same type
vector<char, alloc<char>> vc2 = vc;
// verbose and fib are of the same type
vector<int, My_alloc<int>> verbose = fib;


template<int>
struct int_exact_traits {
    // idea int_exact_traits<N>::type is a type with exactly N bits
    using type = int;
};

template<>
struct int_exact_traits<8> {
    using type = char;
};

template<>
struct int_exact_trait<16> {
    using type = short;
};

// define alias for convenient notation
template<int N>
using int_exact = typename int_exact_traits<N>::type;
// int_exact<8> is an int with 8 bits
int_exact<8> a = 7;

