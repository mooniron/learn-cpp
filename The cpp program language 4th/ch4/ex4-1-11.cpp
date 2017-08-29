/**************************************************************
* Name     :  ex4-1-11.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年4月19日
**************************************************************/


/*
example 4.5 : algorithms
    4.5.1 : use iterators
*/


#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;


// does s contain the character c?
bool has_c(const string& s, char c)
{
    auto p = find(s.begin(), s.end(), c);
    if (p != s.end())
    {
        return true;
    }
    else
    {
        // not found
        return false;
    }
}   // end function has_c

// equivalent : more shorter version
bool has_c_short(const string& s, char c)
{
    return find(s.begin(), s.end(), c) != s.end();
}


// find all occurrences of c in s
vector<string::iterator> find_all(string& s, char c)
{
    //
    vector<string::iterator> res;
    for (auto p = s.begin(); p != s.end(); ++p)
    {
        if (*p == c)
        {
            res.push_back(p);
        }   // end if
    }   // end for
    // move
    return res;
}


// test find_all
int test_find_all(char c)
{
    int count = 0;
    string m {"Mary had a little lamb"};
    for (auto p : find_all(m, c))
    {
        if (*p != c)
        {
            cerr << "a bug!" << endl;
        }   // end if
        else
        {
            count++;
        }
    }   // end for
    // the number of occurrences
    return count;
}   // end function test_find_all


// generaic find_all
// C for containers, V for the elements of the container C
template<typename C, typename V>

// find all occurrences of v in c
vector<typename C::iterator> find_all_g(C& c, V v)
{
    // typename to inform the compiler C::iterator is a type, not a value of some type.
    vector<typename C::iterator> res;
    for (auto p = c.begin(); p != c.end(); ++p)
    {
        if (*p == v)
        {
            res.push_back(p);
        }   // end if
    }   // end for
    // move
    return res;
}   // end function find_all_g



// type alias of typename C::iterator
template<typename T>
//using Iterator<T> = typename T::iterator;
using Iterator = typename T::iterator;

template<typename C, typename V>

// find all occurrences of v in c
vector<Iterator<C>> find_all_h(C& c, V v)
{
    vector<Iterator<C>> res;
    for (auto p = c.begin(); p != c.end(); ++p)
    {
        if (*p == v)
        {
            res.push_back(p);
        }   // end if
    }   // end for
    return res;
}   // end function find_all_h


// test all
void test_all()
{
    string m {"Mary had a little lamb"};
    // p is a string::iterator
    for (auto p : find_all_h(m, 'a'))
    {
        if (*p != 'a')
        {
            cerr << "string bug!\n";
        }   // end for
    }   // end for

    // list<double>
    list<double> ld {1.1, 2.2, 3.3, 1.1};
    // p is a list<double>::iterator
    for (auto p : find_all_h(ld, 1.1))
    {
        if (*p != 1.1)
        {
            cerr << "list bug!\n";
        }   // end if
    }   // end for

    // vector<string>
    vector<string> vs {"red", "blue", "green", "green", "orange", "green"};
    for (auto p : find_all_h(vs, "green"))
    {
        if (*p != "green")
        {
            cerr << "vector bug!\n";
        }   // end if
    }   // end for
    for (auto p : find_all_h(vs, "green"))
    {
        *p = "vert";
    }   // end for
    // print the vs
    for (auto p : vs)
    {
        cout << p << '\n';
    }   // end for
}   // end test_all



// main test function
int main()
{
    int n = 0;
    char c {'j'};
    n = test_find_all(c);

    cout << "the occurrences of " << c << " is " << n << endl;

    test_all();
    return 0;
}   // end function main
