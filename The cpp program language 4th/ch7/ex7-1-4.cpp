/**************************************************************
* Name     :  ex7-1-4.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年4月25日
**************************************************************/



/*
example 7.4 : pointers and arrays
*/


// v[4]
int v[] = {1, 2, 3, 4};
// pointer to initial element
int* p1 = v;
// pointer to initial element
int* p2 = &v[0];
// pointer to one-beyond-last element
int* p3 = v + 4;
// error : before beginning, undefined: don't do it
int* p4 = v - 1;
// beyond the end, undefined : don't do it
int* p5 = v + 7;

// from <string.h>
extern "C" int strlen(const char*);
void f()
{
    char v[] = "Annemarie";
    // implicit conversion of char[] to char*
    char* p = v;
    strlen(p);
    // implicit conversion of char[] to char*
    strlen(v);
    // error : can not assign to array
    v = p;
}


#include <iostream>

using namespace std;

int main()
{
    const char* cpc = "LOVE";
    char vc[] = "love";
    char* pc = vc;
    cpc = pc;
    cout << "cpc = " << static_cast<const void*>(cpc) << '\n';
    cout << "pc = " << static_cast<const void*>(pc) << '\n';
    // cpc[0] = 'm';    // error : assignment of read-only location
    // OK
    pc[0] = 'm';
    cout << "vc : " << vc << '\n';
    cout << "pc : " << pc << '\n';
    cout << "cpc : " << cpc << endl;
    return 0;
}
