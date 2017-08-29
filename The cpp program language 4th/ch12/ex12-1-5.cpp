/**************************************************************
* Name     :  ex12-1-5.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年5月18日
**************************************************************/



/*
example 12.2 : argument passing
    section 12.2.2 : array arguments
*/


//
int strlen(const char*);

void f()
{
    char v[] = "Annemarie";
    int i = strlen(v);
    int j = strlen("Nicholas");
}


void odd(int* p);
void odd(int a[]);
void odd(int buf[1020]);

// one way
void compute1(int* vec_ptr, int vec_size);

void f(int (&r)[4]);

void g()
{
    int a1[] = {1, 2, 3, 4};
    int a2[] = {1, 2};
    // ok
    f(a1);
    // error : wrong number of elements
    f(a2);
}

// references to arrays in templates
template<class T, int N>
void f(T(&r)[N])
{
    // ...
}

int a1[10];
double a2[100];

void g()
{
    // T is int, N is 10
    f(a1);
    // T is double；N is100
    f(a2);
}

// arrays of pointers
const char* day[] = {"mon", "tue", "wed", "thu", "fri", "sat", "sun"};
