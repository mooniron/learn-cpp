/**************************************************************
* Name     :  ex5-1-21.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年4月19日
**************************************************************/



/*
example 5.6 : math
    5.6.4 ： vector arithmetic
*/


#include <iostream>
#include <vector>
// optimization for vector numerical computation
#include <valarray>

using namespace std;

/*
template<typename T>
class valarray {
    // ...
};
*/


// use valarray
void f(valarray<double>& a1, valarray<double>& a2)
{
    // numeric array operators *, +, /, and =
    valarray<double> a = a1 * 3.14 + a2 / a1;
    a2 += a1 * 3.14;
    a = abs(a);
    double d = a2[7];
    // ...
}
