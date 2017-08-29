/**************************************************************
* Name     :  ex14-1-2.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年5月29日
**************************************************************/



/*
example 14.2 : namespaces
*/


namespace Graph_lib {
    class Shape { /* ... */ };
    class Line : public Shape { /* ... */ };
    // connected sequence of lines
    class Poly_line : public Shape { /* ... */ };
    // text label
    class Text : public Shape { /* ... */ };
    // compose
    Shape operator+(const Shape&, const Shape&);
    // open file of Shapes
    Graph_reader open(const char*);
}


class Glyph { /* ... */ };
class Line { /* ... */ };


namespace Text_lib {
    class Glyph { /* ... */ };
    // sequence of Glyphs
    class Word { /* ... */ };
    // sequence of Words
    class Line { /* ... */ };
    // sequence of Lines
    class Text { /* ... */ };
    // open text file
    File* open(const char*);
    // concatenate
    Word operator+(const Line&, const Line&);
}


// ln[i]
Glyph glyph(Line& ln, int i);

// ln[i]
Text_lib::Glyph glyph(Text_lib::Line& ln, int i);


// section 14.2.1 explicit qualification
namespace Parser {
    // declaration
    double expr(bool);
    double term(bool);
    double prim(bool);
}

// use
double val = Parser::expr();

// definition
double Parser::expr(bool b)
{
    // ...
}

// error : no logical() in Parser
void Parser::logical(bool);
// error : no trem() in Parser (misspelling)
double Parser::trem(bool);
// error : Parser::prim() takes a bool argument (wrong type)
double Parser::prim(int);


// global function
int f();

int g()
{
    // local variable : hides the global function
    int f;
    // error : we cna't call an int
    f();
    // ok : call the global function
    ::f();
}


// section 14.2.2 : using declarations
#include <string>
#include <vector>
#include <sstream>

// split s into its whitespace-separated substrings
std::vector<std::string> split(const std::string& s)
{
    std::vector<std::string> res;
    std::istringstream iss(s);
    for (std::string buf; iss >> buf; ) {
        res.push_back(buf);
    }
    return res;
}


// use "string" to mean "std::string"
using std::string;

std::vector<string> split(const string& s)
{
    std::vector<string> res;
    std::istringstream iss(s);
    for (string buf; iss >> buf; ) {
        res.push_back(buf);
    }
    return res;
}


namespace N {
    void f(int);
    void f(string);
}

void g()
{
    using N::f;
    // N::f(int)
    f(789);
    // N::f(string)
    f("Bruce");
}


// section 14.2.3 : using-directives
// make every name from std accessible
using namespace std;

// split s into its whitespace-separated substrings
vector<string> split(const string& s)
{
    vector<string> res;
    istringstream iss(s);
    for (string buf; iss >> buf; ) {
        res.push_back(buf);
    }
    return res;
}


using namespace Graph_lib;
using namespace Text_lib;

// Text_lib::Glyph
Glyph g1;
// Graph_lib::Shape
vector<Shape*> vs;
// error : ambigurous
Text txt;
// error : ambiguous
File* fp = open("my_precious_data");


// section 14.2.4 : argument-dependent lookup
namespace Chrono {
    class Date { /* ... */ }
    bool operator==(const Date&, const std::string&);
    std::string format(const Date&);
    // ...
}

void f(Chrono::Date d, int i)
{
    // Chrono::format(d)
    std::string s = format(d);
    // error : no format(int) in scope
    std::string t = format(i);
}


void f(Chrono::Date d, std::string s)
{
    if (d == s) {
        // ...
    }
    else if (d == "August 4, 1914") {
        // ...
    }
}


namespace N {
    struct S { int i };
    void f(S);
    void g(S);
    void h(int);
}

struct Base {
    void f(N::S);
};

struct D : Base {
    void mf();
    void g(N::S x)
    {
        // call Base::f()
        f(x);
        // call D::mf()
        mf(x);
        // error : no h(int) available
        h(1);
    }
};


namespace N {
    // N::f()
    template<class T>
    void f(T, int);
    class X { };
}

namespace N2 {
    N::X x;
    void f(N::X, unsigned);
    void g()
    {
        // calls N::f(X, int)
        f(x, 1);
    }
}



// section 14.2.5 namespaces are open
namespace A {
    // now A has member f()
    int f();
}

namespace A {
    // now A has two members, f() and g()
    int g();
}


