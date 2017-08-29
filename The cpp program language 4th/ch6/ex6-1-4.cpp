/**************************************************************
* Name     :  ex6-1-4.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年4月25日
**************************************************************/



/*
example 6.2 : types
    6.2.3 : character types
*/


#include <iostream>

using namespace std;

void intval();
void digits();

int main()
{
    //intval();
    digits();

    // 255 is "all ones", 0xFF
    char c = 255;
    // i = 255 if c is unsigned, i = -1 if c is signed for two's complement
    int i = c;
    cout << "i = " << i << '\n';

    //
    signed char sc = -160;
    // uc = 96 = 256 - 160
    unsigned char uc = sc;
    // print 't'
    cout << "uc = " << int{uc} << '\n';
    // assume 8-bit chars
    char count[256];
    count[sc] = 12;
    // likely disaster out-of-range access, sc will be converted to unsigned integer implicitly
    ++count[sc];
    cout << "++count[sc] is " << int{count[sc]} << '\n';
    // OK
    ++count[uc];
    cout << "++count[sc] is " << int{count[sc]} << '\n';
    count[-160] = 0;
    ++count[-160];
    cout << "++count[sc] is " << int{count[sc]} << '\n';
    count[-1] = 12;
    ++count[-1];
    cout << "++count[-1] is " << int{count[255]} << '\n';
    // the type of 'ab' is int
    cout << 'ab' << '\n';

    // 6 chars : 'a' '\xa' 'h' '\12' '9' '\0'
    char v1[] = "a\xah\129";
    // 5 chars : 'a' '\xa' 'h' '\127' '\0'
    char v2[] = "a\xah\127";
    // 4 chars : 'a' '\xad' '\127' '\0'
    char v3[] = "a\xad\127";
    // 5 chars : 'a' '\xad' '\012' '7' '\0'
    char v4[] = "a\xad\0127";

    // wide char set, wchar_t
    L'ab';
    // unicode : U'\UFADEBEEF', u'\uDEAD', u'\xDEAD'
    // u'\uXXXX' == U'\U0000XXXX'

    return 0;
}   // end function


// print the integer value of input character c
void intval()
{
    for (char c; cin >> c; )
    {
        cout << "the value of '" << c << "' is " << int{c} << '\n';
    }   // end for
}   // end function intval


//
void digits()
{
    for (int i = 0; i != 10; ++i)
    {
        // '0' + i is an int
        cout << static_cast<char>('0' + i);
    }   // end for
    cout << '\n';
}

/*
void f(char c, signed char sc, unsigned char uc)
{
    // error : no pointer conversion
    char* pc = &uc;
    // error : no pointer conversion
    signed char* psc = pc;
    // error : no pointer conversion
    unsigned char* puc = pc;
    // error : no pointer conversion
    psc = puc;
}
*/


void g(char c, signed char sc, unsigned char uc)
{
    // implementation defined if plain chars are signed and have 8 bits
    c = 255;
    // OK
    c = sc;
    // implementation-defined if plain chars are signed and if uc's value is too large
    c = uc;
    // implementation defined if uc's value is too large
    sc = uc;
    // OK
    uc = sc;
    // implementation defined if plain chars are unsigned and if c's value is too large
    sc = c;
    // OK : conversion to unsigned
    uc = c;
}
