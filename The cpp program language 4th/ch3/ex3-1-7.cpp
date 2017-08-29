/**************************************************************
* Name     :  ex3-1-7.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年4月7日
**************************************************************/


/*
example 3.3 : copy and move
    3.3.1 : copying containers
*/


void test(complex z1) {
    // copy initialization
    complex z2 {z1};
    complex z3;
    // copy assignment
    z3 = z2;
    // ...
    }   // end function test

/*  bad_copy : memberwise copy  */
void bad_copy(Vector v) {
    // copy v1's respresentation into v2, v2.elem pointer == v1.elem pointer, v2.sz == v1.sz
    Vector v2 = v1;
    // v2[0] is now also 2!
    v1[0] = 2;
    // v1[1] is now also 3!
    v2[1] = 3;
    }   // end function bad_copy


/*  */
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
    //
    double& operator[](int i);
    const double& operator[](int i) const;
    //
    int size() const;
    };


// copy Vector constructor
Vector::Vector(const Vector& a)
    // allocates spaces for elements
    : elem { new double[sz] },
    sz { a.sz }
{
    // copy elements
    for (int i = 0; i != sz; ++i)
    {
        elem[i] = a.elem[i];
    }   // end for
}   // end copy constructor


// copy assignment
Vector& Vector::operator=(const Vector& a)
{
    double* p = new double[a.sz];
    for (int i = 0; i != a.sz; ++i)
    {
        p[i] = a.elem[i];
    }
    // delete old elements
    delete[] elem;
    elem = p;
    sz = a.sz;
    // "this" is predefined in a member function, and points to the object for caller
    return *this;
}

