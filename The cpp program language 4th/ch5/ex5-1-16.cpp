/**************************************************************
* Name     :  ex5-1-16.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年4月19日
**************************************************************/



/*
example 5.4 : small utility components
    5.4.3 : pairs and tuples

just a collection of data
*/


#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;


template<typename Forward_iterator, typename T, typename Compare>

pair<Forward_iterator, Forward_iterator> \
equal_range(Forward_iterator first, Forward_iterator last, const T& val, Compare cmp);



// search in a sorted sequence of Records
// compare names
auto rec_eq = [](const Record& r1, const Record& r2) { return r1.name < r2.name; };

// assume that v is sorted an its "name" field
void f(const vector<Record>& v)
{
    auto er = equal_range(v.begin(), v.end(), Record{"Reg"}, rec_eq);
    // print all equal records
    for (auto p = er.first; p != er.second; ++p)
    {
        // assume that << is defined for Record
        cout << *p;
    }
}


// use make_pair()
void f(vector<string& v>)
{
    // pp is a pair<vector<string>::iterator, int>
    auto pp = make_pair(v.begin(), 2);
    // ...
}


// tuple
// the type is explicitly specified
tuple<string, int, double> t2("Sild", 123, 3.14);
// the type is deduced, t is a tuple<string, int, double>
auto t = make_tuple(string("Herring"), 10, 1.23);
// get first element of tuple
string s = get<0>(t);
// get compile-time selection of elements, i must use the ugly get<1>(t)
int x = get<1>(t);
double d = get<2>(t);


