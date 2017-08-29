/**************************************************************
* Name     :  ex26-1-2.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年7月17日
**************************************************************/



/*
example 26.1 : introduction
example 26.2 : template instantiation
*/


// section 26.2.1 : when is instantiation needed

class X;
// OK : no definition of X needed
X* p;
// error : definition of X needed
X a;

template<typename T>
class Link {
    // ok : no definition of Link needed yet
    Link* suc;
    // ...
};

// no instantiation of Link<int> needed yet
Link<int>* p1;
// now we need to instantiate Link<int>
Link<int> lnk;

template<typename T>
class List {
    // ...
    void sort();
};

class Glob {
    // ... no comparison operators ...
};

void f(List<Glob>& lb, List<string>& ls)
{
    // ... use operations on lb, but not lb.sort()
    ls.sort();
}


// section 26.2.2 : manual control of instantiation
// class
template class vector<int>;
// member function
template int& vector<int>::operator[](int);
// nonmember function
template int convert<int, double>(double);
// ok redundant
template int convert<int, double>(double);
// ok
template int convert<int>(double);

#include "MyVector.h"
// suppresses implicit instantiation
// explicitly instantiate elsewhere
extern template class MyVector,int>;

void foo(MyVector,int>& v)
{
    // ... use the vector in here ...
}

#include "MyVector.h"

// instantiate in this translation unit, use this point of instantiation
template class MyVector,int>;

