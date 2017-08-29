/**************************************************************
* Name     :  ex7-1-10.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年4月25日
**************************************************************/



/*
example 7.7 : references
*/


#include <iostream>
#include <vector>

using namespace std;


/*
template<class T>

class vector {
    T* elem;
    int sz;
    // ...
public :
    // return reference to element
    T& operator[](int i) { return elem[i]; }
    // return reference to const element
    const T& operator[](int i) const { return elem[i]; }
    // pass element to be added by reference
    void push_back(const T& a);
};
*/

//void f(const vector<double>& v)
void f(vector<double>& v)
{
    // copy the value of the double referred to by v.operator[](1) into d1
    double d1 = v[1];
    // place 7 in the double referred to by the result of v.operator[](2)
    v[2] = 7;
    // give push_back() a reference to d1 to work with
    v.push_back(d1);
}


int main()
{
    vector<double> vd {1, 2, 3};
    f(vd);

    return 0;
}
