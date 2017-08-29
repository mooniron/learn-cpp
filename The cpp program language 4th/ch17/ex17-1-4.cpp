/**************************************************************
* Name     :  ex17-1-4.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年6月10日
**************************************************************/



/*
example 17.3 : class object initialization
*/


#include <string>

using namespace std;


// section 17.3.1 : initialization without constructors
int a {1};
char* p {nullptr};

struct Work {
    string author;
    string name;
    int year;
};

// memberwise initialization
Work s9 {
    "Beethoven",
    "Symphony No. 9 in D minor, Op. 125; Choral",
    1874
};

// copy initialization
Work currently_playing {s9};
// default initialization
Work none {};
Work alpha;

void f9)
{
    Work beta;
    // ...
}

// input buffer
// uninitialization as local variable for performance critical
struct Buf {
    int count;
    char buf[16 * 1024];
};

// statically allocated, so initialized by default
Buf buf0;
// == Buf buf0 {};

void f()
{
    // leave elements uninitialized
    Buf buf1;
    // I really want to zero out those elements
    Buf buf2 {};
    // *p1 is uninitialized
    int* p1 = new int;
    // *p2 == 0
    int* p2 = new int {};
    // *p3 == 7
    int* p3 = new int {7};
    // ...
}


// control access to T* member
template<class T>
class Checked_pointer {
public :
    // check for nullptr and return value
    T& operator*();
private :
    T* p;
};

// error : can't access p.p, it needs a constructor to initialize it
Checked_pointer<int> p {new int {7}};



// section 17.3.2 : initialization using constructors
struct X {
    X(int);
};

// error : no initializer
X x0;
// error : empty initializer
X x1 {};
// ok
X x2 {2};
// error : wrong initialzer type
X x3 {"two"};
// error : wrong number of initializers
X x4 {1, 2};
// ok : a copy constructor is implicitly defined
X x5 {x4};


struct Y : X {
    // provide default initializer for member m
    X m {0};
    // initialize base and member
    Y(int a) : X {a}, m {a} { };
    // initialize base and member
    Y() : X {0} { };
};

// initialize global variable
X g {1};

void f(int a)
{
    // error : no default value for X
    X def {};
    // ok : use default constructor
    Y de2 {};
    // initialize local variable
    X* p {nullptr};
    X var {2};
    // initialize object on free store
    p = new X {4};
    // initialize array elements
    X a[] {1, 2, 3};
    // initialize vector elements
    vector<X> v {1, 2, 3, 4};
}


struct Y : X {
    X m;
    // syntax error : can't use = for member initialization
    Y(int a) : X(a), m = a { };
};

void f(int a)
{
    // function return an X (surprise!?)
    X def();
    // initialize local variable
    X* p {nullptr};
    X var = 2;
    // syntax error : can't use = for new
    p = new X = 4;
    // error : cna't use () for array initialization
    X a[] (1, 2, 3);
    // error : can't use () for list elements
    vector<X> v (1, 2, 3, 4);
}


struct S {
    S(const char*);
    S(double*);
};

// S::S(const char*)
S s1 {"Napier"};
// S::S(double*)
S s2 {new double {1.0}};
// ambiguous : S::S(const char*) or S::S(double*) ?
S s3 {nullptr};


// section 173.2.1 : initialization by constructors
struct S1 {
    // no constructor
    int a, b;
};

struct S2 {
    int a, b;
    // constructor
    S2(int aa = 0, int bb = 0) : a (aa), b (bb) { };
};

// error : no constructor
S1 x11 (1, 2);
// OK : memberwise initialization
S1 x12 {1, 2};
// error : no constructor
S1 x13 (1);
// ok : x14.b becomes 0
S1 x14 {1};

// ok : use constructor
S2 x21 (1, 2);
// ok : use constructor
S2 x22 {1, 2};
// ok : use constructor and one default argument
S2 x23 (1);
// ok : use constructor and one default argument
S2 x24 {1};

// one elemnt with the value 77
vectgor<int> v1 {77};
// 77 elements with the default value 0
vector<int> v2 (77);

// 77 elements with the default value ""
vector<string> v1 {77};
// 77 elements with the default value ""
vector<string> v2 (77);
// vector<string> (std;:initializer_list<string>) doesn't accept {77}
// one element with the value "Boohl"
vector<string> v3 {"Boohl"};
// error : no constructor takes a string argument
vector<string> v4 ("Boohl");

// 100 int*s initialized to nullptr
vector<int*> v5 {100.0};
// 2 int*s initialized to nullptr
vector<int*> v6 {0, 0};
// empty vector (v7.size() == 0)
vector<int*> v7 (0, 0);
// empty vector (v8.size() == 0)
vector<int*> v8;


// section 17.3.3 : default constructors
class Vector {
public :
    // default constructor : no element
    Vector();
    // ...
};

// OK
Vector v1;
// OK
Vector v2 {};

class String {
public :
    // default constructor empty string
    String(const char* p = "");
    // ...
};

// ok
String s1;
// ok
String s2 {};


void f()
{
    // uninitialized
    int a0;
    // function declaration (intended?)
    int a1();
    // a2 becomes 0
    int a2 {};
    // d becomes 0.0
    double d {};
    // p becomes nullptr
    char* p {};
    // uninitialized int
    int* p1 = new int;
    // the int is initialized to 0
    int* p2 = new int {};
}


template<class T>
struct Handle {
    T* p;
    Handle(T* pp = new T {}) : p {pp} { }
    // ...
};

