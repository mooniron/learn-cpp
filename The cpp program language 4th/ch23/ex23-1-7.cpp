/**************************************************************
* Name     :  ex23-1-7.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年7月12日
**************************************************************/



/*
example 23.7 : source code organization
*/


// file out.h
#include<iostream>

template<typename T>
void out(const T& t)
{
    std::cerr << t;
}


// file user1.cpp
#include "out.h"
// use out()

// file user2.cpp
#include "out.h"
// use out()


// include template definitions later
// file outdecl.h
template<typename T>
void out(const T& t);

// file out.cpp
#include <iostream>

template<typename T>
void out(const T& t)
{
    std::cerr << t;
}

// file user3.cpp
#include "out.h"
#include "out.cpp"


// error : cause different definitions
// file user1.cpp
#include "out.h"
// use out()

// file user4.cpp
#define std MyLib
#include "out.h"
// use out()


// section 23.7.1 : linkage
double accum(const vector<double>& v)
{
    return accumulate(v.begin(), v.end(), 0.0);
}

double accum(const vector<double>& v);

