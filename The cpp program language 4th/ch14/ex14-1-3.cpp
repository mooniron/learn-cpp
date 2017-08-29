/**************************************************************
* Name     :  ex14-1-3.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年5月29日
**************************************************************/



/*
example 14.3 : modularization and interfaces
*/


// section 14.3.1 : namespaces as modules
namespace Parser {
    double expr(bool);
    double prim(bool get) { /* ... */ }
    double term(bool get) { /* ... */ }
    double expr(bool get) { /* ... */ }
}

namespace Lexer {
    enum class Kind : char { /* ... */ }
    class Token { /* ... */ };
    class Token_stream { /* ... */ };
    Token_stream ts;
}

namespace Table {
    map<string, double> table;
}

namespace Driver {
    void calculate() { /* ... */ }
}

int main() { /* ... */ }

namespace Error {
    int no_of_errors;
    double error(const string& s) { /* ... */ }
}


// interface separated from the implementation
namespace Parser {
    double expr(bool);
    double prim(bool);
    double term(bool);
    double expr(bool);
}

double Parser::prim(bool get) { /* ... */ }
double Parser;:term(bool get) { /* ... */ }
double Parser::expr(bool get) { /* ... */ }



// section 14.3.2 implementations
// handle primaries
double Parser::prim(bool get)
{
    if (get) {
        Lexer::ts.get();
    }

    switch (Lexer::ts.current().kind) {
        // floating-point constant
        case Lexer::Kind::number : {
            double v = Lexer::ts.current().number_value;
            Lexer::ts.get();
            return v;
        }
        case Lexer::Kind::name : {
            double& v = Table::table[Lexer::ts.current().string_value];
            // '=' seen : assignment
            if (Lexer::ts.get().kind == Lexer::Kind::assign) {
                v = expr(true);
            }
            return v;
        }
        // unary minus
        case Lexer::Kind::minus :
            return -prim(true);
        case Lexer::Kind::lp : {
            double e = expr(true);
            if (Lexer::ts.current().kind != Lexer::Kind::rp) {
                return Error::error("')' expected");
            }
            // eat ')'
            ts.get();
            return e;
        }
        default :
            return Error::error("primary expected");
    }
}


// saves eight occurrences of "Lexer::"
using Lexer::ts;
// saves six occurrences of "Lexer::"
using Lexer::Kind;
// saves two occurrences of "Error::"
using Error::error;
// saves one occurrence of "Table::"
using Table::table;

// handle primaries
double prim(bool get)
{
    if (get) {
        ts.get();
    }

    switch (ts.current().kind) {
        case Kind::number : {
            double v = ts.current().number_value;
            ts.get();
            return v;
        }
        case Kind::name : {
            double& v = table[ts.current().string_value];
            // '=' seen assignment
            if (ts.get().kind == Kind::assign) {
                v = expr(true);
            }
            return v;
        }
        // unary minus
        case Kind::minus :
            return -prim(true);
        case Kind::lp : {
            double e = expr(true);
            if (ts.current().kind != Kind::rp) {
                return error("')' expected");
            }
            // eat ')'
            ts.get();
            return e;
        }
        default :
            return error("primary expected");
    }
}


// saves fourteen occurrences of "Lexer::"
using namespace Lexer;
// saves two occurrences of "Error::"
using namespace Error;
// saves one occurrence of "Table::"
using namespace Table;

// handle primaries
double prim(bool get)
{
    // as before
}



// section 14.3.3 interfaces and implementations
// user interface
namespace Parser {
    double expr(bool);
}

// implementer interface
namespace Parser {
    double prim(bool);
    double term(bool);
    double expr(bool);
    // use all facilities offerd by lexer
    using namespace Lexer;
    using Error::error;
    using Table::table;
}


// user interface
namespace Parser {
    double expr(bool);
}

namespace Parser_impl {
    using namespace Parser;
    double prim(bool);
    double term(bool);
    double expr(bool);

    // use all facilities offered by Lexer
    using namespace Lexer;
    using Error::error;
    using Table::table;
}


