/**************************************************************
* Name     :  ex19-1-3.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年6月18日
**************************************************************/



/*
example 19.3 : a string class
*/

#include <iostream>
#include <algorithm>
#include <cstring>


// section 19.3.1 essential operations
class String {
public :
    // default constructor : x {""}
    String();
    // constructor from C-style string x {"Euler"}
    explicit String(const char* p);
    // copy constructor
    String(const String&);
    // copy assignment
    String& operator=(const String&);
    // move constructor
    String(String&& x);
    // move assignment
    String& operator=(String&& x);
    // destructor
    ~String()
    {
        if (short_max < sz) {
            delete[] ptr;
        }
    }
    // ...
};


// section 19.3.2 : access to characters
class String {
public :
    // ...
    // unchecked element access
    char& operator[](int n) { return ptr[n]; }
    char operator[](int n) const { return ptr[n]; }
    // range-checked element access
    char& at(int n)
    {
        check(n);
        return ptr[n];
    }
    char at(int n) const
    {
        check(n);
        return ptr[n];
    }
    // add c at end
    String& operator+=(char c);
    // C-style string access
    const char* c_str() { return ptr; }
    const char* c_str() const { return ptr; }
    // number of elements
    int size() const { return sz; }
    // elements plus available space
    int capacity() const
    {
        return (sz <= short_max) ? short_max : sz + space;
    }
    // ...
};


int hash(const String& s)
{
    int h {s[0]};
    for (int i {1}; i != s.size(); i++) {
        // unchecked access to s
        h ^= s[i] >> 1;
    }
    return h;
}

void print_in_order(const String& s, const vector<int>& index)
{
    for (auto x : index) {
        cout << s.at(x) << '\n';
    }
}


// section 19.3.3 : representation
/*
A simple string that implements the short string optimization;
size() == sz is the number of elements
if size() <= short_max, the characters are held in the String object itself;
otherwise the free store is used.
ptr points to the start of the character sequence. the character sequence is kept
zero-terminated : ptr[size()] == 0;
this allows us to use C library string functions and to easily return a C-style
string c_str();
To allow efficient addition of characters at end, String grows by doubling its allocation;
capacity() is the amount of space available for characters (excluding the terminating 0) :
sz + space
*/

class String {
public :
    // ...
private :
    static const int short_max = 15;
    // number of characters
    int sz;
    char* ptr;
    union {
        // unused allocated space
        int space;
        // leave space for terminating 0
        char ch[short_max + 1];
    };

    // range check
    void check(int n) const
    {
        if (n < 0 || sz <= n) {
            throw std::out_of_range("String::at()");
        }
    }
    // ancillary member functtions
    void copy_from(const String& x);
    void move_from(String& x);
};



// section 19.3.3.1 : ancillary functions
// expand into free store
char* expand(const char* ptr, int n)
{
    char* p = new char[n];
    strcpy(p, ptr);
    return p;
}

// make *this a copy of x
void String::copy_from(const String& x)
{
    if (x.sz <= short_max) {
        // copy *this
        memcpy(this, &x, sizeof(x));
        ptr = ch;
    }
    else {
        // copy the elements
        ptr = expand(x.ptr, x.sz + 1);
        sz = x.sz;
        space = 0;
    }
}

void String::move_from(String& x)
{
    if (x.sz <= short_max) {
        // copy *this
        memcpy(this, &x, sizeof(x));
        ptr = ch;
    }
    else {
        // grab the elements
        ptr = x.ptr;
        sz = x.sz;
        space = x.space;
        // x = ""
        x.ptr = x.ch;
        x.sz = 0;
        x.ch[0] = 0;
    }
}


// section 19.3.4 : member functions
// default constructor x {""}
String::String()
    : sz {0},
    // ptr points to elements, ch is an initial location
    ptr {ch}
{
    // terminating 0
    ch[0] = 0;
}

