/**************************************************************
* Name     :  ex38-1-5.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年8月14日
**************************************************************/



/*
example 38.4: I/O operations
*/


// section 38.4.1: input operations
template<typename C, typename Tr = char_traits<C>>
class basic_istream : virtual public basic_ios<C, Tr> {
public:
    using char_type = C;
    // ...
    explicit_istream(basic_streambuf<C, Tr>* sb);
    // release all resources
    virtual ~basic_istream();
    class sentry;
    // ...
protected:
    // move but no copy
    basic_istream(const basic_istream& rhs) = delete;
    // ...
};

template<typename C, typename Tr = char_traits<C>>
basic_ostream<C, Tr>&  basic_ostream<C, Tr>::operator<<(int i)
{
    sentry s {*this};
    if (!s) {
        // check whether all is well for output to start
        setstate(failbit);
        return *this;
    }
    // ... output the int ...
    return *this;
}


// section 38.4.1.1: formatted input
template<typename T1, typename T2>
void read_pair(T1& x, T2& y)
{
    char c1, c2, c3;
    cin >> c1 >> x >> c2 >> y >> c3;
    if (c1 != '{' || c2 != ',' || c3 != '}') {
        // unrecoverable input format error
        // set badbit
        cin.setstate(ios_base::badbit);
        throw runtime_error("bad read of pair");
    }
}

// section 38.4.1.2: unformatted input
// low-level, old style line read
void f()
{
    // MAX_WORD arrays of MAX_LINE char each
    char word[MAX_WORD][MAX_LINE];
    int i = 0;
    while (cin.getline(word[i++], MAX_LINE, '\n') && i < MAX_WORD) {
        // do nothing
        ;
    }
    // ...
}


// section 38.4.2: output operations
void print_bal(char ch)
{
    cout << "the value of '" << ch "' is " << int{ch} << '\n';
}

void test()
{
    print_val('a');
    print_bal('A');
}

template<typename T>
struct Named_val {
    string name;
    T value;
};

ostream& operator<<(ostream& os, const Named_val& nv)
{
    return os << '{' << nv.name << ':' << nv.value << '}';
}


// section 38.4.2.1: virtual output functions
class My_base {
public:
    // ...
    // write *this to s
    virtual ostream& put(ostream& s) const = 0;
};

ostream& operator<<(ostream& s, const My_base& r)
{
    // use the right put()
    return r.put(s);
}

class Sometype : public My_base {
public:
    // ...
    // the real output function
    ostream& put(ostream& s) const override;
};

// use << which calls the right put()
void f(const My_base& r, Sometype& s)
{
    cout << r << s;
}


// section 38.4.3: manipulators
cout << setprecision(4) << angle;

struct smanip {
    // function to be
    ios_base& (*f)(ios_base&, int);
    // value to be used
    int i;
    smanip(ios_base&(*ff)(ios_base&, int), int ii) : f{ff}, i{ii} { }
};

template<typename C, typename Tr>
basic_ostream<C, Tr>& operator<<(basic_ostream<C, Tr>& os, const smanip& m)
{
    // call m's f with m's stored value
    m.f(os, m.i);
    return os;
}

inline smanip setprecision(int n)
{
    auto h = [](ios_base& s, int x) -> ios_base& {s.precision(x); return s; };
    // make the function object
    return smanip(h, n);
}


// section 38.4.4: stream state
template<typename C, typename Tr = char_traits<C>>
class basic_ios : public ios_base {
public:
    using char_type = C;
    using int_type = typename Tr::int_type;
    // ...
};

class ios_base {
public:
    using fmtflags = /* implementation-defined type */;
    using iostate = /* ... */;
    // ...
    // exception class
    class failure;
    // initialize standard iostreams
    class Init;
};

template<typename T>
char* as_bytes(T&  i)
{
    // treat that memory as bytes
    return static_cast<char*>(&i);
}

void test()
{
    // stream mode is binary
    ifstream ifs("source", ios_base::binary);
    // stream mode is binary
    ofstream ofs("target", ios_base::binary);

    vector<intl> v;
    for (int i; ifs.read(as_bytes(i), sizeof(i)); ) {
        v.push_back(i);
    }
    // ... do something with v ...
    for (auto i : v) {
        // write bytes to binary file:
        ofs.write(as_bytes(i), sizeof(i));
    }
}

