/**************************************************************
* Name     :  ex25-1-2.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年7月17日
**************************************************************/



/*
example 25.2 : template parameters and arguments
*/


// section 25.2.1 : types as arguments
template<typename T>
void f(T);

template<typename T>
class X {
    // ...
};

// T is deduced to be int
f(1);
// T is double
f<double>(1);
// T is complex<double>
f<complex<double>>(1);

// T is double
X<double> x1;
// T is complex<double>
X<complex<double>> x2;

// vector of doubles
vector<double> x1;
// vector of complex<double>
vector<complex<double>> x2;

class X {
    class M { /* ... */ };
    // ...
    void mf();
};

void f()
{
    struct S { /* ... */ };
    // ok
    vector<S> vs;
    // error : X::M is private
    vector<X::M> vm;
}

void M::mf()
{
    // error : no S in scope
    vector<S> vs;
    // ok
    vector<M> vm;
    // ...
}


// section 25.2.2 : values as arguments
template<typename T, int max>
class Buffer {
    T v[max];
public :
    Buffer() { };
    // ...
};

Buffer<char, 128> cbuf;
Buffer<int, 5000> ibuf;
Buffer<Record, 8> rbuf;

template<typename T, char* label>
class X {
    // ...
};

// error : string literal as template argument
X<int, "BMW323Ci"> x1;

char lx2[] = "BMW323Ci";
// ok : lx2 has external linkage
X<int, lx2> x2;

constexpr int max = 200;

void f(int i)
{
    // error : constant expression expected
    Buffer<int, i> bx;
    // ok : constant expression
    Buffer<int, maxx> bm;
}

template<typename T, int max>
class Buffer {
    T v[max];
public :
    // error : attempt to assign to template value argument
    Buffer(int i) { max = i; }
    // ...
};

template<typename T, T default_value>
class Vec {
    // ...
};

Vec<int, 42> c1;
Vec<string, ""> c2;

template<typename T, T default_value = T{}>
class Vec {
    // ...
};

Vec<int, 42> c1;
// default_value is int {}, that is 0
Vec<int> c11;
Vec<string, "for tytwo"> c2;
// default_value is string{}; that is ""
Vec<string> c22;


// section 25.2.3 : operations as arguments
template<typename Key, class V>
class map {
    // ...
};

template<typename Key, typename V, bool(*cmp)(const Key&, cosnst Key&)>
class map {
public :
    map();
    // ...
};

// compare case insensitive
bool insensitive(const string& x, const string& y)
{
    // ...
}

// compare using insensitive()
map<string, int, insensitive> m;

template<typename Key, class V, typename Compare = std::less<Key>>
class map {
public :
    // use the default comparison
    map() { /* ... */ }
    // override the default
    map(Compare c) : cmp {c} { /* ... */ }
    // ...
    // default comparison
    Compare cmp {};
};

// use the default comparison (less<string>)
map<string, int> m1;
// compare using greater<string>()
map<string, int, std::greater<string>> m2;
// make a comparison object
Complex_compare f3 {"French", 3};
// compare using f3()
map<string, int, Complex_compare> m3 {f3};

using Cmp = bool(*)(const string&, const string&);
// compare using a pointer to function
map<string, int, Cmp> m4 {insensitive};
// using lambdas
map<string, int, Cmp> m4 {[](const string& a, const string& b) { return a > b}; };
// error
map<string, int, Cmp> c3 {[](const string& x, const string& y) const { return x < y; }};

auto cmp = [](const string& x, const string& y) const { return x < y; }
map<string, int, decltype(cmp)> c4 {cmp];


// section 25.2.4 : templates as arguments
template<typename T, template<typename>class C>
class Xrefd {
    C<T> mems;
    C<T*> refs;
    // ...
};

// use default allocator
template<typename T>
using My_vec = vector<T>;
// store cross references for Entrys in a vector
Xrefd<Entry, My_vec> x1;

template<typename T>
class My_container {
    // ...
};

// store cross references for Records in a My_container
Xrefd<Record, My_container> x2;

template<typename C, typename C2>
class Xrefd2 {
    C mems;
    C2 refs;
    // ...
};

Xrefd2<vector<Entry>, set<Entry*>> x;


// section 25.2.5 : default template arguments
template<typename Key, class V, typename Compare = std::less<Key>>
class map {
public :
    explicit map(const Compare& comp = {});
    // ...
};

// will use less<string> for comparisons
map<string, int> m1;
// same type as m1
map<string, int, less<string>> m2;

struct No_case {
    // define operator()() to do case-insensitive string comparison
};

// m3 is  of a different type from m1 and m2
map<string, int, No_case> m3;

map<string, int, Complex_compare> m {Complex_compare{"French", 3}};

// error : default argument not trailing
void f1(int x = 0, int y);
// ok
void f2(int x = 0, int y = 1);
// syntax error
f2(, 2);
// call f2(2, 1)
f2(2);

// default argument not trailing
template<typename T1 = int, typename T2>
class X1 {
    // ...
};

// ok
template<typename T1 = int, typename T2 = double>
class X2 {
    // ...
};

// syntax error
X2<, float> v1;
// v2 is X2<float, double>
X2<float> v2;


// section 25.2.5.1 : default function template arguments
// convert Source to Target
template<typename Target = string, typename Source = string>
Target to(Source arg)
{
    stringstream interpreter;
    Target result;
    if (!(interpreter << arg) || !(interpreter >> result) || !(interpreter >> std::ws).eof()) {
        throw runtime_error{"to<>() failed"};
    }
    return result;
}

// very explicit (and verbose)
auto x1 = to<string, double>(1.2);
// Source is deduced to double
// Target is defaulted to string, Source is deduced to double
auto x2 = to<string>(1.2);
// the <> is redundant
auto x4 = to(1, 2);

