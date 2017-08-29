/**************************************************************
* Name     :  ex37-1-6.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年8月12日
**************************************************************/



/*
example 37.5: regex_traits
*/



template<class C>
struct regex_traits {
public:
    using char_type = C;
    using string_type = basic_string<char_type>;
    using locale_type = locale;
    using char_class_type = /* implementation defined bitmask type */;
    // ...
};

