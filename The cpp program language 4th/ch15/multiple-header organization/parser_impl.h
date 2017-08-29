/**************************************************************
* Name     :  parser_impl.h
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年5月31日
**************************************************************/



/*
parser_impl.h
*/

#include "parser.h"
#include "error.h"
#include "lexer.h"

using Error::error;
using namespace Lexer;

// interface for implementers
namespace Parser {
    double prim(bool get);
    double term(bool get);
    double expr(bool get);
}
