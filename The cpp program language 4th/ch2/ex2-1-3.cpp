/**************************************************************
* Name     :  ex2-1-3.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年4月7日
**************************************************************/

/*
* example 2.2.1:
    print square value
*/

#include <iostream>

using namespace std;    //make names from std visible without explicit std::

double square(double x)     //a double precision floating-point number
{
    return x * x;
}

void print_square(double x)
{
    cout << "the square of " << x << " is " << square(x) << "\n";
}

int main ()
{
    print_square(1.2);  // print : the square of 1.2

    return 0;
}
