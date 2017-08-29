/**************************************************************
* Name     :  ex5-1-17.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年4月19日
**************************************************************/



/*
example 5.5 : Regular Expressions
*/


#include <iostream>
#include <regex>
#include <string>

//using std::regex;
using namespace std;


int main()
{
    // ZIP code pattern : XXddddd-dddd and variants, -dddd is optional
    regex pat (R"(\w{2}\s*\d{5}(-\d{4})?)");
    //cout << "pattern: " << pat << '\n';

    // search for a pattern in a stream
    int lineno = 0;
    // read into line buffer
    for (string line; getline(cin, line); )
    {
        ++lineno;
        // matched strings go here, a vector of submatches
        smatch matches;
        // search for pat in line
        if (regex_search(line, matches, pat))
        {
            cout << lineno << " : " << matches[0] << '\n';
        }
    }
}
