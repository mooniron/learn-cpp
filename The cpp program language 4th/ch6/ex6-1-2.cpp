/**************************************************************
* Name     :  ex6-1-2.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年4月25日
**************************************************************/



/*
example 6.1 : the iso c++ standard
*/


#include <iostream>

using namespace std;


int main()
{
    // well-defined: a char has at least of 8 bits and can always hold 64
    unsigned char c1 = 64;
    // implementation-defined : truncation if a char has only 8 bits
    unsigned char c2 = 1088;
    cout << c1 << '\t' << c2 << endl;

    static_assert(4 <= sizeof(int), "sizeof(int) too small");
}   // end function main


const int size = 4 * 1024;
char page[size];

void f()
{
    // undefined
    page[size + size] = 7;
}
