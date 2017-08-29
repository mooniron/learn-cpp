/**************************************************************
* Name     :  ex3-1-11.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年4月7日
**************************************************************/


/*
example 3.4 : Templates
    3.4.2 : function template
*/


template<typename Container, typename Value>

Value sum(const Container& c, Value v)
{
    for (auto x : c)
    {
        v += x;
    }
    return v;
}


//
void user(Vector<int>& v, std::list<double>& ld, std::vector<complex<double>>& vc)
{
    // the sum of a Vector of ints (add ints)
    int x = sum(v, 0);
    // the sum of a Vector of ints (add doubles)
    double d = sum(v, 0.0);
    // the sum of a list of doubles
    double dd = sum(ld, 0.0);
    // the sum of a vector of complex<double>, the initial value is {0.0, 0.0}
    auto z = sum(vc, complex<double> {});
}
