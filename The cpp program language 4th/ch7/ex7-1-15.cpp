/**************************************************************
* Name     :  ex7-1-15.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年5月2日
**************************************************************/


/*
example 7.7 : references
    7.7.4 : pointers and references
*/


#include <iostream>
#include <vector>
#include <string>
//#include <matrix>

using namespace std;


void fp(char* p)
{
    while(*p) {
        // cout << ++ *p;
        cout << *p++;
    }
}


void fr(char& r)
{
    while (r) {
        // loops : increment the char refered to, rather than the reference, nearlyinfinite loop
        cout ++r;
    }
}



void fr2(char& r)
{
    // get a pointer to the object refered to
    char* p = &r;
    while (*p) {
        cout << *p++;
    }
}   // end function


template<class T> class Proxy {
    T& m;
public :
    Proxy(T& mm) : m {mm} { }
    // ...
};  // end class


template<class T> class Handle {
    // handle refers to its current object
    T* m;
public :
    Proxy(T* mm) : m {mm} { }
    void rebind(T* mm) { m = mm; }
    // ...
};  // end class




// OK
Matrix operator+(const Matrix&, const Matrix&);
// error : no user-defined type argument, not allow to redefine operator for built-in types
Matrix operator-(const Matrix*, const Matrix*);     // pointer type arguments, built-in
Matrix y, z;
// ...
// OK
Matrix x = y + z;
// error and ugly
Matrix x2 = &y - &z;


// a collection of something refers to an object
int x, y;
// error : array of references
string& a1[] = {x, y};
// OK
string* a2[] = {&x, &y};
// error : vector of references
vector<string&> s1 = {x, y};
// OK
vector<string*> s2 = {&x, &y};



int main()
{
    char s[] {"hello"};
    fp(s);

    return 0;
}



void fp(X* p)
{
    if (p == nullptr) {
        // no value
    }
    else {
        // use *p
    }   // end if
}   // end function


// common style
void fr(X& r)
{
    // assume that r is valid and use it
}   // end function


// define a "null reference" for a particular type
void fr2(X& r)
{
    if (&r == &nullX) {
        // or maybe r == nullX
        // no value
    }
    else {
        // use r
    }
}


// an invalid reference
char* ident(char* p) { return p; }

char& r {*ident(nullptr)}; // invalid code
