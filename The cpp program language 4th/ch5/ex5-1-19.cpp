/**************************************************************
* Name     :  ex5-1-19.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年4月19日
**************************************************************/



/*
example 5.6 : math
    5.6.2 : complex numbers
*/


#include <iostream>
#include <cmath>
#include <numeric>
#include <complex>
#include <list>

using namespace std;

/*
template<typename Scalar>
class complex {
public :
    complex(const Scalar& re = {}, const Scalar& im = {});
    // ...
};
*/


// use complex numbers
void f(complex<float> fl, complex<double> db)
{
    complex<long double> ld {fl + sqrt(db)};
    db += fl * 3;
    fl = pow(1 / fl, 2);
    // ...
}
