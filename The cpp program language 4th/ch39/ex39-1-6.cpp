/**************************************************************
* Name     :  ex39-1-6.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年8月20日
**************************************************************/



/*
example 39.5: convenience interfaces
*/


// section 39.5.1: character classification
template<class C>
inline bool isspace(C c, const locale& loc)
{
    return use_facet<ctype<C>>(loc).is(space, c);
}

inline int isspace(int i)
{
    // almost
    return isspace(i, locale());
}


// section 39.5.2: character conversions
// section 39.5.3: string conversions
wstring_convert<codecvt_utf8<wchar_t>> myconv;
string s = myconv.to_bytes(L"Hello\n");
cout << s;

template<class Codecvt, class Wc = wchar_t, class Wa = std::allocator<Wc>, class Ba = std::allocator<char>>
class wstring_convert {
public:
    using byte_string = basic_string<char, char_traits<char>, Ba>
    using wide_string = basic_string<Wc, char_traits<Wc>, Wa>;
    using state_type = typename Codecvt::state_type;
    using int_type = typename wide_string::traits_type::int_type;
    // ...
};

void test()
{
    wstring_convert<codecvt_utf8_utf16<wchar_t>> converter;
    string s8 = u8"This is a UTF-8 string";
    wstring s16 = converter.from_bytes(s8);
    string s88 = converter.to_bytes(s16);
    if (s8 != s88) {
        cerr << "Insane!\n";
    }
}


// section 39.5.4: buffer conversions
template<class Codecvt, class C = wchar_t, class Tr = std::char_traits<C>>
class wbuffer_convert : public std::basic_streambuf<C, Tr> {
public:
    using state_type = typename Codecvt::state_type;
    // ...
};

