/**************************************************************
* Name     :  ex12-1-4.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年5月18日
**************************************************************/



/*
example 12.2 : argument passing
    section 12.2.1 : reference argument
*/


// section 12.2.1 : reference arguments
void f(int val, int& ref)
{
    ++val;
    ++ref;
    // ...
}


void g()
{
    int i = 1;
    int j = 1;
    f(i, j);
}

// the value of "arg" can not be modified
void f(const Large& arg)
{
    // (except by using explicit type conversion;)
}

// assume g() modify the arg
void g(Large& arg);

// number of C-style character string
int strlen(const char*);
// copy a C-style string
char* strcpy(char* to, const char* from);
// compare C-style strings
int strcmp(const char*, const char*);

// fortran-style sqrt taking a reference argument
float fsqrt(const float&);
// pass reference to temp holding 2.0f
void g(double d)
{
    float r = fsqrt(2.0f);
    // pass reference to r
    r = fsqrt(r);
    // pass reference to temp holding static_cast<float>(d)
    r = fsqrt(d);
}

void update(float& i);

void g(double d, float r)
{
    // error : const argument
    update(2.0f);
    // pass reference to r
    update(r);
    // error : type conversion required
    update(d);
}

// (non-const) lvalue reference argument
void f(vector<int>&);
// const lvlaue reference argument
void f(const vector<int>&);
// rvalue reference argument
void f(vector<int>&&);

void g(vector<int>& vi, const vector<int>& cvi)
{
    // call f(vector<int>&)
    f(vi);
    // call f(const vector<int>&)
    f(vci);
    // call f(vector<int>&&);
    f(vector<int>{1, 2, 3, 4});
}
