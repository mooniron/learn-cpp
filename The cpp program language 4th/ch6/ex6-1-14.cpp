/**************************************************************
* Name     :  ex6-1-14.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年4月25日
**************************************************************/



/*
example 6.5 : type aliases
*/


// pointer to character
using Pchar = char*;
// pointer to function taking a double and returning an int
using PF = int (*)(double);

// similar types can define the same name as a member alias
template<class T>
class vector {
    // every container has a value_type
    using value_type = T;
    // ...
};

template<<class T>
class list {
    // every container has a value_type
    using value_type = T;
    // ...
};

// p1 is a char*
Pchar p1 = nullptr;
// fine
char* p3 = p1;


// an older keyword : typedef
// equivalent to "using int32_t = int;"
typedef int int32_t;
// equivalent to "using int16_t = short;"
typedef short int16_t;
// equivalent to "using PtoF = void(*)(int)"
typedef void (*PtoF)(int);


// introduce a template alias
template<typename T>
using Vector = std::vector<T, My_allocator<T>>;

//
using Char = char;
// error : can not apply type specifiers, such us unsigned to an alias
using Uchar = unsigned Char;
// OK
using Uchar = unsigned char
