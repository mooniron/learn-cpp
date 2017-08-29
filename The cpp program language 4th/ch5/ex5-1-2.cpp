/**************************************************************
* Name     :  ex5-1-2.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年4月19日
**************************************************************/



/*
example 5.2 : resource management
*/


#include <iostream>

using namespace std;

/*  lock class  */

// used to protect access to shared data
mutex m;
// ...

void f()
{
    // acquire the mutex m
    unique_lock<mutex> lck {m};
    // manipulate shared data
    // ...
}
