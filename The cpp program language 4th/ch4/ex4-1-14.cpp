/**************************************************************
* Name     :  ex4-1-14.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年4月19日
**************************************************************/


/*
example 4.5 : algorithms
    4.5.6 : container algorithms

a sequence is defined by a pair of iterators [begin, end)
*/


// sort(v.begin(), v.end()) --> sort(v)

namespace Estd {
    using namespace std;
    template<class C>
    void sort(C& c)
    {
        sort(c.begin(), c.end());
    }

    template<class C, class Pred>
    void sort(C& c, Pred p)
    {
        sort(c.begin(), c.end(), p);
    }

    // ...
}
