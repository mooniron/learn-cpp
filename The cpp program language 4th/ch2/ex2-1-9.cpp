/**************************************************************
* Name     :  ex2-1-9.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年4月7日
**************************************************************/


/*
example 2.3.2 :
    class
*/


#include <iostream>

using namespace std;

class Vector {
public :
    // construct a vector (replace function Vector_init)
    Vector(int s) : elem {new double[s]}, sz {s} {}
    // element access : subscripting
    double& operator[](int i) {return elem[i];}
    int size() {return sz;}
private :
    // pointer to the elements
    double* elem;
    // the number of elements
    int sz;
};  // end class Vector

// a Vector of 6 elements
Vector v(6);

double read_and_sum(int s) {
    // make Vector of s elements
    Vector v(s);
    for (int i = 0; i != v.size(); ++i) {
        cin >> v[i];
        }   // end for

    double sum = 0.0;
    for (int i = 0; i != v.size(); ++i) {
        // take the sum of elements
        sum += v[i];
        }   // end for

    return sum;
    }   // end function read_and_sum


int main() {
    double sum {0};

    sum = read_and_sum(6);
    cout << "sum is " << sum << endl;
    return 0;
    }   // end function main
