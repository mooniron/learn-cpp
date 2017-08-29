/**************************************************************
* Name     :  ex2-1-10.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年4月7日
**************************************************************/


/*
example 2.3.3 :
    enumeration
*/


#include <iostream>

using namespace std;

// strongly scoped enum Color
enum class Color {red, blue, green};
// less strongly typed plain enum
enum Colorl {red, blue, green};
// strongly scoped enum Traffic_light
enum class Traffic_light {green, yellow, red};

Color col = Color::red;
Traffic_light light = Traffic_light::red;

/*
Color x = red;  // error : which red?
Color y = Traffic_light::red;   // that red is not a Color
Color z = Color::red;   // ok
int i = Color::red;     // error: Color::red is not an int
Color c = 2;    // error : 2 is not a Color
*/

// prefix increment
// return a reference Traffic_light&, a enum number can not be a reference
Traffic_light& operator++(Traffic_light& t) {
    switch(t) {
        // error: invalid initialization of non-const reference of type 'Traffic_light&' from an rvalueue of type 'Traffic_light'
        //case Traffic_light::green : return Traffic_light::yellow;
        case Traffic_light::green : return t = Traffic_light::yellow;
        case Traffic_light::yellow : return t = Traffic_light::red;
        case Traffic_light::red : return t = Traffic_light::green;
        }   // end switch
    return t;
    }   // end function

// next becomes Traffic_light::green
// error : reference to 'next' is ambiguous, confusing from the standard library name.
Traffic_light next_light = ++light;

int main() {
    if (next_light == light) {
    //if (light == Traffic_light::green) {
        cout << "light == Traffic_light::green" << endl;
        }
    else {
        cout << "error" << endl;
        }

    /*  lvalue and rvalue block : lvalue has an address, and rvalue has no address. */
    // int foobar();    // a function return int value
    // int* ipf = &foobar();    // error : foobar() is a rvalue

    int x = 5;
    //int* ip = &x++;       // error : x++ is a rvalue, just a constant value of x, not x variable;
    int* ip = &++x;         // ok : ++x is a lvalue
    //int& rp = x++;        // error : x++ is a rvalue, just a constant value, has no address to refer.
    int& rp = ++x;          // ok : ++x is a lvalue
    cout << "x = " << x << endl;
    cout << "*ip = " << *ip << endl;
    cout << "rp = " << rp << endl;


    return 0;
    }   // end function main
