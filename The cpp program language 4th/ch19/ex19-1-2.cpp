/**************************************************************
* Name     :  ex19-1-2.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年6月18日
**************************************************************/



/*
example 19.2 : special operators
*/


#include <iostream>
#include <vector>
#include <string>
#include <utility>

using namespace std;


// section 19.2.1 : subscripting
struct Assoc {
    // vector of {name, value} pairs
    vector<pair<string, int>> vec;
    //
    const int& operator[](const string&) const;
    int& operator[](const string&);
};

// search for s; return a reference to its value if found
// otherwise, make a new pair {s, 0} and return a reference to its value
int& Assoc::operator[](const string& s)
{
    for (auto& x : vec) {
        if (s == x.first) {
            return x.second;
        }
    }
    // initial value : 0
    vec.push_back({s, 0});
    // return last element
    return vec.back().second;
}

// count the occurrences of each word on input
int main()
{
    Assoc values;
    string buf;
    while (cin >> buf) {
        ++values[buf];
    }
    for (auto x : values.vec) {
        cout << '{' << x.first << ',' << x.second << "}\n";
    }
}


// section 19.2.2 : function call
struct Action {
    int operator()(int);
    pair<int, int> operator()(int, int);
    double operator()(double);
    // ...
};

void f(Action act)
{
    int x = act(2);
    auto y = act(3, 4);
    double z = act(2.3);
    // ...
}


class Add {
    complex val;
public :
    // save a value
    Add(complex c) : val {c} { }
    Add(double r, double i) : val {{r, i}} { }
    // add a value to argument
    void operator()(complex& c) const { c += val; }
};

void h(vector<complex>& vec, list<complex>& lst, complex z)
{
    for_each(vec.begin(), vec.end(), Add{2, 3});
    for_each(lst.bing(), lst.end(), Add{z});
}

template<typename Iter, typename Fct>
Fct for_each(Iter b, Iter e, Fct f)
{
    while (b != e) {
        f(*b++);
    }
    return f;
}

void h2(vector<complex<double>>& vec, list<complex<double>>& lst, complex<double> z)
{
    for_each(vec.begin(), vec.end(), [](complex<double>& a) { a += complex<double>{2, 3}; });
    for_each(lst.begin(), lst.end(), [z](complex<double>& a) { a += z; });
}


// section 19.2.3 : deferencing
class Ptr {
    // ..
    X* operator ->();
};

void f(Ptr p)
{
    // (p.operator->())->m = 7
    p->m = 7;
}

void g(Ptr p)
{
    // syntax error
    X* q1 = p->;
    // ok
    X* q2 = p.operator->();
}

// Disk_ptr
template<typename T>
class Disk_ptr {
    string identifier;
    T* in_core_address;
    // ...
public :
    Disk_ptr(const string& s) : identifier {s}, in_core_address {nullptr} { }
    ~Disk_ptr() { write_to_disk(in_core_address, identifier); }
    T* operator ->()
    {
        if (in_core_address == nullptr) {
            in_core_address = read_from_disk(identifier);
        }
        return in_core_address;
    }
};


// use Disk_ptr
struct Rec {
    string name;
    // ...
};

void update(const string& s)
{
    Disk_ptr<Rec> p {s};
    // update s; if necessary, first retrieve from disk
    p->name = "Roscoe";
    // ...
}   // p’s destructor writes back to disk

// is true
p->m == (*p).m
// is true
(*p).m == p[0].m
// is true
p->m == p[0].m


template<typename T>
class Ptr {
    Y* p;
public :
    // deference to access member
    Y* operator ->() { return p; }
    // deference to acess while object
    Y& operator *() { return *p; }
    // deference to access element
    Y& operator [](int i) { return p[i]; }
    // ...
};


// section 19.2.4 : increment and decrement
// traditional use
void f1(X a)
{
    X v[200];
    X* p = &v[0];
    p--;
    // oops : p out of range
    *p = a;
    ++p;
    *p = a;
}

// checked
void f2(Ptr<X> a)
{
    X v[200];
    Ptr<X> p(&v[0], v);
    p--;
    // run-time error : p out of range
    *p = a;
    ++p;
    // ok
    *p = a;
}


