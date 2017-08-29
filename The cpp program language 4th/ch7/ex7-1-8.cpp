/**************************************************************
* Name     :  ex7-1-8.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年4月25日
**************************************************************/



/*
example 7.5 : pointers and const
*/


#include <iostream>

using namespace std;


// model is a const
const int model = 90;
// v[i] is a const
const int v[] = {1, 2, 3, 4};
// error : no initializer
//const int x;


void f()
{
    // error
    model = 200;
    // error
    v[2] = 3;
}


void g(const X* p)
{
    // can't modify *p here
}


void h()
{
    // val can be modified here
    X val;
    // can not be modified here
    g(&val);
    // ...
}


void f1(char* p)
{
    char s[] = "Gorm";

    // pointer to constant
    const char* pc = s;
    // error : pc points to constant
    pc[3] = 'g';
    // OK
    pc = p;

    // constant pointer
    char *const cp = s;
    // OK
    cp[3] = 'a';
    // error : cp is constant
    cp = p;

    // const pointer to const
    const char *const cpc = s;
    // error : cpc points to constant
    cpc[3] = 'a';
    // error : cpc is constant
    cpc = p;
}


// const pointer to char
char *const cp;
// pointer to const char
char const* pc;
// pointer to const char
const char* pc2;


// find first occurrence of c in p
const char* strchr(const char* p, char c);
// find first occurrence of c in p
char* strchr(char* p, char c);


void f4()
{
    int a = 1;
    const int c = 2;
    // OK
    const int* p1 = &c;
    // OK
    const int* p2 = &a;
    // error : initialization of int* with const int*
    int* p3 = &c;
    // try to change the value of c
    *p3 = 7;
}
