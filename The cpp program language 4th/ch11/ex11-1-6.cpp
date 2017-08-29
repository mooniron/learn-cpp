/**************************************************************
* Name     :  ex11-1-6.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年5月14日
**************************************************************/



/*
example 11.5 : explicit type conversion
*/


#include <iostream>

using namespace std;


template<class Target, class Source>
Target narrow_cast(Source v)
{
    // convert the value to Target type
    auto r = static_cast<Target>(v);
    if (static_cast<Source>(r) != v) {
        throw runtime_error("narrow_cast<>() failed");
    }
    return r;
}


void test(double d, int i, char* p)
{
    auto c1 = narrow_cast<char>(64);
    // will throw if chars are unsigned
    auto c2 = narrow_cast<char>(-64);
    // will throw if chars are 8-bit and signed
    auto c3 = narrow_cast<char>(264);
    // ok
    auto d1 = narrow_cast<double>(1/3.0F);
    // will probably throw
    auto f1 = narrow_cast<float>(1/3.0);
    // may throw
    auto c4 = narrow_cast<char>(i);
    // may throw
    auto f2 = narrow_cast<float>(d);
    // compile-time error
    auto p1 = narrow_cast<char*>(i);
    // compile-time error
    auto i1 = narrow_cast<int>(p);
    // may throw (but probably will not)
    auto d2 = narrow_cast<double>(i);
    // may throw
    auto i2 = narrow_cast<int>(d);
}


int main()
{
    char c {'m'};
    char* p = &c;
    test(123.0, 12, p);

    return 0;
}
