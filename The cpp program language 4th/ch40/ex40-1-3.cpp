/**************************************************************
* Name     :  ex40-1-3.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年8月22日
**************************************************************/



/*
example 40.3: standard mathematical functions
*/


void f()
{
    // clear old error state
    errno = 0;
    sqrt(-1);
    if (errno == EDOM) {
        cerr << "sqrt() not defined for negative argument";
    }
    pow(numeric_limits<double>::max(), 2);
    if (errno == ERANGE) {
        cerr << "result of pow() too large to reperesent as a double";
    }
}

