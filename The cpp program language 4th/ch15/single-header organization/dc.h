/**************************************************************
* Name     :  dc.h
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年5月31日
**************************************************************/



/*
dc.h : desk calculator header file
*/


#include <map>
#include <string>
#include <iostream>


namespace Parser {
    double expr(bool);
    double term(bool);
    double prim(bool);
}

namespace Lexer {
    enum class Kind : char {
        name, number, end, plus = '+', minus = '-', mul = '*', div = '/',
        print = ';', assign = '=', lp = '(', rp = ')'
    };

    struct Token {
        Kind kind;
        string string_value;
        double number_value;
    };

    class Token_stream {
    publick :
        Token_stream(istream& s) : ip {&s}, owns {false}, ct {Kind::end} { }
        Token_stream(istream* p) : ip {p}, owns {true}, ct {Kind::end} { }
        ~Token_stream() { close(); }
        // read and return next token
        Token get();
        // most recently read token
        Token& current();

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
        // current_token
        Token ct {Kind::endl};
    };

    extern Token_stream ts;
}


namespace Table {
    extern map<string, double> table;
}

namespace Error {
    extern int no_of_errors;
    double error(const string& s);
}

namespace Driver {
    void calculate();
}

