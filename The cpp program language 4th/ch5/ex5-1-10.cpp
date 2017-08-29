/**************************************************************
* Name     :  ex5-1-10.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年4月19日
**************************************************************/



/*
example 5.3 :concurrency
    5.3.5 : communicating tasks
    5.3.5.2 : packaged_tasks
*/



#include <iostream>
#include <thread>
#include <future>
#include <vector>
#include <numeric>


using namespace std;


// compute the sum of [beg, end) starting with the initial value init
double accum(double* beg, double* end, double init)
{
    return accumulate(beg, end, init);
}

//
double comp2(vector<double>& v)
{
    // type of task
    using Task_type = double(double*, double*, double);

    // package the task (i.e., accum)
    packaged_task<Task_type> pt0 {accum};
    packaged_task<Task_type> pt1 {accum};

    // get hold of pt0's future
    future<double> f0 {pt0.get_future()};
    // get hold of pt1's future
    future<double> f1 {pt1.get_future()};

    double* first = &v[0];
    // start a thread for pt0, accumulate the front half elements of v
    thread t1 {move(pt0), first, first + v.size() / 2, 0};
    // start a thread for pt1, accumulate the end half elements of v
    thread t2 {move(pt1), first + v.size() / 2, first + v.size(), 0};

    // ...
    // wait for t1 completed
    t1.join();
    // wait for t2 completed
    t2.join();
    // get the results, total sum results
    return f0.get() + f1.get();
}


// main test block
int main()
{
    //
    vector<double> v {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    double* first = &v[0];
    cout << "the front sum result is " << accum(first, first + v.size() / 2, 0) << endl;
    cout << "the end sum result is " << accum(first + v.size() / 2, first + v.size(), 0) << endl;
    cout << "the total sum result is " << comp2(v) << endl;
    //cout << "the sum result is " << v[2] << endl;

    return 0;
}
