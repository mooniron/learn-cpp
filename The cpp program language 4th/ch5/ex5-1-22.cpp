/**************************************************************
* Name     :  ex5-1-22.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年4月19日
**************************************************************/



/*
example 5.6 : math
    5.6.5 : numeric limits
*/


#include <iostream>
#include <limits>

using namespace std;


static_assert(numeric_limits<char>::is_signed, "unsigned characters!");
static_assert(100000 < numeric_limits<int>::max(), "small ints!");
