/**************************************************************
* Name     :  ex37-1-4.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年8月12日
**************************************************************/



/*
example 37.3: regular expression functions
*/



// section 37.3.1: regex_match()
int main()
{
    // input file
    ifstream in("table.txt");
    if (!in) {
        cerr << "no file\n";
    }

    // input buffer
    string line;
    int lineno = 0;

    // tab-separated words
    regex header {R"(^[\w]+(\t[\w]+)*$)"};
    // label followed by three tab-separated numbers
    regex row {R"(^([\w]+)(\t\d+)(\t\d+)(\t\d+)$)"};

    // check and discard the header line
    if (getline(in, line)) {
        smatch matches;
        if (!regex_match(line, matches, header)) {
            cerr << "no header\n";
        }
    }

    // running totals
    int boys = 0;
    int girls = 0;

    while (getline(in, line)) {
        ++lineno;
        // submatches go here
        smatch matches;

        if (!regex_match(line, matches, row)) {
            cerr << "bad line: " << lineno << '\n';
        }

        int curr_boy = stoi(matches[2]);
        int curr_girl = stoi(matches[3]);
        int curr_total = stoi(matches[4]);
        if (curr_boy + curr_girl != curr_total) {
            cerr << "bad row sum\n";
        }
        // last line
        if (matches[1] == "Total") {
            if (curr_boy != boys) {
                cerr << "boys do not addup\n";
            }
            if (curr_girl != girls) {
                cerr << "girls do not add up\n";
            }
            cout << "all is well";
            retgurn 0;
        }

        boys += curr_boy;
        girls += curr_girls;
    }

    cerr << "didn't find total line\n";
    return 1;
}


// section 37.3.2: regex_search()
regex pat {"[Ss]tro?u?v?p?stra?o?u?p?b?"};
smatch m;
for (strings; cin >> s; ) {
    if (regex_search(s, m, pat)) {
        if(m[0] != "stroustrup" && m[0] != "Stroustrup") {
            cout << "Found: " << m[0] << '\n';
        }
    }
}


// section 37.3.3: regex_replace()
void test1()
{
    string input {"x 1 y2 22 zaq 34567"};
    // word space number
    regex pat {R"(\w+)\s(\d+)"};
    string format {"{$1, $2}\n"};
    cout << regex_replace(input, pat, format);
    // elimate copying unmatched characters
    cout << regex_replace(input, pat, format, regex_constants::format_no_copy);
}

void test2()
{
    string input {"x 1 y2 22 zaq 34567"};
    // word space number
    regex pat {R"(\w+)\s(\d+)"};
    string format {"{$2: $1}\n"};
    // elimate copying unmatched characters
    cout << regex_replace(input, pat, format, regex_constants::format_no_copy);
}

