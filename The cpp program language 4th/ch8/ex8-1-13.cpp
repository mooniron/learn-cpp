/**************************************************************
* Name     :  ex8-1-13.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年5月3日
**************************************************************/


/*
example 8.4 : enumerations
   8.4.2 : plain enums
*/


#include <iostream>

using namespace std;



enum Traffic_light { red, yellow, green };
// error : two definitions of yellow (to the same value)
// error : two definitions of red (to the different values)
enum Warning { green, yellow, orange, red };

// error : no int->Warning conversion
Warning a1 = 7;
// OK : green is in scope and converts to int
int a2 = green;
// OK : Warning->int conversion
int a3 = Warning::green;
// OK
Warning a4 = Warning::green;
//
//Warning a5 = green;


void f(Traffic_light x)
{
    // ok (but Traffic_light doesn't have a 9)
    if (x == 9) { /* ... */ }
    // error : two reds in scope
    if (x == red) { /* ... */ }
    // ok (ouch!)
    if (x == Warning::red) { /* ... */ }
    // ok
    if (x == Traffic_light::red) { /* ... */ }
}   // end function


// disambiguate the enumerators
enum Traffic_light {
    tl_red,
    tl_yellow,
    tl_green
};

// fire alert levels
enum Warning { green, yellow, orange, red };

void f(Traffic_light x)
{
    // ok (ouch!)
    if (x == red) { /* ... */ }
    // ok (ouch!)
    if (x == Warning::red) { /* ... */ }
    // error : red is not a Traffic_light value
    if (x == Traffic_light::red) { /* ... */ }
}


// underlying type is char
enum Traffic_light : char {
    tl_red, tl_yellow, tl_green
};

// declaration
enum Color_code : char;
// use of declaration
void foobar(Color_code *p);

// definition
enum Color_code : char {
    red, yellow, green, blue
};

// range 0 : 1 (0 : 2^k - 1), k = 1
enum E1 { dark, light};
// range 0 : 15, 0 : 2^k - 1, k = 4
enum E2 { a = 3, b = 9 };
// range : -1048576 : 1048575 == -2^k : 2^k - 1, k = 20
enum E3 { min = -10, max = 1000000 };


// range 0 : 15
enum Flag { x = 1, y = 2, z = 4, e = 8 };
// f0 gets the default value 0
Flag f0 {};
// type error : 5 is not of type Flag
Flag f1 = 5;
// error : no explicit conversion from int to Flag
Flag f2 = Flag {5};
// ok : 5 is within the range of Flag
Flag f3 = static_cast<Flag>(5);
// ok 12 is within the range of Flag
Flag f4 = static_cast<Flag>(z | e);
// undefined : 99 is not within the range of Flag
Flag f5 = static_cast<Flag>(99);


// unamed enums
enum {
    arrow_up = 1,
    arrow_down,
    arrow_sideways
};



/*  range test  */
#include <iostream>

using namespace std;


enum Num : char {
    x = 1,
    y = 2,
    z = 4,
    e = 8
};

enum Num2 {
    x2 = 1,
    y2 = 2,
    z2 = 4,
    e2 = 8
};

//enum class Numbits : char {
enum class Numbits : char {
    x = 1,
    y = 2,
    z = 4,
    e = 8
};

// default underlying type is int
enum class Numbits2{
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
    // 43
    cout << static_cast<int>(n2) << '\n';
    // -43
    Numbits n3 = static_cast<Numbits>(-299);
    // 43
    cout << static_cast<int>(n3) << '\n';

    // -43
    Numbits2 n4 = static_cast<Numbits2>(-299);
    // 43
    cout << static_cast<int>(n4) << '\n';

    Num2 n5 = static_cast<Num2>(299);
    cout << static_cast<int>(n5) << '\n';

    return 0;
}
