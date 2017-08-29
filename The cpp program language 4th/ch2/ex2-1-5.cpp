/**************************************************************
* Name     :  ex2-1-5.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年4月7日
**************************************************************/

/*
* example 2.2.3:
*    constants: const, constexpr;

const: for interfaces
    promise not to change the value;
constexpr: allow data in memory, where it is unlikely to corrupted and for performance.
    to be evaluated at compile time;
*/

#include <iostream>

using namespace std;

int main ()
{
    const int dmv = 13;     // dmv is a int constant
    int var = 13;       // var is not a constant
    constexpr double max1 = 1.4 * square(dmv);      // ok : if square(13) is a constant expression
    constexpr double max2 = 1.4 * square(var);      // error: var is not a constant expression
    const double max3 = 1.4 * square(var);      // ok : may be evaluated at run time
    double sum(const vector<double>);       // sum will not modify its argument
    vector<double> v {1.2, 3.4, 4.5};       // v is not a constant
    const double s1 = sum(v);       // ok : evaluated at run time
    constexpr double s2 = sum(v);       // error : sum(v) not constant expression
    // a constant expression function
    constexpr double square(double x) {return x * x;}

    return 0;
}
