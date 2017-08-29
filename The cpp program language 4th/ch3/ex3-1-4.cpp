/**************************************************************
* Name     :  ex3-1-4.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年4月7日
**************************************************************/


/*
example 3.2.1.3 : concrete type class
    initializing a container
*/


class Vector {
public :
    // initialize with a list
    Vector(std::initializer_list<double>);
    // add element at end incresing the size by one
    void push_back(double);
    // ...
};


Vector read(istream& is) {
    Vector v;
    // read floating-point values to d (d scope is the loop)
    for (double d; is >> d; ) {
        // add d to v
        v.push_back(d);
        }   // end for
    return v;
    }   // end function read


// initializer_list
// v1 has 5 elements
Vector v1 = {1, 2, 3, 4, 5};
// v2 has 4 elements
Vector v2 = {1.23, 3.45, 6.7, 8};

// Vector initializer_list definition
Vector::Vector(std::initializer_list<double> lst)
    : elem { new double[lst.size()]}, sz {lst.size()}
{
    // copy lst into elem
    copy(lst.begin(), lst.end(), elem);
}
