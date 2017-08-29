/**************************************************************
* Name     :  ex17-1-5.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年6月10日
**************************************************************/



/*
example 17.4 : member and base initialization
*/


// section 17.4.1 : member initialization
class Club {
    string name;
    vector<string> members;
    vector<string> officers;
    Date founded;
    // ...
    Club(const string& n, Date fd);
};

Club::Club(const string& n, Date fd)
    : name {n}, members {}, officers {}, founded {fd}
{
    // ...
}

// equivalent to the previous version
Club::Club(const string& n, Date fd)
    : name {n}, founded {fd}
{
    // ...
}

struct B {
    B(int);
    /* ... */
};

struct BB : B {
    /* ... */
};

struct BBB : BB {
    // error : trying to initialize base's base
    BBB(int i) : B(i) { };
};


// section 17.4.1.1 : Member initialization and assignment
class X {
    const int i;
    Club cl;
    Club& rc;
    // ...
    X(int ii, const string& n, Date d, Club& c)
        : i {ii}, cl {n, d}, rc {c}
    {
    }
};


class Person {
    string name;
    string address;
    // ...
    Person(const Person&);
    Person(const string& n, const string& a);
};

Person::Person(const string& n, const string& a)
    : name {n}
{
    address = a;
}


// section 17.4.2 : base initializers
class B1 {
    // has default constructor
    B1();
};

// no default constructor
class B2 {
    B2(int);
};

struct D1 : B1, B2 {
    D1(int i) : B1 {}, B2 {i} { };
};

struct D2 : B1, B2 {
    // B1 {} is used implicitly
    D2(int i) : B2 {i} { };
};

struct D1 : B1, B2 {
    // error : B2 requires an int initializer
    D1(int i) { }
};


// section 17.4.3 : delegating constructors
class X {
    int a;
    validate(int x)
    {
        if (0 < x && x <= max) {
            a = x;
        }
        else {
            throw Bad_X(x);
        }
    }
public :
    X(int x) { validate(x); }
    X() { validate(42); }
    X(string s)
    {
        int x = to<int>(s);
        validate(x);
    }
    // ...
};

class X {
    int x;
public :
    X(int x)
    {
        if (0 < x && x <= max) {
            a = x;
        }
        else {
            throw Bad_X(x);
        }
    }
    X() : X {42} { }
    X(string s) : X {to<int>(s)} { }
    // ...
};

class X {
    int x;
public :
    X(int x)
    {
        if (0 < x && x <= max) {
            a = x;
        }
        else {
            throw Bad_X(x);
        }
    }
    // error
    X() : X {42}, a {56} { }
    // ...
};

class X {
    int x;
public :
    X(int x)
    {
        if (0 < x && x <= max) {
            a = x;
        }
        else {
            throw Bad_X(x);
        }
    }
    // error
    // likely error
    X() { X {42}; }
    // ...
};


// section 17.4.4 : in-class initializers
class A {
public :
    int a {7};
    int b = 77;
};

class A {
public :
    int a;
    int b;
    A() : a {7}, b {77} { }
};

class A {
public :
    A() : a {7}, b{5}, algorithm {"MD5"}, state {"Constructor run"} { }
    A(int a_val) : a {a_val}, b{5}, algorithm {"MD5"}, state {"Constructor run"} { }
    A(D d) : a {7}, b{g(d)}, algorithm {"MD5"}, state {"Constructor run"} { }
    // ...
private :
    int a, b;
    // cryptographic hash to be applied to all As
    HashFunction algorithm;
    // string indicating state in object life cycle
    string state;
};

class A {
public :
    A() : a {7}, b{5} { }
    A(int a_val) : a {a_val}, b{5} { }
    A(D d) : a {7}, b{g(d)} { }
    // ...
private :
    int a, b;
    // cryptographic hash to be applied to all As
    HashFunction algorithm {"MD5"};
    // string indicating state in object life cycle
    string state {"Constructor run"};
};

class A {
public :
    A() : { }
    A(int a_val) : a {a_val} { }
    A(D d) : b{g(d)} { }
    // ...
private :
    // the meaning of 7 for a is ...
    int a {7};
    // the meaning of 5 for b is ...
    int b {5};
    // cryptographic hash to be applied to all As
    HashFunction algorithm {"MD5"};
    // string indicating state in object life cycle
    string state {"Constructor run"};
};


int count = 0;
int count2 = 0;

int f(int i)
{
    return i + count;
}

struct S {
    // that is, ::count2
    int m1 {count2};
    // that is, this->m1 + ::count;
    int m2 {f(m1)};
    // very odd constructor
    S() { ++count2; }
};

int main()
{
    // {0, 0}
    S s1;
    ++count;
    // {1, 2}
    S s2;
}


// 17.4.5 : static member initialization
class Node {
    // ...
    // declaration
    static int node_count;
    // ...
};

// definition
int Node::node_count = 0;

class Curious {
public :
    // ok
    static const int c1 = 7;
    // error : not const
    static int c2 = 11;
    // ok,  but not static
    const int c3 = 13;
    // error : in-class initializer not constant
    static const int c4 = sqrt(9);
    // error : in-class not integral (use constexpr rather than const)
    static const float c5 = 7.0;
    // ...
};

// don't repeat initializer here
const int Curious::c1;
// ok : Curious::c1 has been defined
const int* p = &Curious::c1;

template<class T, int N>
// fixed-size array
class Fixed {
public :
    static constexpr int max = N;
    // ...
private :
    T a[max];
};

class X {
    enum { c1 = 7, c2 = 11, c3 = 13, c4 = 17 };
};


