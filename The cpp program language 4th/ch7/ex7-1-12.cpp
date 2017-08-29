/**************************************************************
* Name     :  ex7-1-12.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年4月25日
**************************************************************/


/*
example 7.7 : references
    7.7.2 : rvalue references
*/


#include <iostream>
#include <vector>
#include <string>
#include <utility>

using namespace std;


string var {"cambridge"};
string f();

// lvalue reference, bind r1 to var (a lvalue)
string& r1 {var};
// lvalue reference, error : f() is a rvalue
string& r2 {f()};
// lvalue reference, error : can not bind to temporary
string& r3 {"Princeton"};
// rvalue reference, fine : bind rr1 to a rvalue (a temporary)
string&& rr1 {f()};
// rvalue reference, error : var is a lvalue
string&& rr2 {var};
// fine : rr3 refers to a temporary holding "Oxford"
string&& rr3 {"Oxford"};
// OK : make temporary and bind to cr1
//const string cr1& {"Harvard"};
const string& cr1 {"Harvard"};


string fs(string&& s)
{
    if (s.size()) {
        s[0] = toupper(s[0]);
    }
    return s;
}   // end function fs


//
template<class T>
void swap(T& a, T& b)
{
    // now we have two copies of a
    T tmp {a};
    // now we have two copies of b
    a = b;
    // now we have two copies of tmp { aka a }
    b = tmp;
}   // end function swap


template<class T>
void swap(T& a, T& b)
{
    // the initializer may write to a (modify a)
    T tmp {static_cast<T&&>(a)};
    // the assignment may write to b (modify b)
    a = static_cast<T&&>(b);
    // the assignment may write to tmp (modify tmp)
    b = static_cast<T&&>(tmp);
}   //


template<class T>
class vector {
    // ...
    // copy constructor (copy r)
    vector(const vector& r);
    // move constructor (move r)
    vector(vector&& r);
    //
};


vector<string> s;
// s is a lvalue, use copy constructor
vector<string> s2 {s};
// s + "tail" is a rvalue, so use move constructor
vector<string> s3 {s + "tail"};


template<class T>
void swap(T& a, T& b)
{
    // move from a
    T tmp {move(a)};
    // move from b
    a = move(b);
    // move from tmp
    b = move(tmp);
}


void fv(vector<int>& v)
{
    swap(v, vector<int> {1, 2, 3});
    // ...
}


// two overloads
template<class T> void swap(T&& a, T& b);
template<class T> void swap(T& a, T&& b);


void fsv(string& s, vector<int>& v)
{
    // make s.capacity() == s.size()
    s.shrink_to_fit();
    // make s.caparity() == s.size()
    swap(s, string {s});
    // make v empty
    v.clear();
    // make v empty
    swap(s, vector<int> {});
}
