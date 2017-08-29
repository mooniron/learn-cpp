/**************************************************************
* Name     :  ex8-1-12.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年5月3日
**************************************************************/


/*
example 8.4 : enumerations
   8.4.1 : enum classes
*/


#include <iostream>

using namespace std;



enum class Color { red, green, blue };


enum class Traffic_light { red, green, blue };
enum class Warning { green, yellow, orange, red };

// error : no int -> Warning conversion
Warning a1 = 7;
// error : green not in scope
int a2 = green;
// error : no warning -> int conversion
int a3 = Warning::green;
// ok
Warning a4 = Warning::green;

void f(Traffic_light x)
{
    // error : 9 is not a Traffic_light
    if (x == 9) {
        /* ... */
    }
    // no red in scope
    if (x == red) {
        /* ... */
    }
    // error : x is not a Warning
    if (x == Warning::red) {
        /* ... */
    }
    // ok
    if (x == Traffic_light::red) {
        /* ... */
    }
}   // end function



// sizeof(Warning) == sizeof(int)
enum class Warning : int { green, yellow, orange, red };
// sizeof(Warning) == 1
enum class Warning : char { green, yellow, orange, red };

static_cast<int>(Warning::green) == 0
static_cast<int>(Warning::yellow) == 1
static_cast<int>(Warning::orange) == 2
static_cast<int>(Warning::red) == 3


void f2(Warning key)
{
    switch(key) {
        case Warning::green :
            // do something
            break;
        //case Warning::yellow :
            // do something
        //    break;
        case Warning::orange :
            // do something
            break;
        case Warning::red :
            // do something
            break;
    }   // end switch
}   // end function


enum class Printer_flags {
    acknowledge = 1,
    paper_empty = 2,
    busy = 4,
    out_of_black = 8,
    out_of_color = 16,
    // ...
};

constexpr Printer_flags operator|(Printer_flags a, Printer_flags b)
{
    return static_cast<Printer_flags>(static_cast<int>(a) | static_cast<int>(b));
}   // end function

constexpr Printer_flags operator&(Printer_flags a, Printer_flags b)
{
    return static_cast<Printer_flags>(static_cast<int>(a) & static_cast(b));
}   // end function


void try_to_print(Printer_flags x)
{
    if (x & Printer_flags::acknowledge) {
        // ...
    }
    else if (x & Printer_flags::busy) {
        // ...
    }
    // either we are out of black or out of color
    else if (x & (Printer_flags::out_of_black | Printer_flags::out_of_color)) {
        // ...
    }
    // ...
}   // end function


void g(Printer_flags x)
{
    switch (x) {
        case Printer_flags::acknowledge :
            // ...
            break;
        case Printer_flags::busy :
            // ...
            break;
        case Printer_flags::out_of_black :
            // ...
            break;
        case Printer_flags::out_of_color :
            //
        // we are out of black *and* out of color
        case Printer_flags::out_of_black & Printer_flags::out_of_color :
            // ...
            break;
    }   // end switch
}   // end function


// declaration
enum class Color_code : char;
// use of declaration
void foobar(Color_code* p);

// definition
enum class Color_code : char {
    red,
    yellow,
    green,
    blue
};


//
enum class Flag : char {
    x = 1, y = 2, z = 4, e = 8
};

// f0 gets the default value 0
Flag f0 {};
// type error : 5 is not of type Flag
Flag f1 = 5;
// error : no narrowing conversion to an enum class
Flag f2 = Flag {5};
// brute force
Flag f3 = static_cast<Flag>(5);
// error : 999 is not a char value (maybe not caught)
Flag f4 = static_cast<Flag>(999);

// i becomes 2
int i = static_cast<int>(Flag::y);
// c becomes 8
char c = static_cast<char>(Flag::e);




/*  enum range test  */
#include <iostream>

using namespace std;


enum Num : char {
    x = 1,
    y = 2,
    z = 4,
    e = 8
};

//enum class Numbits : char {
enum class Numbits : char {
    x = 1,
    y = 2,
    z = 4,
    e = 8
};

int main()
{
    // ok : (ouch!), the value of n1 is 43
    Num n1 = static_cast<Num>(299);
    // 43
    cout << n1 << '\n';
    // 43
    Numbits n2 = static_cast<Numbits>(299);
    // -43
    Numbits n3 = static_cast<Numbits>(-299);
    // 43
    cout << static_cast<int>(n2) << '\n';

    return 0;
}
