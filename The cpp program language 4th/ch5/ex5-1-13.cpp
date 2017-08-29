/**************************************************************
* Name     :  ex5-1-13.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年4月19日
**************************************************************/



/*
example 5.4 : small utility components
    5.4.2 : type functions

type function : evaluated at compile-time
*/


#include <iostream>
#include <limits>

using std::cin; using std::cout; using std::cerr; using std::endl;
using std::numeric_limits;

int main()
{
    // smallest positive float
    constexpr float min = numeric_limits<float>::min();
    cout << min << '\n';

    // the number of bytes in an int
    constexpr int szi = sizeof(int);
}
