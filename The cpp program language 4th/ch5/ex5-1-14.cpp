/**************************************************************
* Name     :  ex5-1-14.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年4月19日
**************************************************************/



/*
example 5.4 : small utility components
    5.4.2 : type function
    5.4.2.1 : iterator_traits
*/


#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;


void test(vector<string>& v, forward_list<int>& lst)
{
    // sort the vector
    sort(v);
    // sort the singly-linked list
    sort(lst);
}


// for random-access iterators
template<typename Ran>

// we can subscript into [beg : end)
void sort_helper(Ran beg, Ran end, random_access_iterator_tag)
{
    // just sort it
    sort(beg, end);
}


// for forward iterators
template<typename For>

// we can traverse [beg : end)
void sort_helper(For beg, For end, forward_iterator_tag)
{
    // initialize a vector from [beg : end)
    vector<decltype(*beg)> v {beg, end};
    sort(v.begin(), v.end());
    // copy the elements back
    copy(v.begin(), v.end(), beg);
}


// container C
template<typename C>

// sort the container c
void sort(C& c)
{
    using Iter = Iterator_type<C>;
    sort_helper(c.begin(), c.end(), Iterator_category<Iter> {});
}


// C's iterator type
template<typename C>
using Iterator_type = typename C::iterator;

// Iter's category
template<typename Iter>
using Iterator_category = typename std::iterator_traits<Iter>::iterator_category

