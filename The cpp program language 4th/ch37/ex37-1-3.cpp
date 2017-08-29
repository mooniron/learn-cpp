/**************************************************************
* Name     :  ex37-1-3.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年8月12日
**************************************************************/



/*
example 37.2: regex
*/



template<class C, class traits = regex_traits<C>>
class basic_regex {
public:
    using value_type = C;
    using traits_type = traits;
    using string_type = typename traits::string_type;
    using flag_type = regex_constants::syntax_option_type;
    using locale_type = typename traits::locale_type;

    // not virtual; basic_regex is not meant to be used as a base class
    ~basic_regex();
    // ...
};

using regex = basic_regex<char>;

// no way of outputting the  pattern in pat1
regex pat1 {R"(\w+\d*)"};
string s {R"(\w+\d*)"};
regex pat2 {s};
// the pattern in pat2
cout << s << '\n';


// section 37.2.1: match results
template<class Bi>
class sub_match : public pair<Bi, Bi> {
public:
    using value_type = typename iterator_traits<Bi>::value_type;
    // ...
    // true if *this contains a match
    bool matched;
    // ...
};

regex pat ("<(.*?)>(.*?)</(.*?)>");

string s = "Always look for the <b> bright </b> sideof <b> death </b>";

if (regex_search(s, m, pat)) {
    if (m[1] == m[3]) {
        cout << "match\n";
    }
}

template<class Bi, class A = allocator<sub_match<Bi>>>
class match_results {
public:
    using value_type = sub_match<Bi>;
    using const_reference = const value_type&;
    // ...
    // not virtual
    ~match_results();
    // ...
};

// C-style string
using cmatch = match_results<const char*>;
// wide C-style string
using wcmatch = match_results<const wchar_t*>;
// string
using smatch = match_results<string::const_iterator>;
// wstring
using wsmatch = match_results<wstring::const_iterator>;

void test()
{
    regex pat ("(AAAA)(BBB)?");
    string s = "AAAA";
    smatch m;
    regex_search(s, m, pat);

    cout << boolalpha;
    // true: we found a match
    cout << m[0].matched << '\n';
    // true: there was a first sub_match
    cout << m[1].matched << '\n';
    // false: no second sub_match
    cout << m[2].matched << '\n';
    // false: there couldn't be a third sub_match for pat
    cout << m[3].matched << '\n';
}


// section 37.2.2: formatting

