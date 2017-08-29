/**************************************************************
* Name     :  ex5-1-15.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年4月19日
**************************************************************/



/*
example 5.4 : small utility components
    5.4.2 : type function
    5.4.2.2 : type predicates
*/


#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <type_traits>

using namespace std;


// yes, int is an arithmetic type
bool b1 = Is_arithmetic<int>();
// no, std::string is not an arithmetic type
bool b2 = Is_arithmetic<string>();


//
template<typename Scalar>

class complex {
    Scalar re, im;
public :
    static_assert(Is_arithmetic<Scalar>(), "Sorry, I only support complex of arithmetic types");
    // ...
};


// improve readability
template<typename T>

constexpr bool Is_arithmetic() { return std::is_arithmetic<T>::value; }
