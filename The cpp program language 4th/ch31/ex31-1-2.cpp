/**************************************************************
* Name     :  ex31-1-2.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年7月27日
**************************************************************/



/*
example 31.1: introduction
example 31.2: container overview
*/



// section 31.2.1: container representation
// section 31.2.2: element requirements
// section 31.2.2.1 :comparisons

// case-insensitive string compare
class Nocase {
public:
    bool operator()(const string&, const string&) const;
};

// return true if x is lexicographically less than y, not taking case into account
bool Nocase::operator()(const string& x, const string& y) const
{
    auto p = x.begin();
    auto q = y.begin();
    while (p != x.end()  && q != y.end() && toupper(*p) == toupper(*q)) {
        ++p;
        ++q;
    }

    if (p == x.end()) {
        return q != y.end();
    }
    if (q == y.end()) {
        return false;
    }
    return toupper(*p) < toupper(*q);
}


struct Cstring_less {
    bool operator()(const char* p, const char* q) const
    {
        return strcmp(p, q) < 0;
    }
};

map<char*, int, Cstring_less> m;


// section 31.2.2.2: other relational operators
// not done where the user supplied a comparison
if (x == y)
// done where the user supplied a comparison cmp
if (!cmp(x, y) && !cmp(y, x))

