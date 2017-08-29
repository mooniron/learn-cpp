/**************************************************************
* Name     :  ex5-1-9.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年4月19日
**************************************************************/



/*
example 5.3 :concurrency
    5.3.5 : communicating tasks
    5.3.5.1 : future and promise
*/



#include <iostream>
#include <thread>
#include <future>


using namespace std;


// a task place the result in px
void f(promise<X>& px)
{
    // ...
    try {
        X res;
        // ... compute a value for res ...
        px.set_value(res);
    }
    // oops : couldn't compute res
    // pass the exception to the future's thread
    catch (...) {
        px.set_exception(current-exception());
    }
}


// a task : get the result from future fx
void g(future<X>& fx)
{
    // ...
    try {
        // if necessory wait for the value to get computed
        X v = fx.get();
        // ... use v ...
    }   // end try
    // oops : someone couldn't conpute v
    catch (...) {
        // .. handle error ...
    }
}
