/**************************************************************
* Name     :  ex37-1-2.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年8月12日
**************************************************************/



/*
example 37.1: regular expressions
*/



void use()
{
    // input file
    ifstream in("file.txt");
    if (!in) {
        cerr << "no file\n";
    }

    // U.S. postal code pattern
    regex pat {R"(\w{2}\s*\d{5}(-\d{4})?)"};
    int lineno = 0;
    for (string line; getline(in, line); ) {
        ++lineno;
        // matched strings go here
        smatch matches;
        if (regex_search(line, matches, pat)) {
            // the complete match
            cout << lineno ": " << matches[0] << '\n';
        }
        if (1 < matches.size() && matches[1].matched) {
            // submatch
            cout << "\t: " << matches[1] << '\n';
        }
    }
}


// section 37.1.1: regular expression notation
bool is_identifier(const string& s)
{
    //regex pat {"[_[:alpha:]]\\w*"};
    regex pat {R"[_[:alpha:]]\w*"};
    return regex_match(s, pat);
}

// spaces, colons, and/or commas followed by a number
(\s|:|,)*(\d*)
// spaces, colons, and/or commas followed by a number
(?\s|:|,)*(\d*)

