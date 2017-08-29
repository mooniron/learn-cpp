/**************************************************************
* Name     :  ex40-1-6.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年8月22日
**************************************************************/



/*
example 40.6: generalized numerical algorithms
*/


// section 40.6.1: accumulate()
template<typename In, typename T>
T accumulate(In first, In last T init)
{
    for ( ; first != last; ++first) {
        init = init + *first;
    }
    return init;
}

void f(vector<int>& price, list<float>& incr)
{
    int i = accumulate(price.begin(), price.end(), 0);
    double d = 0;
    d = accumulate(incr.begin(), incr.end(), d);
    int prod = accumulate(price.begin, price.end(), 1, [](int a, int b){ return a * b; });
    // ...
}

struct Record {
    // ...
    int unit_price;
    int number_of_units;
};

long price(long val, const Record& r)
{
    return val + r.unit_price * r.number_of_units;
}

void f(const vector<Record>& v)
{
    cout << "Total value: " << accumulate(v.begin(), v.end9), 0, price) << '\n';
}


// section 40.6.2: inner_product()
template<typename In, typename In2, typename T>
T inner_product(In first, In last, In2 first2, T init)
{
    while (first != last) {
        init = init + *first++ * *first2++;
    }
    return init;
}

template<typename In, typename In2, typename T, typename BinOp, typename BinOp2>
T inner_product(In first, In last, In2 first2, T init, BinOp op, BinOp2 op2)
{
    while (first != last) {
        init = op(init, op2(*first++, *first2++));
    }
    return init;
}

valarray<double> operator*(const Matrix& m, valarray<double>& v)
{
    valarray<double> res(m.dim2());
    for (size_t i = 0; i < m.dim2(); i++) {
        auto& ri = m.row(i);
        res[i] = inner_product(ri, ri.end(), &v[0], double(0));
    }
    return res;
}


// section 40.6.3: partial_sum() and adjacent__difference()
vector<double> temps;
void f()
{
    adjacent_difference(temps.begin(), temps.end(), temps.begin());
}

template<typename In, typename Out, typename BinOp>
Out partial_sum(In first, In last, Out res, BinOp op)
{
    if (first == last) {
        return res;
    }
    *res = *first;
    T val = *first;
    while (++first != last) {
        val = op(val, *first);
        *++res = val;
    }
    return ++res;
}

template<typename In, typename Out>
Out partial_sum(In first, In last, Out res)
{
    // use std::plus
    return partial_sum(first, last, res, plus);
}

void f()
{
    partial_sum(temps.begin(), temps.end(), temps.begin());
}


// section 40.6.4:iota()
vector<int> v(5);
iota(v.begin(), v.end(), 50);
vector <int> v2 {50, 51, 52, 53, 54, 55};

if (v != v2) {
    error("complain to your library vendor");
}

