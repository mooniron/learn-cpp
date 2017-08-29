// Vector.cpp


// get the interface
#include <Vector.h>

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
