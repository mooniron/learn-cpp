/**************************************************************
* Name     :  ex3-1-12.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年4月7日
**************************************************************/


/*
example 3.4 : Templates
    3.4.3 : function objects
    The ability of carry data plus their efficiency make function objects particularly useful as
arguments to algorithms.
*/

#include <iostream>

using namespace std;

/*  */
template<typename T>

class Less_than {
    // value to compare against
    const T val;
public :
    Less_than(const T& v) : val(v) {}
    // call operator
    bool operator()(const T& x) const { return x < val; }
}


// lti(i) will compare i to 42 using <(i < 42)
Less_than<int> lti {42};
// lts(s) will compare s to "backus" using <(s < "backus")
Less_than<string> lts {"backus"};

//
void fct(int n, const string& s)
{
    // true if n < 42
    bool b1 = lti(n);
    // true if s < "backus"
    bool b2 = lts(s);
    // ...
}


/*  count the occurrences of values for which a predicate returns true  */
template<typename C, typename P>

int count(const C& c, P pred)
{
    int cnt = 0;
    for (const auto& x : c)
    {
        if (pred(x))
        {
            ++cnt;
        }
    }   // end for

    return cnt;
}   // end function count


//
void f(const Vector<int>& vec, const list<string>& lst, int x, const string& s)
{
    cout << "number of values less than " << x \
         << " : " << count(vec, Less_than<int>{x}) << '\n';
    cout << "number of values less than " << s \
         << " : " << count(lst, Less_than<string>{s}) << '\n';
}


/*
[&] is a capture list specifying the local variable used will passed by reference.
lambda expression for implicitly generating function objects.
*/
void fim(const Vector<int>& vec, const list<string>& lst, int x, const string& s)
{
    cout << "number of values less than " << x \
         << " : " << count(vec, [&](int a) { return a < x; }) << '\n';
    cout << "number of values less than " << s \
         << " : " << count(lst, [&](const string& a) { return a < s; }) << '\n';
}


/*  */
template<class C, class Oper>

// assume c is a container of pointers
void for_all(C& c, Oper op)
{
    for (auto& x : c)
    {
        // pass op() a reference to each element pointed to
        op(*x);
    }   // end for
}   // end function for_all()


/*  read shapes, draw all, rotate all */
void user()
{
    vector<unique_ptr<Shape>> v;
    //
    while (cin)
    {
        v.push_back(read_shape(cin));
    }
    // draw_all
    for_all(v, [](Shape& s) { s.draw(); });
    // rotate_all(45)
    for_all(v, [](Shape& s { s.rotate(45); }));
}
