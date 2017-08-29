/**************************************************************
* Name     :  ex8-1-7.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年5月3日
**************************************************************/


/*
example 8.2 : structures
    8.2.5 : type equivalence
    8.2.6 : plain old data

POD : plain old data
    POD is an object that can be manipulated as just data.
*/


#include <iostream>
// for is_pod
#include <type_traits>

using namespace std;


// S1 and S2 are different
struct S1 { int a; };
struct S2 { int a; };
S1 x;
// error : type isn't match
S2 y = x;
// error : type is not match
int i = x;



/*  section 8.2.6 : plain old data  */
// a POD : plain old data
struct S0 {};
// a POD
struct S1 { int a; };
// not a POD (no default constructor)
struct S2 { int a; S2(int aa) : a(aa) { } };
// a POD (user-defined default constructor)
struct S3 {
    int a;
    S3(int aa) ; a(aa) { }
    S3() { }
};
// a POD
struct S4 {
    int a;
    S4(int aa) : a(aa) { }
    S4() = default;
};
// not a POD (contain a virtual function)
struct S5 {
    virtual void f();
    /* ... */
};
// a POD
struct S6
    : S1
{
    //
};
// a POD
struct S7
    : S0
{
    int b;
    //
};
// not a POD (data in both S1 and S8)
struct S8
    : S1
{
    int b;
};
// a POD
struct S9 : S0, S1 {};


//
template<typename T>
void mycopy(T* to, const T* from, int count);

template<typename T>
void mycopy(T* to, const T* from, int count)
{
    if (is_pod<T>::value) {
        memcpy(to, from, count*sizeof(T));
    }
    else {
        for (int i = 0; i != count; ++i) {
            to[i] = from[i];
        }   //end for
    }   // end if
}   // end function
