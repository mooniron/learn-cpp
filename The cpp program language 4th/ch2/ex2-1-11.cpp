/**************************************************************
* Name     :  ex2-1-11.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年4月7日
**************************************************************/


/*
example 2.4.0 :
    modularity
*/


#include <iostream>

using namespace std;


// the sqrt function declaration : takes a double and return a double
double sqrt(double);

// Vector class declaration
class Vector {
public :
    Vector(int s);
    double& operator[](int i);
    int size();
private :
    // elem : point to an array of sz doubles
    double* elem;
    int sz;
};


// sqrt definition
double sqrt(double d) {
    // ... algorithms as found in math textbooks
    }   // end function sqrt


// definition of the constructor
Vector::Vector(int s)
    : elem {new double[s]}, sz {s}
{
}

// definition of Vector subscripting operator
double& Vector::operator[](int i) {
    return elem[i];
    }   // end function operator[]

// definition of size
int Vector::size() {
    return sz;
    }   // end function size
