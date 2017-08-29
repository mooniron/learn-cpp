/**************************************************************
* Name     :  ex4-1-10.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年4月19日
**************************************************************/


/*
example 4.5 : algorithms

a sequence is represented by a pair of iterators specifying the first element and the
one-byond-the-last element.
*/


// sort a vector and copy each unique vector element on a list

struct Entry {
    string name;
    int number;
};


// less than
bool operator<(const Entry& x, const Entry& y)
{
    // order Entrys by their names
    return x.name < y.name;
}


void f(vector<Entry>& vec, list<Entry>& lst)
{
    // use < for order
    sort(vec.begin(), vec.end());
    // don't copy adjacent equal elements, lst would be overwritten
    unique_copy(vec.begin(), vec.end(), lst.begin());
}


// place the unique elements in a new container
list<Entry> place_unique_to_list(vector<Entry>& vec)
{
    //
    list<Entry> res;
    sort(vec.begin(), vec.end());
    // append to res
    unique_copy(vec.begin(), vec.end(), back_inserter(res));
    // a move constructor
    return res;
}