// C-style string constructor
String::String(const char* p)
    : sz {strlen(p)},
    ptr {(sz <= short_max) ? ch : new char[sz + 1]},
    space {0}
{
    // copy characters into ptr from p
    strcpy(ptr, p);
}

// copy constructor
String::String(const String& x)
{
    // copy representation from x
    copy_from(x);
}

// move constructor
String::String(String&& x)
{
    move_from(x);
}

// copy assignment
String& String::operator=(const String& x)
{
    // deal with self-assignment
    if (this == &x) {
        return *this;
    }
    char* p = (short_max < sz) ? ptr : 0;
    copy_from(x);
    delete[] p;
    return *this;
}

// move assignment
String& String::operator=(String&& x)
{
    // deal with self-assignment
    if (this == &x) {
        return *this;
    }
    // delete target
    if (short_max < sz) {
        delete[] ptr;
    }
    // does not throw
    move_from(x);
    return *this;
}

String& String::operator+=(char c)
{
    // expand to long string
    if (sz == short_max) {
        // double the allocation (+2 because of the terminating 0)
        int n = sz + sz + 2;
        ptr expand(ptr, n);
        space = n - sz - 2;
    }
    else if (short_max < sz) {
        if (space == 0) {
            // expand in free store
            // double the allocation
            int n = sz + sz + 2;
            char* p = expand(ptr, n);
            delete[] ptr;
            ptr = p;
            space = n - sz - 2;
        }
        else {
            --space;
        }
    // add c at end
    ptr[sz] = c;
    // increase size and set terminator
    ptr[++sz] = 0;
    return *this;
}


// section 19.3.5 : helper functions
ostream& operator<<(ostream& os, const String& s)
{
    return os << s.c_str();
}

istream& operator>>(istream& is, String& s)
{
    // clear the target string
    s = "";
    // skip whitespace
    is >> ws;
    char ch = ' ';
    while (is.get(ch) && !isspace(ch)) {
        s += ch;
    }
    return is;
}


bool operator==(const String& a, const String& b)
{
    if (a.size() != b.size()) {
        return false;
    }
    for (int i = 0; i != a.size(); ++i) {
        if (a[i] != b[i]) {
            return false;
        }
    }
    return true;
}

bool operator!=(const String& a, const String& b) {
    return !(a == b);
}

// C-string-style access
char* begin(String& x)
{
    return x.c_str();
}

char* end(String& x)
{
    return x.c_str() + x.size();
}

const char* begin(const String& x)
{
    return x.c_str();
}

const char* end(const String& x)
{
    return x.c_str() + x.size();
}


// cancatenation
String& operator+=(String& a, const String& b)
{
    for (auto x : b) {
        a += x;
    }
    return a;
}


// cancatenation
String operator+(const String& a, const String& b)
{
    String res {a};
    res += b;
    return res;
}


String s = "Njal ";
// concatenate : add to the end of s
s += "Gunnar";


String operator"" _s(const char* p, size_t)
{
    return String {p};
}


// C-style string
void f(const char*);
// our string
void f(const String&);

void g()
{
    // f(const char*)
    f("Madden's");
    // f(const String&)
    f("Christopher's"_s);
}S


// section 19.3.6 : using our string
int main()
{
    String s ("abcdefghij");
    cout << s << '\n';
    s += 'k';
    s += 'l';
    s += 'm';
    s += 'n';
    cout << s << '\n';
    String s2 = "Hell";
    s2 += " and high water";
    cout << s2 << '\n';

    String s3 = "qwerty";
    s3 = s3;
    String s4 = "the quick brown fox jumped over the lazy dog";
    s4 = s4;
    cout << s3 << " " << s4 << "\n";
    cout << s + ". " + s3 + String(". ") + "Horsefeathers\n";

    String buf;
    while (cin >> buf && buf != "quit") {
        cout << buf << " " << buf.size() << " " << buf.capacity() << '\n';
    }

    return 0;
}


