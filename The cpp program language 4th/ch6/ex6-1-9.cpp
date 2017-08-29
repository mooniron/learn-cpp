/**************************************************************
* Name     :  ex6-1-9.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年4月25日
**************************************************************/



/*
example 6.3 : declarations
*/


#include <iostream>
#include <vector>
#include <string>
#include <complex>

using namespace std;


int main()
{
    // set aside memory for a char and intialize it to 0
    char ch;
    string s;
    // set aside memory for an int initialized to 1
    auto count = 1;
    const double pi {3.1415926535897};
    // variable declaration
    extern int error_number;
    // set aside memory for a pointer to char, set aside memory for a string literal "Njal"
    // initialize the pointer with the address of that string literal
    const char* name = "Njal";
    const char* season[] = {"spring", "summer", "fall", "winter"};
    vector<string> people {name, "Skarphedin", "Gunnar"};
    // Date is a struct with three members
    struct Date {
        int d, m, y;
    };
    // day is a function that executes the specified code
    int day(Date* p) { return p->d; }
    // function declaration
    double sqrt(double);
    template<class T>
    T abs(T a) { return a < 0 ? -a : a; }
    // possible compile-time evaluation
    constexpr int fac(int n) { return (n < 2) ? 1 : n * fac(n - 1); }
    // compile-time initialization
    constexpr double zz {ii * fac(7)};
    // type alias
    using Cmplx = std::complex<double>;
    // Point is a name for std::complex<short>
    using Point = std::complex<short>;
    // type name declaration, defined elsewhere
    struct User;
    enum class Beer { Carlsberg, Tuborg, Thor };
    namespace NS { int a; }
}


double sqrt(double d) { /* ... */ }
int error_number = 1;
struct User { /* ... */ };


int count;
// error : redefinition
int count;
extern int error_number;
// error : type mismatch
extern short error_number;
// OK redeclaration
extern int error_number;


void f()
{
    // initialize count to 1
    int count {1};
    // name is a variable that points to a constant
    char* name {"Bjarne"};
    // assign 2 to count
    count = 2;
    //
    name = "Marian";

    // error : c is not declared a type
    const c = 8;
    // error : function gt not return a type
    gt(int a, int b);

    // int x; int y;
    int x, y;
    // int* p; int y;   NOT int* y;
    int* p, y;
    // int x; int* q;
    int x, *q;
    // int v[10]; int* pv;
    int v[10], *pv;
}
