/**************************************************************
* Name     :  ex5-1-11.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年4月19日
**************************************************************/



/*
example 5.3 :concurrency
    5.3.5 : communicating tasks
    5.3.5.3 : async()
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


// spawn many tasks if v is large enough
double comp4(vector<double>& v)
{
    if (v.size() < 10000)
    {
        return accum(v.begin(), v.end(), 0.0);
    }

    auto v0 = &v[0];
    auto sz = v.size();

    // first quarter
    auto f0 = async(accum, v0, v0 + sz / 4, 0.0);
    // second quarter
    auto f1 = async(accum, v0 + sz / 4, v0 + sz / 2, 0.0);
    // third quarter
    auto f2 = async(accum, v0 + sz / 2, v0 + sz * 3 / 4, 0.0);
    // fourth quarter
    auto f3 = async(accum, v0 + sz * 3 / 4, v0 + sz, 0.0);

    // collect and combine the results
    return f0.get() + f1.get() + f2.get() +f3.get();
}


