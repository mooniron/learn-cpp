/**************************************************************
* Name     :  ex5-1-12.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年4月19日
**************************************************************/



/*
example 5.4 : small utility components
    5.4.1 : time
*/


#include <iostream>
#include <chrono>

using namespace std::chrono;
using std::cin; using std::cout; using std::cerr; using std::endl;


int main()
{
    auto t0 = high_resolution_clock::now();
    //do_work();
    auto t1 = high_resolution_clock::now();
    cout << duration_cast<milliseconds>(t1 - t0).count() << "msec\n";
}
