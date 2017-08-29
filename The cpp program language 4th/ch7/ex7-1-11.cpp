/**************************************************************
* Name     :  ex7-1-11.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年4月25日
**************************************************************/


/*
example 7.7 : references
    7.7.1 : lvalue references
*/


#include <iostream>
#include <vector>
#include <string>
#include <utility>

using namespace std;


void f()
{
    int var = 1;    // var and r now refer to same int object
    int& r {var};
    // x becomes 1, copy value to x
    int x = r;
    // var becomes 2
    r = 2;
}

//int& r1;      // error : a reference must be initialized
int var = 1;
// OK : r1 is initialized
int& r1 {var};
// error : initializer missing
//int& r2;
// OK : r3 initialized elsewhere
extern int& r3;


void g()
{
    int var = 0;
    int& rr {var};
    // var is incremented to 1
    ++rr;
    // pp points to var
    int* pp = &rr;
}


/*
// error : lvalue needed
double& dr = 1;
// OK
const double& cdr {1};
// first create a temporary with the right value
double temp = double{1};
// then use the temporary as the initializer for cdr
const double& cdr {temp};
*/


void increment(int& aa)
{
    ++aa;
}


int next(int p)
{
    return p + 1;
}





// map example
template<class K, class V>
// a simple map class
class Map {
public :
    // return the value corresponding to the key k
    V& operator[](const K& k);
    pair<K, V>* begin() { return &elem[0]; }
    pair<K, V>* end() { return &elem[0] + elem.size(); }
private :
    // {key, value} pairs
    vector<pair<K, V>> elem;
};


template<class K, class V>
V& Map<K, V>::operator[](const K& k)
{
    for (auto& x : elem) {
        if (k == x.first) {
            return x.second;
        }
    }

    // not found, add pair at end
    elem.push_back({k, V{}});
    // return the (default) value of the new element
    return elem.back().second;
}


//template<class K, class V>
//class Map;

int main()
{
    int x = 1;
    // x = 2
    increment(x);
    // x = 3
    x = next(x);
    cout << "x = " << x << '\n';

    Map<string, int> buf;

    for (string s; cin >> s; ) {
        ++buf[s];
    }

    for (const auto& x : buf) {
        cout << x.first << ": " << x.second << '\n';
    }

    return 0;
}
