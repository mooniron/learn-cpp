/**************************************************************
* Name     :  ex32-1-3.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年8月2日
**************************************************************/



/*
example policy arguments
*/



template<class Iter>
void sort(Iter first, Iter last)
{
    // ... sort using e1 < e2 ...
}

template<class Iter, class Pred>
void sort(Iter first, Iter last, Pred)
{
    // ... sort using pred(e1, e2) ...
}

// use a default template argument
template<typename Ran, typename Pred = less<Value_type<Ran>>>
void sort(Ran first, Ran last, Pred pred = {})
{
    // ... use pred(x, y) ...
}

bool pred(int);
// find element pred or apply predicate pred()? (the latter)
auto p = find(b, e, pred);

using Predicate = bool(*)(int);

void f(vector<Predicate>& v1, vector<int>& v2)
{
    // element with the value pred
    auto p1 = find(v1.begin(), v1.end(), pred);
    // count elements for which pred() returns true
    auto p2 = find_if(v2.begin(), v2.end(), pred);
}

// don't do this
// count the number of even values in v
int n_even(vector<int>& v)
{
    return find_if(v.begin(), v.end(), [](int& x) { ++x; return x & 1; });
}


// section 32.3.1: complexity
