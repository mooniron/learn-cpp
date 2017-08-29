/**************************************************************
* Name     :  ex7-1-3.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年4月25日
**************************************************************/



/*
example 7.3 : arrays
*/


// an array of three floats : v[0], v[1], v[2]
float v[3];
// an array of 32 pointers to char a[0] .. a[31]
char* a[32];

void f()
{
    int aa[10];
    // assign to aa's 7th element
    aa[6] = 9;
    // undefined behavior
    int x = aa[99];
}

void f2(int n)
{
    // error : array size not a constant expression
    int v1[n];
    // OK : vector with n int elements
    vector<int> v2(n);
}

// 10 ints in static storage
int a1[10];
void f3()
{
    // 20 ints on the stack
    int a2[20];
    // 40 ints on the free store
    int* p = new int[40];
    // ...
}


/*  section 7.3.1 : array initializers  */
int v1[] = {1, 2, 3, 4};
char v2[] = {'a', 'b', 'c', 0};
// too many initializers
char v3[2] = {'a', 'b', 0};
// ok
char v4[3] = {'a', 'b', 0};
// too few elements, 0 is used for the rest
int v5[8] = {1, 2, 3, 4};
// error : can not copy an array (can not assign an int* to an array)
int v6[8] = v5;
// error : no array assignment
v6 = v5;


/*  section 7.3.2 : string literals  */
void fs()
{
    // error, but accepted in pre-c++11-standard code
    char* p = "Plato";
    // error : assignment to const
    p[4] = 'e';
}


void fs2()
{
    // p is an array of 5 char
    char p[] = "Zeno";
    // OK
    p[0] = 'R';
}


const char* error_message(int i)
{
    // ...
    return "range error";
}


const char* p = "Heraclitus";
const char* q = "Heraclitus";

void g()
{
    // the result is implementation-defined
    if (p == q)
    {
        cout << "one!\n";
        cout << "beep at end of message\a\n"
    }
    // ...
}

// the compiler will concatenate adjacent strings
char alpha[] = "abcdefghijklmnopqrstuvwxyz" "ABCDEFGHIJKLMNOPQRSTUVWXYZ"


/*  section 7.3.2.1 : raw string literals  */
// the pattern representing two words separated by a backslash
// I hope I've got that right
string s = "\\w\\\\w";
// I'm pretty sure I got that right
string sr = R"(\w\\w)";
// the string is "quoted string"
string s2 = R"("quoted string")";
// delimiter : R"***(...)***"
string sr2 = R"***("quoted string containing the usual terminator("))")***";
// a raw string literal can contain a newline
string counts {R"(1
22
333")"};
// equivalent to
string x1 {"1\n22\n333"};



/*  section 7.3.2.2 larger character sets  */
// const wchar_t type
L"love";

// implementation character set string
"folder\\file"
// implementation character raw set string
R"(folder\file)"
// UTF-8 string
u8"folder\\file"
// UTF-8 raw string
u8R"(folder\file)"
// UTF-16 string
u"folder\\file"
// UTF-16 raw string
uR"(folder\file)"
// UTF-32 string
U"folder\\file"
// UTF-32 raw string
UR"(folder\file)"
//
u8"The official vowels in Danish are : a, e, i, o, u, \u00E6, \u00F8, \u00E5 and y."