// will generate int {}
Handle<int> px;


int glob {9};

struct X {
    // ok
    const int a1 {7};
    // error : requires a user-defined constructor
    const int a2;
    // ok
    const int& r {9};
    // ok
    int& r1 {glob};
    // error : requires a user-defined constructor
    int& r2;
};

// error : no default constructor for x
X x;

// has default constructor
struct S1 {
    S1();
};

// no default constructor
struct S2 {
    S2(string);
};

// OK : 10default elements S2
S1 a1[10];
// error : cannot initialize elements
S2 a2[10];
// ok : two element;
S2 a3[] {"alpha", "beta"};
// ok : 10 default elements
vector<S1> v1(10);
// error : cannot initialize elements
vector<S2> v2(10);
// ok : two elements
vector<S2> {"alpha", "beta"};
// ok : 10 elements each initialized to S2 {""}
vector<S2> v2 (10, "");
// ok no elements
vector<S2> v4;



// section 17.3.4 initializer-list constructors
vector<double> v = {1, 2, 3.456, 99.99};
list<pair<string, string>> languages = {{"Nygaard", "Simula"}, {"Richarda", "BCPL"}};
map<vector<string>, vector<int>> years = {
    {{"Marice", "Vincent", "Wilkes"}, {1913, 1945, 1951, 1967, 2000}},
    {{"Martin", "Richards"}, {1982, 2003, 2007}},
    {{"David", "John", "Wheeler"}, {1927, 1947, 1951, 2004}}
};


void f(initializer_list<int>);
f({1, 2});
f({23, 345, 4567, 56789});
// the empty list
f({});
// error : function call () missing
f{1, 2};

years.insert({{"Bjarne","Stroustrup"},{1950, 1975, 1985}});


// section 17.3.4.1 : initializer_list constructor disambiguation
struct X {
    X(initializer_list<int>);
    X();
    X(int);
};

// empty list : default constructor or initializer list constructor? (the default constructor)
X x0 {};
// one integer : an int argument or a list of one element? (the initializer list constructor)
X x1 {1};

// one element
vector<int> v1 {1};
// two elements
vector<int> v2 {1, 2};
// three elements
vector<int> v3 {1, 2, 3};

vector<string> vs1 {"one"};
vector<string> vs2 {"one", "two"};
vector<string> vs3 {"one", "two", "three"};

// one element with the default value {0}
vector<int> v1 (1);
// one element with value {2}
vector<int> v2 (1, 2);


// 17.3.4.2 : use of initializer_lists
void f(initializer_list<int> args)
{
    for (int i = 0; i != args.size(); ++i) {
        cout << args.begin()[i] << "\n";
    }
}

// equivalenty
void f(initializer_list<int> args)
{
    for (auto p = args.begin(); p != args.end(); ++p) {
        cout << *p << '\n';
    }
}

void f(initializer_list<int> args)
{
    for (auto x : args) {
        cout << x << '\n';
    }
}

int f(std::initializer_list<int> x, int val)
{
    // error : attempt to change the value of an initializer-list element
    *x.begin() = val;
    // ok
    return *x.begin();
}

void g()
{
    for (int i = 0; i != 10; ++i) {
        cout << f({1, 2, 3}, i) << '\n';
    }
}


template<class E>
class Vector {
public :
    // initializer-list constructor
    Vector(std::initializer_list<E> s);
    // ...
private :
    int sz;
    E* elem;
};

template<class E>
Vector::Vector(std;::initializer_list<E> s)
    // set vector size
    : sz {s.size()}
{
    // get the right amount of space
    reserve(sz);
    // initialize elements in elem[0 : s.size())
    uninitialized_copy(s.begin(), s.end(), elem);
}



// section 17.3.4.3 : direct and copy initialization
vector<vector<double>> vs = {
    // OK: vector of five elements
    {10, 11, 12, 13, 14},
    // OK: vector of one element
    {10},
    // error : vector<double>(int) is explicit
    10,
    // OK: vector of five elements
    vector<double>{10, 11, 12, 13},
    // OK: vector of one element with value 10.0
    vector<double>{10},
    // OK: vector of 10 elements with value 0.0
    vector<double>(10),
};

// ok : v1 has 7 elements;
vector<double> v1 (7);
// error : no conversion from int to vector<double>
vector<double> v2 = 9;
void f(const vector<double>&);

void g()
{
    // error : no conversion from int to vector
    v1 = 9;
    // error : no conversion from int to vector
    f(9);
}

// ok : v1 has one element with value 7
vector<double> v1 {7};
// ok : v1 has one element with value 9
vector<double> v1 {9};

void f(const vector<double>&);
void g()
{
    // ok : v1 now has one element with the value 9
    v1 = {9};
    // ok : f is called with the list {9}
    f({9});
}

// ok : v1 has three elements with  values {7, 8, 9}
vector<double> v1 {7, 8, 9};
// ok : v2 has three elements with  values {9, 8, 7}
vector<double> v2 = {9, 8, 7};

void f(const vector<double>&);
void g()
{
    // ok : v1 now has three elements with values {9, 10, 11}
    v1 = {9, 10, 11};
    // ok
    f({9, 8, 7, 6, 5, 4});
}

// ok : v1 has one element
vector<string> v1 {"Anya"};
// ok : one element
vector<string> v2 {"courtney"};

void f(const vector<string>&);
void g()
{
    // ok : v1 now has one element with the value "Gavin"
    v1 = {"Gavin"};
    // ok : f is called with the list {"Horah"}
    f({"Norah"});
}

