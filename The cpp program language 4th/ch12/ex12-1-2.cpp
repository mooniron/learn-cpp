/**************************************************************
* Name     :  ex12-1-2.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年5月14日
**************************************************************/



/*
example 12.1 : function declarations
*/


// no arguments and return an Elem*
Elem* next_elem();
// int argukment; return nothing
void exit(int);
// double argument; return a double
double sqrt(double);
// call sqrt() with the argument dou& string::(int)
char& string::operator[](int);

// parts of a declaration
struct S {
    [[noreturn]] virtual inline auto f(const unsigned long int *const) ->void const noexcept;
};

// a declaration
void swap(int*, int*);

// a definition
void swap(int* p, int* q)
{
    int t = *p;
    *p = *q;
    *q = t;
}


// two declarations of the same function
// type is void(int)
void f(int);
// type is void(int)
void f(const int);

// return a reference to the larger of a, b, and c
int& max(int& a, int& b, int& c);

int& max(int& x1, int& x2, int& x3)
{
    return (x1 > x2) ? ((x1 > x3) ? x1 : x3) : ((x2 > x3) ? x2 : x3);
}


// no use of the third argument
void search(table* t, const char* key, const char*)
{
    // ...
}


// same declarations
// prefix return type
string to_string(int a);
// suffix return type
auto to_string(int a) -> string;

template<class T, class U>
auto product(const vector<T>& x, const vector<U>& y) -> decltype(x * y);


// error : no value returned
int f1() {}
// ok
void f2() {}
// ok
int f3() {
    return 1;
}
// error : return value in void function
void f4() {
    return 1;
}
// error : return value missing
int f5() {
    return;
}
// ok
void f6() {
    return;
}

int fac(int n)
{
    return (n > 1) ? n * fac(n - 1) : 1;
}

// more than one return statement
int fac2(int n)
{
    if (n > 1) {
        return n * fac2(n - 1);
    }
    return 1;
}

// 1 is implicitly converted to double{1}
double f() {
    return 1;
}

int* fp() {
    int local = 1;
    // ...
    // bad
    return &local;
}

int& fr() {
    int local = 1;
    // ...
    // bad
    return local;
}


void g(int* p);

void h(int* p)
{
    // ...
    // ok : equivalent to "g(p); return;"
    return g(p);
}


// section 12.1.5 inline functions
inline int fac(int a)
{
    return (n < 2) ? 1 : n * fac(n - 1);
}


// section 12.1.6 : constexpr functions
constexpr int fac(int n)
{
    return (n > 1) ? n * fac(n - 1) : 1;
}

// must be evaluated at compile time
constexpr int f9 = fac(9);

int f(int n)
{
    // may be evaluated at compile time
    int f5 = fac(5);
    // evaluated at run time (n is a variable)
    int fn = fac(n);
    // must be evaluated at compile time
    constexpr int f6 = fac(6);
    // error : can't guarantee compile-time evaluation
    constexpr int fnn = fac(n);
    // ok : array bounds must be constants and fac(4) is constexpr
    char a[fac(4)];
    // error : array bounds must be constants and n is a variable
    char a2[fac(n)];
    // ...
}


// constexpr functions consist of only return statement
int glob;

// error : constexpr function can not be void
constexpr void bad1(int a)
{
    // error : side effect in constexpr function
    glob = a;
}

constexpr int bad2(int a)
{
    // error : if-statement in constexpr function
    if (a >= 0) return a;
    else return -a;
}


constexpr int bad3(int a)
{
    // error : local variable in constexpr function
    int sum = 0;
    // error : loop-statement in constexpr function
    for (int i = 0; i < a; ++i) {
        sum += fac(i);
    }
    return sum;
}


// section 12.1.6.1 : constexpr and references
constexpr int ftbl[] {1, 2, 3, 5, 8, 13};
constexpr int fib(int n)
{
    return (n < sizeof(ftbl) / sizeof(*ftbl)) ? ftbl[n] : fib(n);
}


template<>
class complex<float>
{
public :
    // ...
    explicit constexpr complex(const complex<double>&);
}

constexpr complex<float> z {2.0};

// ok
constexpr const int* addr(const int& r)
{
    return &r;
}


static const int x = 5;
// ok
constexpr const int* p1 = addr(x);
// ok
constexpr int xx = *p1;
static int y;
constexpr const int* p2 = addr(y);
// error : attempt to read a variable
constexpr int yy = *p2;
// error : address of temporary
constexpr const int* tp = addr(5);


// section 12.1.6.2 : conditional evaluation
constexpr int check(int i)
{
    return (low <= i && i < high) ? i : throw out_of_range();
}

constexpr int low = 0;
constexpr int high = 99;

// ...
constexpr int val = check(f(x, y, z));


// section 12.1.7 : noreturn
// exit will never return
[[noreturn]] void exit(int);


// section 12.1.8 : local variables
void f(int a)
{
    while (a--) {
        // initialize once
        static int n = 0;
        // initialize each while loop
        int x = 0;
        cout << "n == " << n++ << ", x == " << x++ << '\n';
    }
}


int main()
{
    f(3);

    return 0;
}


int fn(int n)
{
    // ok
    static int n1 = n;
    // undefined
    static int n2 = fn(n - 1) + 1;
    return n;
}
