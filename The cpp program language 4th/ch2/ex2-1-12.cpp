/**************************************************************
* Name     :  ex2-1-12.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年4月7日
**************************************************************/


/*
example 2.4.1 :
    separate compilation
*/


#include <iostream>
// get standard-library math function including sqrt
#include <cmath.h>
// get Vector interface
#include "Vector.h"

// make std members visible
using namespace std;


double sqrt_sum(Vector& v) {
    double sum = 0;

    for (int i = 0; i != v.size(); ++i) {
        // sum square roots
        sum += sqrt(v[i]);
        }   // end for

    return sum;
    }   // end function sqrt_sum