template<typename T>
class Ptr {
    T* ptr;
    T* array;
    int sz;
public :
    template<int N>
    // bin to array a, sz == N, initial value p
    Ptr(T* p, T (&a)[N]);
    // bin to array a of size s, initial value p
    Ptr(T* p, T* a, int s);
    // bin to single object, sz == 0, initial value p
    Ptr(T* p);
    // prefix
    Ptr& operator++();
    // postfix
    Ptr operator++(int);
    // prefix
    Ptr& operator--();
    // postfix
    Ptr operator--(int);
    // presix
    T& operator*();
};


// return the current object after incrementing
// maybe wrong version
template<typename T>
Ptr& Ptr<T>::operator++()
{
    // ... check that ptr + 1 can be pointed to ...
    return *++ptr;
}

// return the current object after incrementing
// my version
template<typename T>
Ptr& Ptr<T>::operator++()
{
    // ... check that ptr + 1 can be pointed to ...
    ++ptr;
    return *this;
}

// increment and return a Ptr with the old value
template<typename T>
Ptr Ptr<T>::operator++(int)
{
    // ... check that ptr + 1 can be pointed to ...
    Ptr<T> old {ptr, array, sz};
    ++ptr;
    return old;
}


// checked
void f3(T a)
{
    T v[200];
    Ptr<T> p(&v[0], v, 200);
    // suffix p--
    p.operator--(0);
    // run-time error : p out of range
    p.operator*() = a;
    // prefix : ++p
    p.operator++();
    // ok
    p.operator*() = a;
}


// section 19.2.5 : allocation and deallocation
// use for individual object
void* operator new(size_t);
// use for array
void* operator new[](size_t);
// use for individual object
void operator delete(void*, size_t);
// use for array
void operator delete[](void* size_t);


class Employee {
public :
    // ...
    void* operator new(size_t);
    void* operator delete(void*, size_t);
    void* operator new[](size_t);
    void operator delete[](vid*, size_t);
};

void* Empl oyee::operator new(size_t s)
{
    // allocate s bytes of memory an return a pointer to it
}

void Employee::operator delete(void* p, size_t s)
{
    // delete only if p != 0
    if (p) {
        // assume p points to a bytes of memory allocated by Employee::operator new()
        // and free that memory for reuse
    }
}

// potential trouble (the exact type is lost)
Employee* p = new Manager;
// ...
// hope Employee has a virtual destructor
delete p;



// section 19.2.6 : user-defined literals
// imaginary literal
constexpr complex<double> operator"" i(long double d)
{
    // complex is a literal type
    return {0, d};
}

// std::string literal
std::string operator"" s(const char* p, size_t n)
{
    // requires free-store allocation
    return string {p, n};
}


template<typename T>
void f(const T&);

void g()
{
    // pass pointer to char*
    f("Hello");
    // pass (five-character) string object
    f("Hello"s);
    // pass (six-character) string object
    f("Hello\n"s);
    // complex{2, 1}
    auto z = 2 + 1i;
}


Bignum operator"" x(const char* p)
{
    return Bignum(p);
}

void f(Bignum);

f(123456789012345678901234567890123456789012345x);


string operator"" s(const char* p, size_t n);
// calls operator ""("one two", 7)
string s12 = "one two"s;
// calls operator ""("two\ntwo", 7)
string s22 = "two\ntwo"s;
// calls operator ""("two\\ntwo", 8)
string sxx = R"(two\ntwo)"s;


template<char...>
// base 3, i.e., ternary
constexpr int operator"" _b3();

// ok : means 2 * 9 + 0 * 3 + 1 == 19
201_b3
// error : 4 is not a ternary digit
241_b3


// x to the nth power for n >= 0
constexpr int ipow(int x, int n)
{
    return (n > 0) ? x * ipow(n - 1) : 1;
}

// handle the single ternary digit case
template<char c>
constexpr int b3_helper()
{
    static_assert(c < '3', "not a ternary digit");
    return c;
}

// peel off one ternary digit
template<char c, char... tail>
constexpr int b3_helper()
{
    static_assert(c < '3', "not a ternary digit");
    return ipow(3, sizeof...(tail)) * (c - '0') + b3_helper(tail...);
}

// base 3, i.e., ternary
template<char... chars>
constexpr int operator"" _b3()
{
    return b3_helper(chars...);
}


namespace Numerics {
    // ...
    class Bignum { /* ... */ };
    namespace literals {
        Bignum operator"" x(const char*);
    }
    // ...
}

using namespace Numerics::literals;


// reserve by the standard library
123km
// available for your use
123_km
