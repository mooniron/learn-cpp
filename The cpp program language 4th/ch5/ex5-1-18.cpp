/**************************************************************
* Name     :  ex5-1-18.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年4月19日
**************************************************************/



/*
example 5.6 : math
    5.6.1 mathematical functions and algorithms
*/


#include <iostream>
#include <cmath>
#include <numeric>
#include <complex>
#include <list>

using namespace std;


void f()
{
    list<double> lst {1, 2, 3, 4, 5, 9999.99999};
    // calculate the sum
    auto s = accumulate(lst.begin(), lst.end(), 0.0);
    // print 10014.99999
    cout << s << '\n';
}


int main()
{
    f();

    return 0;
}
