/**************************************************************
* Name     :  ex10-1-3.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年5月6日
**************************************************************/



/*
example 10.3 : operators
    10.3.1 : results
    10.3.2 : evaluate order
    10.3.3 : operator precedence
    10.3.4 : temporary object
*/


#include <iostream>

using namespace std;


void f(int x, int y)
{
    // the value of x = y is the value of x after the assignment
    int j = x = y;
    // p points to x
    int* p = &++x;
    // error : x++ is not an lvalue (it is not the value stored in x)
    int* q = &(x++);
    // address of the int with the larger value
    int* p2 = &(x > y ? x : y);
    // error : 1 is not an lvalue
    int& r = (x < y) ? x : 1;
}


// overflow
void f()
{
    int i = 1;
    while (0 < i) {
        ++i;
        cout << "i has become negative!" << i << '\n';
    }
}


// section 10.3.1 : evaluate order
// undefined whether f() or g() is called first
int x = f(2) + g(3);
int i = 1;
// undefined result
v[i] = i++;
// two arguments, should be avoided
f1(v[i], i++);
// one argument, i++, should be avoided
f2( (v[i], i++) );


// section 10.3.3 : operator precedence
// i & (mask == 0)
if (i & mask == 0)
if ((i & mask) == 0)


// section 10.3.4 : temporary objects
void f(sting& s1, string& s2, string& s3)
{
    const char* cs = (s1 + s2).c_str();
    cout << cs;
    if (strlen(cs = (s2 + s3).c_str()) < 8 && cs[0] == 'a') {
        // cs used here
    }
    // ...
}

void fgood(string& s1, string& s2, string& s3)
{
    cout << s1 + s2;
    string s = s2 + s3;
    if (s.length() < 8 && s[0] == 'a') {
        // use s here
    }
}


// a temporary can be used as an initializer
void g(const string&, const string&);

// return a reference of a local variable is an error

void h(string& s1, string& s2)
{
    const string& s = s1 + s2;
    string ss = s1 + s2;
    // we can use s and ss here
    g(s, ss);
}


void fc(Shape& s, int n, char ch)
{
    // construct a string with n copies of ch to pass to Shape::move()
    s.move(string(n, ch));
    // ...
}
