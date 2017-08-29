/**************************************************************
* Name     :  ex5-1-6.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年4月19日
**************************************************************/



/*
example 5.3 :concurrency
    5.3.3 : returning results
*/



#include <iostream>
#include <thread>
#include <vector>

using namespace std;


// take input from v; place result in *res
void f(const vector<double>& v, double* res);

class F {
public :
    // constructor
    F(const vector<double>& vv, double* p) : v {vv}, res {p} { }
    // place result in *res
    void operator()();
private :
    // source of input
    const vector<double>& v;
    // target for output
    double* res;
};


// main function
int main()
{
    vector<double> some_vec;
    vector<double> vec2;
    // ...
    double res1;
    double res2;

    // f(some_vec, &res1) executes in a separate thread
    thread t1 {f, some_vec, &res1};
    // F{vec2, &res2}() executes in a separate thread
    thread t2 {F{vec2, &res2}};

    t1.join();
    t2.join();

    cout << res1 << ' ' << res2 << '\n';
    thread t2 {};
}
