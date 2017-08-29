/**************************************************************
* Name     :  ex7-1-2.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年4月25日
**************************************************************/



/*
example 7.2 : pointers
*/


char c = 'a';
// p holds the address of c; & is the address-of operator
char* p = &c;
// c2 == 'a'; * is the deference operator
char c2 = *p;
// pointer to int
int* pi;
// pointer to pointer to char
char* ppc;
// array of 15 pointers to ints
int* ap[13];
// pointer to function taking a char* argument; returns an int
int (*fp)(char*);
// function taking a char* argument; returns a pointer to int
int* f(char*);


/*  section 7.2.1 : void*  */
void fvoid(int* pi)
{
    // ok : implicit conversion of int* to void*
    void* pv = pi;
    // error : can not dereference void*
    *pv;
    // error : can not increment void* (the size of object pointed to is unknown)
    ++pv;
    // explicit conversion back to int*
    int* pi2 = static_cast<int*>(pv);
    // error
    double* pd1 = pv;
    // error
    double* pd2 = pi;
    // unsafe
    double* pd3 = static_cast<double*>(pv);
    // allocate n bytes from my special heap
    void* my_alloc(size_t n);
}


/*  section 7.2.2 : nullptr  */
int* pi = nulptr;
double* pd = nullptr;
// error : i is not a pointer
int i = nullptr;
// x gets the value nullptr
int* x = 0;
// using the macro NULL, in C, NULL is typically (void*)0 ; in c++, error : can not assign a void* to int*
int* p = NULL;
