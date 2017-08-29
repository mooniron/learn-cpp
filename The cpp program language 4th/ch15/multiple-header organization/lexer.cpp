/**************************************************************
* Name     :  lexer.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年5月31日
**************************************************************/



/*
lexer.cpp
*/


#include "lexer.h"
#include "error.h"
#include <cctype>
// redundant in dc.h
#include <iostream>

// defaults to "read from cin"
Lexer::Token_stream ts;

Lexer::Token Lexer::Token_stream::get()
{
    /* ... */
}

Lexer::Token& Lexer::Token_stream::current()
{
    /* ... */
}

