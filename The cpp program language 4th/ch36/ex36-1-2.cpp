/**************************************************************
* Name     :  ex36-1-2.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年8月11日
**************************************************************/



/*
example 36.1: introduction
example 36.2: character classification
*/



// section 36.2.1: classification functions
// a character, verbose and slower
if ('a' < ch && ch < 'z')
// a lowercase character
if (islower(ch))

// a lowercase character in Danish
// assuming "danish" is the name for a Danish locale
if (islower, danish)


// section 36.2.2: character traits
template<typename C>
struct char_traits { };

template<>
struct char_traits<char> {
    // char_traits operations should not throw exceptions
    using char_type = char;
    // type of integer value of character
    using int_type = int;
    // offset in stream
    using off_type = streamoff;
    // position in stream
    using pos_type = streampos;
    // multibyte stream state
    using state_type = mbstate_t;
    // ...
};

template<>
struct char_traits<char16_t>;
template<>
struct char_traits<char32_t>;
template<>
struct char_traits<wchar_t>;

