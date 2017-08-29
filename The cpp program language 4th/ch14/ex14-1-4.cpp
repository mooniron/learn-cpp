/**************************************************************
* Name     :  ex14-1-4.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年5月29日
**************************************************************/



/*
example 14.4 : composition using namespaces
*/


// section 14.4.1 : convenience vs. safety
namespace X {
    int i, j, k;
}

int k;

void f1()
{
    int i = 0;
    // make names from X accessible
    using namespace X;
    // local i
    i++;
    // X::j
    j++;
    // error : X's k or the global k?
    k++;
    // the global k
    ::k++;
    // X's k
    X::k++;
}

void f2()
{
    int i = 0;
    // error : i declared twice in f2()
    using X::i;
    using X::j;
    // hides global k
    using X::k;

    i++;
    // X::j
    j++;
    // X::k
    k++;
}


// section 14.4.2 namespace aliases
// short name, will clash (eventually)
namespace A {
    // ...
}

A::String s1 = "Grieg";
A::String s2 = "Nielsen";

// too long
namespace American_Telephone_and_Telegraph {
    // ...
}

American_Telephone_and_Telegraph::String s3 = "Grieg";
American_Telephone_and_Telegraph::String s4 = "Nielsen";

// use namespace alias to shorten names;
namespace ATT = American_Telephone_and_Telegraph;

ATT::Sting s3 = "Grieg";
ATT::String s4 = "Nielsen";

namespace Lib = Foundation_library_v2r11;

Lib::set s;
Lib::String s5 = "Sibelius";


// section 14.4.3 : namespace composition
namespace His_string {
    class String { /* ... */ };
    String operator+(const String&, const String&);
    String operator+(const String&, const char*);
    void fill(char);
    // ...
}

namespace Her_vector {
    template<class T>
    class Vector { /* ... */ };
    // ...
}

namespace My_lib {
    using namespace His_string;
    using namespace Her_vector;
    void my_fct(String&);
}

void f()
{
    // finds My_lib::His_string::String
    My_lib::String s = "Byron";
    // ...
}

using namespace My_lib;

void g(Vector<String>& vs)
{
    // ...
    my_fct(vs[5]);
}

// error : no fill() declared in My_lib
void My_lib::fill(char c)
{
    // ...
}

// ok : fill() declared in His_string
void His_string::fill(char c)
{
    // ...
}

// ok: String is My_lib::String, meaning His_string::String
void My_lib::my_fct(String& v)
{
    // ...
}



// section 14.4.4 : composition and selection
namespace His_lib {
    class String { /* ... */ };
    template<class T>
    class Vector { /* ... */ };
    // ...
}

namespace Her_lib {
    template<class T>
    class Vector { /* ... */ };
    class String { /* ... */ };
    // ...
}

namespace My_lib {
    // everything from His_lib
    using namespace His_lib;
    // everything from Her_lib
    using namespace Her_lib;

    // resolve potential clash in favor of His_lib
    using His_lib::String;
    // resolve potential clash in favor of Her_lib
    using Her_lib::Vector;

    // additional stuff
    template<class T>
    class List { /* ... */ };
    // ...
}


namespace Lib2 {
    // everything from His_lib
    using namespace His_lib;
    // everything from Her_lib
    using namespace Her_lib;

    // resolve potential clash in favor of His_lib
    using His_lib::String;
    // resolve potential clash in favor of Her_lib
    using Her_lib::Vector;

    // rename
    using Her_string = Her_lib::String;
    // rename
    template<class T>
    using His_vec = His_lib::Vector<T>;

    template<class T>
    class List { /* ... */ };
    // ...
}



// section 14.4.5 : namespaces and overloading
// old A.h :
void f(int);
// ...

// old B.h :
void f(char);
// ...

// old user. :
#include "A.h"
#include "B.h"

void g()
{
    // calls f(char) from B.h
    f('a');
    //
}


// new A.h :
namespace A {
    void f(int);
}

// new B.h :
namespace B {
    void f(char);
}

// new user.c :
#include "A.h"
#include "B.h"

using namespace A;
using namespace B;

void  g()
{
    // calls f(char) from B.h
    f('a');
}


sort(v.begin(), v.end());
sort(v);

#include <algorithm>

namespace Estd {
    using namespace std;
    template<class C>
    void sort(C& c) { std::sort(c.begin(), c.end()); }

    template<class C, class P>
    void sort(C& c, P p) { std::sort(c.begin(), c.end(), p); }
}


using namespace Estd;

template<class T>
void print(const vector<T>& v)
{
    for (auto& x : v) {
        cout << x << ' ';
    }
    cout << '\n';
}

void f()
{
    std::vector<int> v {7, 3, 9, 4, 0, 1};

    sort(v);
    print(v);
    sort(v. [](intx, int y) { return x > y; });
    print(v);
    sort(v.begin(), v.end());
    print(v);
    sort(v.begin(), v.end(), [](int x, int y) { return x > y; });
    print(v);
}



// section 14.4.6 : versioning
namespace Popular {
    // V3_2 provides the default meaning of Popular
    inline namespace V3_2 {
        double f(double);
        int f(int);
        template<class T>
        class C { /* ... */ };
    }
    namespace V3_0 {
        // ...
    }
    namespace V2_4_2 {
        double f(double);
        template<class T>
        class C { /* ... */ };
    }
}


using namespace Popular;

void f()
{
    // Popular::V3_2::f(int)
    f(1);
    // Popular::V3_0::f(double)
    V3_0::f(1);
    // Popular::V2_4_2::f(double)
    V2_4_2::f(1);
}

template<class T>
Popular::C<T*> { /* ... */ };

// file V3_common
// ... lots of declarations ...
// file V3_2
// V3_2 provides the default meaning of Popular
namespace V3_2 {
    double f(double);
    int f(int);
    template<class T>
    class C { /*...*/ };
    #include "V3_common"
}

// file V3_0.h :
namespace V3_0 {
    #include "V3_common"
}

// file Popular.h :
namespace Popular {
    inline #include "V3_2.h"
    #include "V3_0.h"
    #include "V2_4_2.H"
}



// section 14.4.7 : nested namespaces
namespace X {
    // ... all my declarations ...
}

void h();

namespace X {
    void g();
    // ...
    namespace Y {
        void f();
        void ff();
        // ...
    }
}


void X::Y::ff()
{
    f();
    g();
    h();
}

void X::g()
{
    // error : no f() in X
    f();
    // ok
    Y::f();
}

void h()
{
    // error : no global f()
    f();
    // error : no global Y
    Y::f();
    // error : no f() in X
    X::f();
    // ok
    X::Y::f();
}



// section 14.4.8 : unnamed namespaces
#include "header.h"
namespace Mine {
    int a;
    void f() { /* ...  */ }
    int g() { /* ...  */ }
}


#include "header.h"
// equivalent
// namespace $$$ {
namespace {
    int a;
    void f() { /* ...  */ }
    int g() { /* ...  */ }
}

using namespace $$$;



// section 14.4.9 C headers
#include <stdio.h>

int main()
{
    printf("Hello, world!\n");
}


// cstdio
namespace std {
    // ...
    int printf(const char* ...);
}

// stdio.h :
#include <cstdio>

using namespace std;

// carefully avoids polluting the global namespace
#include <vector>
// error : no "vector" in global scope
vector v1;

// contains a "using namespace std;"
#include <stdio.h>
// oops : this now works
vector v2;


// stdio.h
#include <cstdio>
using std::printf;
// ...
