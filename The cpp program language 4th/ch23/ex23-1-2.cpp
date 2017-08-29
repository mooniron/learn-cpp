/**************************************************************
* Name     :  ex23-1-2.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年7月12日
**************************************************************/



/*
example 23.2 : a simple sring template
*/


template<typename C>
class String {
public :
    String();
    explicit String(const C*);
    String(const String&);
    String operator=(const String&);
    // ...
    // unchecked element access
    C& operator[](int n) { return ptr[n]; }
    // add c at end
    String& operator+=(C c);
private :
    // for the short string optimization
    static const int short_max = 15;
    int sz;
    // ptr points to sz Cs
    C* ptr;
};


String<char> cs;
String<unsigned char> us;
String<wchar_t> ws;
// Japanese character
struct Jchar { /* ... */ };
String<Jchar> js;


// count the occurrences of each word on input
int main()
{
    map<String<char>, int> m;
    for (String<char> buf; cin >> buf; ) {
        ++m[buf];
    }
    // ... write out result ...
}

// Japanese version
// count the occurrences of each word on input
int main()
{
    map<String<Jchar>, int> m;
    for (String<Jchar> buf; cin >> buf; ) {
        ++m[buf];
    }
    // ... write out result ...
}

using string = std::basic_string<char>;

// count the occurrences of each word on input
int main()
{
    map<string<char>, int> m;
    for (string<char> buf; cin >> buf; ) {
        ++m[buf];
    }
    // ... write out result ...
}


// section 23.2.1 : defining a template
// default constructor
template<typename C>
String<C>::String()
    : sz {0}, ptr {ch}
{
    // terminating 0 of the appropriate character type
    ch[0] = {};
}

template<typename C>
String& String<C>::operator+=(C c)
{
    // ... add c to the end of this string ...
    return *this
}


template<typename T>
class String { /* ... */ };
// error : double definition
class String { /* ... */ };


// section 23.2.2 : template instantiation
String<char> cs;

void f()
{
    String<Jchar> js;
    cs = "It's the implementation's job to figure out what code needs to be generated";
}

