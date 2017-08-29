/**************************************************************
* Name     :  ex6-1-8.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年4月25日
**************************************************************/



/*
example 6.2 : types
    6.2.8 : sizes
*/


#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


int main()
{
    // the allignment of a char
    auto ac = alignof(char);
    // the alignment of an int
    auto ai = alignof(int);
    // the alignment of an double
    auto ad = alignof(double);
    // the alignment of an int pointer
    auto aa = alignof(int*);
    cout << ac << '\t' << ai << '\t' << ad << '\t' << aa << '\n';
}



template<typename X>
// alignas
void user(const vector<X>& vx)
{
    constexpr int bufmax = 1024;
    // uninitialized
    alignas(X) X buffer[bufmax];
    const int max = min(vx.size(), bufmax / sizeof(X));
    uninitialized_copy(vx.begin(), vx.begin() + max, buffer);
    // ...
}
