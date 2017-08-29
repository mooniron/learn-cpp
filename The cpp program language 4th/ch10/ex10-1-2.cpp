/**************************************************************
* Name     :  ex10-1-2.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年5月6日
**************************************************************/



/*
example 10.2 : a desk calculator

    the calculator consists of four main parts : a parser, an input function, a symbol table and
a driver.

example 10.2.1 : the parser
    program :
        // end is end-of-input
        end
        expr_list end

    expr_list :
        // print is newline or semicolon
        expression print
        expression print expr_list

    expression :
        expression + term
        expression - term
        term

    term :
        term / primary
        term * primary
        primary

    primary :
        // number is a floating-point literal
        number
        // name is an identifier
        name
        - primary
        ( expression )

the main algorithms is recursive descent.
*/


// I/O
#include <iostream>
// strings
#include <string>
// map
#include <map>
// isalpha(), etc
#include <cctype>
#include <sstream>
#include <vector>

using namespace std;
map<string, double> table;

// token
enum class Kind : char {
    name, number, end,
    plus = '+', minus = '-', mul = '*', div = '/',
    print = ';', assign = '=', lp = '(', rp = ')'
};

struct Token {
    Kind kind;
    string string_value;
    double number_value;
};

class Token_stream {
public :
    Token_stream(istream& s) : ip {&s}, owns {false} { }
    Token_stream(istream* p) : ip {p}, owns {true} { }
    ~Token_stream() { close(); }

    // read and return next token
    Token get();
    // most recently read token
    //const Token& current();
    Token& current() { return ct; };

    void set_input(istream& s)
    {
        close();
        ip = &s;
        owns = false;
    }
    void set_input(istream* p)
    {
        close();
        ip = p;
        owns = true;
    }

private :
    void close() { if (owns) delete ip; }
    // pointer to an input stream
    istream* ip;
    // does the Token_stream own the istream?
    bool owns;
    // current token
    Token ct {Kind::end};
};



double error(const string&);

// type-oriented, elegant code, but not good use
Token Token_stream::get()
{
    char ch;
    // skip whitespace except '\n'
    do {
        if (!ip->get(ch)) {
            return ct = {Kind::end};
        }
    } while (ch != '\n' && isspace(ch));

    switch (ch) {
        case ';' :
        case '\n' :
            return ct = {Kind::print};
        case '*' :
        case '/' :
        case '+' :
        case '-' :
        case '(' :
        case ')' :
        case '=' :
            return ct = {static_cast<Kind>(ch)};
        // digit
        case '0' : case '1' : case '2' : case '3' : case '4' : \
        case '5' : case '6' : case '7' : case '8' : case '9' : case '.' :
            // put the first digit (or .) back into the input stream
            ip->putback(ch);
            // read the number into ct
            *ip >> ct.number_value;
            ct.kind = Kind::number;
            return ct;
        // name, name = , or error
        default :
            if (isalpha(ch)) {
                ct.string_value = ch;
                while (ip->get(ch) && isalnum(ch)) {
                    // append ch to end of string_value
                    ct.string_value += ch;
                }
                ip->putback(ch);
                return ct = {Kind::name};
            }
            error("bad token");
            return ct = {Kind::print};
    }
}


// error handle
int no_of_errors;

double error(const string& s)
{
    no_of_errors++;
    cerr << "error : " << s << '\n';
    return 1;
}


// use input from cin
Token_stream ts {cin};

double term(bool);

// parser functions block
// expr() : handle add and subtract
double expr(bool get)
{
    double left = term(get);
    // forever
    for ( ; ; ) {
        switch (ts.current().kind) {
            case Kind::plus :
                left += term(true);
                break;
            case Kind::minus :
                left -= term(true);
                break;
            default :
                return left;
        }
    }
}


double prim(bool);

// term() : multiply and divide
double term(bool get)
{
    double left = prim(get);

    for ( ; ; ) {
        switch (ts.current().kind) {
            case Kind::mul :
                left *= prim(true);
                break;
            case Kind::div :
                if (auto d = prim(true)) {
                    left /= d;
                    break;
                }
                return error("divide by 0");
            default :
                return left;
        }
    }
}


// handle primaries
double prim(bool get)
{
    if (get) {
        // read next token
        ts.get();
    }

    switch (ts.current().kind) {
        // floating-point constant
        case Kind::number : {
            double v = ts.current().number_value;
            ts.get();
            return v;
        }
        case Kind::name : {
            // find the corresponding
            double& v = table[ts.current().string_value];
            if (ts.get().kind == Kind::assign) {
                // '=' seen : assignment
                v = expr(true);
            }
            return v;
        }
        case Kind::minus :
            return -prim(true);
        case Kind::lp : {
            auto e = expr(true);
            if (ts.current().kind != Kind::rp) {
                return error("'}' expected");
            }
            // eat ')'
            ts.get();
            return e;
        }
        default :
            return error("primary expected");
    }
}


//
void calculate()
{
    for ( ; ; ) {
        ts.get();
        if (ts.current().kind == Kind::end) {
            break;
        }
        if (ts.current().kind == Kind::print) {
            continue;
        }
        cout << expr(false) << '\n';
    }
}


vector<string> arguments(int, char*[]);

int main(int argc, char* argv[])
{
    switch (argc) {
        /// read from standard input
        case 1 :
            break;
        // read from argument string
        case 2 :
            ts.set_input(new istringstream {argv[1]});
            break;
        default :
            error("too many arguments");
            return 1;
    }

    // insert predefined names
    table["pi"] = 3.1415926535897932385;
    table["e"] = 2.7182818284590452354;
    calculate();

    return no_of_errors;
}

// char* argv[argc + 1]; argv[argc] == 0 == nullptr;
vector<string> arguments(int argc, char* argv[])
{
    vector<string> res;
    for (int i = 0; i != argc; ++i) {
        res.push_back(argv[i]);
    }
    return res;
}
