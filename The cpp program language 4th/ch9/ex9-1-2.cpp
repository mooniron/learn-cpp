/**************************************************************
* Name     :  ex9-1-2.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年5月6日
**************************************************************/



/*
example 9.1 : introduction
example 9.2 : statement summary
example 9.3 : declarations as statements
*/


#include <iostream>
#include <string>
#include <vector>


using namespace std;


// expression statement
a = b + c;
// if-statement
if (a == 7) {
    // execute if and only if a == 7
    b = 9;
}


/*  section 9.2  */


/*  section 9.3  */
void f(vector<<string>& v, int i, const char* p)
{
    if (p == nullptr) {
        return;
    }   // end if
    if (i < 0 || v.size() <= i) {
        error("bad index");
    }   // end if
    string s = v[i];
    if (s == p) {
        // ...
    }
    // ...
}   // end function


void use()
{
    string s1;
    s1 = "The best is the enemy of the good.";
    // ...
    // better performance
    string s2 {"Voltaire"};
}   // end function


void input()
{
    int buf[max];
    int count = 0;
    for (int i; cin >> i;) {
        if (i < 0) {
            error("unexpected negative value");
        }   // end if
        if (count == max) {
            error("buffer overflow");
        }
        buf[count++] = i;
    }   // end for
    // ...
}   // end function
