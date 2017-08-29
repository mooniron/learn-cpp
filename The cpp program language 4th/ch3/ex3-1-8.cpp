/**************************************************************
* Name     :  ex3-1-8.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年4月7日
**************************************************************/


/*
example 3.3 : copy and move
    3.3.2 : moving containers

&& :
    && means "rvalue reference" and is a reference which we can bind an rvalue.
    lvalue is which appear on the left-hand side of an assignment.
    rvalue is which you can't assign to.
    a rvalue reference is a reference to something that nobody else can assign to.

*/


/*  class Vector  */
class Vector {
private :
    // elem points to an array of sz doubles
    double* elem;
    int sz;
public :
    // constructor : establish invariants, acquire resources
    Vector(int s);
    // destructor : release resources
    ~Vector() { delete[] elem; }
    // copy constructor
    Vector(const Vector& a);
    // copy assignment
    Vector& operator=(const Vector& a);

    // move constructor
    Vector(Vector&& a);
    // move assignment
    Vector& operator=(Vector&& a);

    //
    double& operator[](int i);
    const double& operator[](int i) const;
    //
    int size() const;
    };





/*  3.3.2 moving containers  */

Vector operator+(const Vector& a, const Vector& b)
{
    if (a.size() != b.size())
    {
        throw Vector_size_mismatch {};
    }

    Vector res(a.size());
    for (int i = 0; i != a.size(); ++i)
    {
        res[i] = a[i] + b[i];
    }
    // return involves the copying of res, and into some place where the caller can access
    return res;
}


/*  use operator +  */
void f(const Vector& x, const Vector& y, const Vector& z)
{
    Vector r;
    // ...
    // copy twice, each + copy once
    r = x + y + z;
    // ...
}


/*  move constructor definition  */
Vector::Vector(Vector&& a)
    // "grab the elements" from a
    : elem { a.elem },
    sz { a.sz }
{
    // now a has no elements
    a.elem = nullptr;
    //
    a.sz = 0;
}


/*  */
Vector f()
{
    Vector x(1000);
    Vector y(1000);
    Vector z(1000);
    // ...
    // we get a copy
    z = x;
    // we get a move
    y = std::move(x);
    // ...
    // we get a move
    return z;
}
