/**************************************************************
* Name     :  ex18-1-2.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年6月10日
**************************************************************/



/*
example 18.1 : introduction
*/


// very simple complex
class complex {
    double re, im;
public :
    complex(double r, double i) : re {r}, im {i} { }
    complex operator+(complex);
    complex operator*(complex);
};

void f()
{
    complex a = complex {1, 3.1};
    complex b {1.2, 2};
    complex c {b};
    a = b + c;
    b = b + c * a;
    c = a * b + complex(1, 2);
}

void g(complex a, complex b)
{
    // ok : right hand side of assignment
    a = {1, 2};
    // ok : right hand side of assignment
    a += {1, 2};
    // syntax error
    b = a + {1, 2};
    // ok
    b = a + complex{1, 2};
    // ok : a function argument is considered an initializer
    g(a, {1, 2});
    // syntax error
    {a, b} = {b, a};
}
