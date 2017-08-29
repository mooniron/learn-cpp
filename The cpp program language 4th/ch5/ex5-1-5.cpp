/**************************************************************
* Name     :  ex5-1-5.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年4月19日
**************************************************************/



/*
example 5.3 :concurrency
    5.3.2 : passing arguments
*/



#include <iostream>
#include <thread>
#include <vector>

using namespace std;


// function do somethind with v
void f(vector<double>& v);

// function object do something with v
struct F {
    vector<double>& v;
    // constructor
    F(vector<double>& vv) : v {vv} { }
    // application operator;
    void operator() {};
};


// main function
int main()
{
    vector<double> some_vec {1, 2, 3, 4, 5, 6, 7, 8, 9};
    vector<double> vec2 {10, 11, 12, 13, 14};

    // f(some_vec) executes in a separate thread
    thread t1 {f, some_vec};
    // F(ver2)() executes in a separate thread
    thread t2 {F{vec2}};

    t1.join();
    t2.join();
}

