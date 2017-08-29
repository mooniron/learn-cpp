/**************************************************************
* Name     :  ex37-1-5.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年8月12日
**************************************************************/



/*
example 37.4: regular expression iterators
*/



// section 37.4.1: regex_iterator
template<class Bi, class C = typename iterator_traits<Bi>::value_type, class Tr = typename regex_traits<C>::type>
class regex_iterator {
public:
    using regex_type = basic_regex<C, Tr>;
    using value_type = match_results<Bi>;
    // ...
};

using cregex_iterator = regex_iterator<const char*>;
using wcregex_iterator = regex_iterator<const wchar_t*>;
using sregex_iterator = regex_iterator<string::const_iterator>;
using wsregex_iterator = regex_iterator<wstring::const_iterator>;


void test()
{
    string input = "as as; asd ++e^asdf asdfg";
    regex pat {R"(\s+(\w+))"};;
    for (sregex_iterator p(input.begin(), input.end(), pat); p != sregex_iteator{}; ++p) {
        cout << (*p)[1] << '\n';
    }
}


// section 37.4.2: regex_token_iterator
template<class Bi, class C = typename iterator_traits<Bi>::value_type, class Tr = typename regex_traits<C>::type>
class regex_token_iterator {
public:
    using regex_type = basic_regex<C, Tr>;
    using value_type = sub_match<Bi>;
    // ...
};

using cregex_token_iterator = regex_token_iterator<const char*>;
using wcregex_token_iterator = regex_token_iterator<const wchar_t*>;
using sregex_token_iterator = regex_token_iterator<string::const_token_iterator>;
using wsregex_token_iterator = regex_token_iterator<wstring::const_token_iterator>;


void test1()
{
    string input {"aa::bb cc::dd ee::ff"};
    regex pat {R"((\w+)([[:punct:]]+)(\w+)\s*)"};
    sregex_token_iterator end{};
    for (sregex_token_iterator p{input.begin(), input.end(), pat, {1, 3}}; p != end; ++p) {
        cout << *p << '\n';
    }
}

void test2()
{
    string s {"1,2 , 3 ,4,5, 6 7"};
    // use comma as token separator
    regex pat {R"(\s*,\s*)"};
    copy(sregex_token_iterator{s.begin(), s.end(), pat, -1}, sregex_token_iterator{},
        ostream_iterator<string>{cout, "\n"});
}

void test3()
{
    string s {"1,2 , 3 ,4,5, 6 7"};
    // use comma as token separator
    regex pat {R"(\s*,\s*)"};
    sregex_token_iterator end {};
    for (sregex_token_iterator p {s.begin(), s.end(), pat, -1}; p != end; ++p) {
        cout << *p << '\n';
    }
}