cout << "Please enter a number: ";
int num;
cin >> num;


enum event {
    erase_event,
    imbue_event,
    copyfmt_event
};

using event_callback = void (*)(event, ios_base&, int index);


// section 38.4.5: formatting
// section 38.4.5.1: formatting state
// use the default floating-point format
ios.unsetf(ios_base::floatfield);
// use hexadecimal floats
ios.setf(ios_base::fixed | ios_base::scientific, ios_base::floatfield);

cout.precision(8);
cout << 1234.56789 << ' ' << 1234.56789 << ' ' << 123456 << '\n';
cout.precision(4);
cout << 1234.56789 << ' ' << 1234.56789 << ' ' << 123456 << '\n';

cout.width(4);
// print 12 proceded by two spaces
cout << 12;
cout.width(4);
cout.fill('#');
// print ##ab
cout << "ab";
// "as many characters as needed"
cout.width(0);
cout.width(4);
// print abcdef
cout << "abcdef";
cout.width(4);
cout.fill('#');
// print ##12:13
cout << 12 << ':' << 13;


// section 38.4.5.2: standard manipulators
// print 1234, 4d2, 2322
cout << 1234 << ', ' hex << 1234 << ', ' << oct << 1234 << '\n';
constexpr double d = 123.456;
cout << d << "; " << scientific << d << "; " << hexfloat << d << "; " << fixed << d
    << "; " << defaultfloat << d << '\n';

// print (##12) (12)
cout << '(' << setw(4) << setfill('#') << 12 << ") (" << 12 << ")\n";

string input {"0 1 2 3 4"};
istringstream iss {input};
string s;
for (char ch; iss >> ch; ) {
    s += ch;
}
// print "01234"
cout << s;

istringstream iss2 {input};
iss >> noskipws;
for (char ch; iss2 >> ch; ) {
    s += ch;
}
// print "0 1 2 3 4"
cout << s;


// section 38.4.5.3: user-defined manipulators
// general format, precision 4
Form gen4 {4};
void f(double d)
{
    Form sci8;
    // scientific format, precision 8
    sci8.scientific().precision(8);
    cout << d << ' ' << gen4(d) << ' ' << sci8(d) << ' ' << d << '\n';
    // scientific format, precision 10
    Form sci {10, ios_base::scientific};
    cout << d << ' ' << gen4(d) << ' ' << sci(d) << ' ' << d << '\n';
}


// our formatting type
class Form;

// Form plus value
struct Bound_form {
    const Form& f;
    double val;
};

class Form {
    friend ostream& operator<<(ostream&, const Bound_form&);

    // precision
    int prc;
    // width 0 means "as wide as needed"
    int wdt;
    // general, scientific, or fixed
    int fmt;
    // ...
public:
    explicit Form(int p = 6, ios_base::fmtflags f = 0, int w = 0) : prc{p}, fmt{f}, wdt{w} { }
    // make a Bound_form for *this and d
    Bound_form Form::operator()(double d) const
    {
        return Bound_form{*this, d};
    }
    Form& scientific()
    {
        fmt = ios_base::scientific;
        return *this
    }
    Form& fixed()
    {
        fmt = ios_base::fixed;
        return *this;
    }
    Form& general()
    {
        fmt = 0;
        return *this;
    }
    Form& uppercase();
    Form& lowercase();
    Form& precision(int p)
    {
        prc = p;
        return *this;
    }
    // applies to all types
    Form& width(int w)
    {
        wdt = w;
        return *this;
    }
    Form& fill(char);
    // explicit plus
    Form& plus(bool b = true);
    // print trailing zeros
    Form& trailing_zeros(bool b = true);
};


ostream& operator<<(ostream& os, const Bound_form& bf)
{
    ostringstream s;
    s.precision(bf.f.prc);
    s.setf(bf.f.fmt, ios_base::floatfield);
    // compose string in s
    s << bf.val;
    // output s to os
    return os << s.str();
}

