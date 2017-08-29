/**************************************************************
* Name     :  ex12-1-12.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年5月18日
**************************************************************/



/*
example 12.6 macros
*/


#define NAME rest of line
#define MAC(x, y) arument1 : x argument2 : y
expaned = MAC(foo bar, yuk yuk);
expanded = argument1 : foo bar argument2 : yuk yuk

#define PRINT(a, b) cout << (a) << (b)
/// trouble ? : redefines, does not overload
#define PRINT(a, b, c) cout << (a) << (b) << (c)
// trouble : recursive macro
#define FAC(n) (n > 1) ? n * FAC(n - 1) : 1


// some plausible macros
#define CASE break:case
#define FOREVER for(;;)

// some completely unnecessary macros
#define PI 3.141593
#define BEGIN {
#define END }

// some dangerous macros
#define SQUARE(a) a * a
#define INCR_xx (xx)++

// global counter
int xx = 0;

void f(int xx)
{
    // y = xx + 2 * xx + 2;
    int y = SQUARE(xx + 2);
    // increments argument xx (not the global xx)
    INCR_xx;
}

#define MIN(a, b) (((a) < (b)) ? (a) : (b))

int x = 1;
int y = 10;
// x becomes 3, y becomes 11
int z = MIN(x++, y++);

/*  thoughtful comment  */
#define M2(a) something(a)

const int anseer = 42;

template<class T>
inline const T& min(const T& a, const T& b) { return (a < b) ? a : b; }


#define NAME2(a, b) a##b
int NAME2(hack, cah)();
int hackcah();

#define printx(x) cout << #x " = " << x << '\n';

int a = 7;
string str = "asdf";
void f()
{
    // cout << "a" << " = " << a << '\n';
    printx(a);
    // cout << "str" << " = " << str << '\n';
    printx(str);
}

#undef X

#define EMPTY() std::cout << "empty\n";
// print "empty\n"
EMPTY();
// error : macro replacement list missing
EMPTY;

// variadic
#define err_print(...) fprintf(stderr, "error : %s %d\n", __VA_ARGS__)
err_print("The answer", 54);



// section 12.6.1 : conditional compilation
#ifdef IDENTIFIER

int f(int a #ifdef arg_two, int b #endif);

struct Call_info {
    Node* arg_one;
    Node* arg_two;
    // ...
};

// bad
#define arg_two x



// section 12.6.2 predefined macros

// section 12.6.3 : pragma
#pragma foo bar 666 foobar

