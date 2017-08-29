/**************************************************************
* Name     :  ex5-1-7.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年4月19日
**************************************************************/



/*
example 5.3 :concurrency
    5.3.4 : sharing data
*/



#include <iostream>
#include <thread>
#include <vector>

using namespace std;


// controlling mutex
mutex m;
// shared data
int sh;

void f()
{
    // acquire mutex
    unique_lock<mutex> lck {m};
    // manipulate shared data
    sh += 7;
}   // release mutex implicitly


//
class Record {
public :
    mutex rm;
    // ...
};


// acquire several locks simultaneously
void fs()
{
    // ...
    // defer_lock : don't yet try to acquire the mutex
    unique_lock<mutex> lck1 {m1, defer_lock};
    unique_lock<mutex> lck2 {m2, defer_lock};
    unique_lock<mutex> lck3 {m3, defer_lock};

    // acquire all three locks
    lock(lck1, lck2, lck3);
    // ... manipulate shared data ...
}   // implicitly release all mutexes
