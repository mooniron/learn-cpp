/**************************************************************
* Name     :  ex15-1-2.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年5月31日
**************************************************************/



/*
example 15.1 : separate compilation
example 15.2 : linkage
*/


// sectgion 15.2 : linkage
// file1.cpp :
int x = 1;
int f() { /* do something */ }

// file2.cpp :
extern int x;
int f();
void g() { x = f(); }


// file1.cpp :
int x = 1;
int b = 1;
extern int c;

// file2.cpp :
// means int x = 0;
int x;
extern double b;
extern int c;


// file.cpp :
// error : f() not (yet) declared
int g() { return f() + 7; }
// error : x not (yet) declared
int f() { return x; }
int x;


// internal linkage : not accessible from other translation units
static int x1 = 1;
// internal linkage : not accessible from other translation units
const char x2 = 'a';
// external linkage : accessible from other translation units
int x1 = 1;
// external linkage : accessible from other translation units
extern const char x2 = 'a';


// file1.cpp :
inline int f(int i) { return i; }
// file2.cpp :
inline int f(int i) { return i + 1; }

// file1.cpp
extern inline int g(int i);
// error : g() undefined in this translation unit
int h(int i) { return  g(i); }
// file2.cpp
extern inline int g(int i) { return i + 1; }
// ...


// h.h
inline int next(int i) { return i + 1; }
// file1.cpp
#include "h.h"
// fine
int h(int i) { return next(i); }
// file2.cpp
#include "h.h"
// ...


// file1.cpp
using T = int;
const int x = 7;
constexpr T c2 = x + 1;

// file2.cpp
using T = double;
const int x = 8;
constexpr T c2 = x + 9;

// file1.cpp
extern const int a = 77;
// file2.cpp
extern const int a;
void g()
{
    cout << a << '\n';
}




// section 15.2.1 : file-local names
// file1.cpp
namespace {
    class X { /* ... */ };
    void f();
    int i;
    // ...
}

// file2.cpp
class X { /*  ... */ };
void f();
int i;
// ...


// section 15.2.2 : header files
// from standard include directory
#include <iostream>
// from current directory
#include "myheader.h"



// section 15.2.3 : the one-definition rule
// file1.cpp :
struct S { int a; char b; };
void f(S*);
// file2.cpp
struct S { int a; char b; };
void f(S* p) { /* ... */ }

// s.h :
struct S { int a; char b; }
void f(S*);

// file1.cpp
#include "s.h"
// use f() here

// file2.cpp :
#include "s.h"
void f(S* p)
{
    /* ... */
}


// three ways of violating the ODR
// file1.cpp :
struct S1 { int a; char b; };
// error : double definition
struct S1 { int a; char b; };

// file1.cpp :
struct S2 { int a; char b; };
// file2.cpp :
// error
struct S2 { int a; char bb; };

// file1.cpp :
typedef int X;
struct S3 { X a; char b; };

// file2.cpp :
typedef char X;
// error
struct S3 { X a; char b; }


// s.h :
struct S { Point a; char b; };

// file1.cpp :
#define Point int
#include "s.h"
// ...

// file2.cpp :
class Point { /* ... */ };
#include "s.h"
// ...



// section 15.2.4 : standard-library headers
// for C++ compilers only
#ifdef __cplusplus
// the standard library is defined in namespace std
namespace std {
    // stdio functions have C linkage
    extern "C" {
        #endif
        /* ... */
        int printf(const char* ...);
        /* ... */
        #ifdef __cplusplus
    }
}

// ...
// make printf available in global namespace
using std::printf;
// ...
#endif


// section 15.2.5 : linkage to non-c++ code
// according to the C linkage conventions
extern "C" char* strcpy(char*, const char*);
// differ
extern char* strcpy(char*, const char*);


extern "C" int f();

int g()
{
    // error : no argument expected
    return f(1);
}

extern "C" {
    char* strcpy(char*, const char*);
    int strcmp(const char*, const char*);
    int strlen(const char*);
    // ...
}


extern "C" {
    #include <string.h>
}


#ifdef __cplusplus
extern "C" {
#endif
    char* strcpy(char*, const char*);
    int strcmp(const char*, const char*);
    int strlen(const char*);
    // ...
#ifdef __cplusplus
}
#endif


extern "C" {
    // any declaration here, for example
    // definition
    int g1;
    // declaration, not definition
    extern int g2;
}

// declaration, not definition
extern "C" int g3;
// definition
extern "C" { int g4; }

#include <cstdio>

void f()
{
    // ok
    std::printf("hello, ");
    // error : no global printf()
    printf("world\1");
}



// section 15.2.6 : linkage and pointers to functions
// FT has c++ linkage
typedef int (*FT) (const void*, const void*);

extern "C" {
    // CFT has C linkage
    typedef int (*CFT) (const void*, const void*);
    // cmp has C linkage
    void qsort(void* p, size_t n, size_t sz, CFT cmp);
}

// cmp has c++ linkage
void isort(void* p, size_t n, size_t sz, FT cmp);
// cmp has C linkage
void xsort(void* p, size_t n, size_t sz, CFT cmp);
// cmp has C++ linkage
extern "C" void ysort(void* p, size_t n, size_t sz, FT cmp);

// compare() has c++ linkage
int compare(const void*, const void*);
// ccmp() has C linkage
extern "C" int ccmp(const void*, const void*);

void f(char* v, int sz)
{
    // error
    qsort(v, sz, 1, &compare);
    // ok
    qsort(v, sz, 1, &ccmp);

    // ok
    isort(v, sz, 1, &compare);
    // error
    isort(v, sz, 1, &ccmp);
}


