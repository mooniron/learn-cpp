/**************************************************************
* Name     :  ex39-1-5.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年8月20日
**************************************************************/



/*
example 39.4: standard facets
*/


// sort using character comparison from "da_DK"
// read the Danish  locale (including all of its facets) once
locale dk {"da_DK"};
// then use the dk locale and its facets as needed
void f(vector<string>& v, const locale& loc)
{
    const collate<char>& col {use_facet<collate<char>>(dk)};
    const ctype<char>& ctyp {use_facdet<ctype<char>>(dk)};
    // use Danish string comparison
    locale dk1 {loc, &col};
    // use Danish character classification and string comparison
    locale dk2 {dk1, &ctyp};
    sort(v.begin(), v.end(), dk2);
    // ...
}

// Danish letters, American numbers
locale dk_us(locale::classic(), dk, collate|ctype);


// section 39.4.1: string comparison
template<class C>
class collate : public locale::facet {
public:
    using  char_type = C;
    using string_type = basic_string<C>;
    explicit collate(size_t = 0);
    int compare(const C* b, const C* e, const C2* b2, const C* e2) const
    {
        return do_compare(b, e, b2, e2);
    }
    long hash(const C* b, const C* e) const
    {
        return do_hash(b, e);
    }
    string_type transform(const C* b, const C*  e) const
    {
        return do_transform(b, e);
    }

    // facet identifier object
    static locale::id id;
protected:
    // note: protected destructor
    ~collate();
    virtual int do_compare(const C* b, const C* e, const C* b2, const C* e2) const;
    virtual string_type do_transform(const C* b, const C* e) const;
    virtual long do_hash(const C* b, const C* e) const;
};


cf.compare(cf.transform(s), cf.transform(s2)) == cf.compare(s, s2)

void f(const string& s1, const string& s2, const collate<char>& cmp)
{
    // because compare() operates on char[]s
    const char* cs1 {s1.data()};
    const char* cs2 {s2.data()};
    switch(cmp.compare(cs1, cs1+s1.size(), cs2, cs2+s2.size())) {
        case 0:
            // identical strings according to cmp
            // ...
            break
        case 1:
            // s1 > s2
            // ...
            break;
        case -1:
            // s1 < s2
            break;
    }
}

void f(const string& s1, const string& s2, const string& name)
{
    // compare using implementation's character set values
    bool b {s1 == s2};
    // get start of data
    const char* s1b {s1.data()};
    // get end of data
    const char* s1e {s1.data() + s1.size()};
    const char* s2b {s2.data()};
    const char* s2e {s2.data() + s2.size()};

    using Col = collate<char>;
    // from the current global locale
    const Col& global {use_facet<Col>(locale{})};
    int i0 {global.compare(s1b,  s1e, s2b, s2e)};
    // from my preferred locale
    const Col& my_coll {use_facet<Col>(locale{""})};
    int i1 {my_coll.compare(s1b, s1e, s2b, s2e)};
    // from a named locale
    const Col& n_coll {use_facet<Col>(locale{name})};
    int i2 {n_coll.compare(s1b, s1e, s2b, s2e)};
}

void f(const string& s1, const string& s2, const string& name)
{
    // compare using the current global locale
    int i0  = locale{}(s1, s2);
    // compare using my preferred locale
    int i1 = locale{""}(s1, s2);
    // compare using the named locale
    int i2 = locale{name}(s1, s2);
    // ...
}


// section 39.4.1.1: named collate
template<class C>
class collate_byname : public collate<C> {
public:
    typedef basic_string<C> string_type;
    // construct from named locale
    explicit collate_byname(const char*, size_t r = 0);
    explicitcollate_byname(const string&, size_t r = 0);
protected:
    // note: protected destructed
    ~collate_byname();
    int do_compare(const C* b, const C* e, const C* b2, const C* e2) const override;
    string_type do_transform(const C* b, const C* e) const override;
    lont do_hash(const C* b, const C* e) const override;
};


// section 39.4.2: numeric formatting
// section 39.4.2.1: numeric punctuation
class My_punc : public numpunct<char> {
public:
    explicit My_punct(size_t r = 0) : numpunct<char>(r) { }
protected:
    // comma
    char do_decimal_point() const override { return ','; }
    // underscore
    char do_thousands_sep() const override { return '_'; }
    // 3-digit groups
    string do_grouping() const override { return "\003"; }
};

void f()
{
    cout << "style A: " << 12345678 << " *** " << 1234567.8
        << " *** " << fixed << 1234567.8 << '\n';
    // reset floating format
    cout << defaultfloat;
    locale loc(locale(), new My_punct);
    cout.imbue(loc);
    cout << "style B: " << 12345678 << " *** " << 1234567.8
        << " *** " << fixed << 1234567.8 << '\n';
}

template<class C>
class numpunct_byname : public numpunct<C> {
    // ...
};


// section 39.4.2.2: numeric output
template<class C>
class String_numput : public num_put<C, typename basic_string<C>::iterator> {
public:
    String_numput() : num_put<C, typename basic_string<C>::iterator>{1} { }
};

// format i into s starting at pos
void f(int i, string& s, int pos)
{
    String_numput<char> f;
    // format i into s: use cout's formating rules
    f.put(s.begin()+pos, cout, ' ', i);
}

void test(iostream& io)
{
    locale loc = io.getloc();
    wchar_t wc = use_facet<ctype<char>>(loc).widen(c);
    // default
    string s = use_facet<numput<char>>(loc).decimal_point();
    // default: "false"
    string false_name = use_facet<numput<char>>(loc).falsename();
}

template<class C, class Tr>
basic_ostream<C< Tr>&  basic_ostream<C, Tr>::operator<<(double d)
{
    sentry guard(*this);
    if (!guard) {
        return *this;
    }

    try {
        if (use_facet<num_put<C, Tr>>(getloc()).put(*this, *this, this->fill(), d).failed()) {
            setstate(badbit);
        }
    }
    catch (...) {
        handle_ioexception(*this);
    }

    return *this;
}

// called from catch-clause
template<typename C, class Tr>
void handle_ioexception(basic_ostream<C, Tr>& s)
{
    if (s.exceptions() & ios_base::badbit) {
        try {
            // might throw basic_ios::failure
            s.setstate(ios_base::badbit);
        }
        catch(...) {
            // ... do nothing ...
        }
        // rethrow
        throw;
    }
    s.setstate(ios_base::badbit);
}


// section 39.4.2.3: numeric input
template<class C, class Tr>
basic_istream<C< Tr>&  basic_istream<C, Tr>::operator>>(double d)
{
    sentry guard(*this);
    if (!guard) {
        return *this;
    }

    // good
    iostate state = 0;
    istreambuf_iterator<C, Tr> eos;

    try {
        double dd;
        use_facet<num_get<C, Tr>>(getloc()).get(*this, eos, *this, state, dd);
        if (state == 0 || state == eofbit){
            d = dd;
        }
        setstate(state);
    }
    catch (...) {
        handle_ioexception(*this);
    }

    return *this;
}

void f()
{
    cout << "style A: "
    int i1;
    double d1;
    cin >> i1 >> d1;
    // reading using standard format "12345678"

    locale loc(locale::classic(), new My_punct);
    cin.imbue(loc);
    cout << "style B: "
    int i2;
    double d2;
    // read using the "12_345_678" format
    cin >> i2 >> d2;
}


// section 39.4.3: money formatting
// simple type to hold a monetary amount
struct Money {
    // for currencies that have suffered inflation
    using Value = long long;
    Value amount;
};

void f(long int i)
{
    cout << "value= " << i << " amount= " << Money{i} << '\n';
}


// section 39.4.3.1: money punnctuation
class money_base {
public:
    // parts of value layout
    enum part {none, space, symbol, sign, value};
    // layout specification
    struct pattern { char field[4]; };
};

template<class C, bool International = false>
class moneypunct : public locale::facet, public money_base {
public:
    using char_type = C;
    using string_type = basic_string<C>;
    // ...
};

template<class C, bool Intl = false>
class moneypunct_byname : public moneypunct<C, Intl> {
    // ...
};

class My_money_io : public moneypunct<char, true> {
public:
    explicit My_money_io(size_t r = 0) : moneypunct<char, true>{r} { }
    char_type do_decimal_point() const {return '.'; }
    char_type do_thousands_sep() const { return ','; }
    string do_grouping() const { return "\003\003\003"; }
    string_type do_curr_symbol() const { return "USD "; }
    string_type do_positive_sign() const { return ""; }
    string_type do_negative_sign() const { return "()"; }
    // two digits after decimal point
    int do_frac_digits() const { return 2; }
    pattern do_pos_format() const { return pat; }
    pattern do_neg_format() const { return pat; }
private:
    static const pattern pat;
};

const pattern My_money_io::pat { sign, symbol, value, none };


// section 39.4.3.2: money output
ostream& operator<<(ostream& s, Money m)
{
    ostream::sentry guard(s);
    if (!guard) {
        return s;
    }

    try {
        const money_put<char>& f = use_facet<money_put<char>>(s.getloc());
        if (m == static_cast<long long>(m)) {
            if (f.put(s, true, s, s.fill(), m).failed()) {
                s.setstate(ios_base::badbit);
            }
        }
        else {
            ostringstream v;
            // convert to string representation
            // convert to string representation
            v << m;
            if (f.put(s, true, s, s.fill(), v.str()).failed()) {
                s.setstate(ios_base::badbit);
            }
    }
    catch(...) {
        handle_ioexception(s);
    }
    return s;
}


// section 39.4.3.3: money input
int main()
{
    Money m;
    while (cin >> m) {
        cout << m << '\n';
    }
}

istream& operator>>(istream& s, Money& m)
{
    istream::sentry guard(s);
    if (guard)
    try {
        ios_base::iostate state = 0;
        istreambuf_iterator<char> eos;
        string str;
        use_facet<money_get<char>>(s.getloc()).get(s, eos, true, state, str);
        if (state == 0 || state == ios_base::eofbit) {
            long long i = stoll(str);
            if (errno == ERANGE) {
                state |= ios_base::failbit;
            }
            else {
                m = i;
            }
        }
        s.setstate(state);
    }
    catch (...) {
        handle_ioexception(s);
    }
    return s;
}


// section 39.4.4: date and time formatting
// section 39.4.4.1: time_put
// section 39.4.4.2: time_get
class time_base {
public:
    enum dateorder {
        no_order,   // meaning mdy
        dmy,    // meaning %d%m%y
        mdy,
        ymd,
        ydm
    };
};

template<class C, class In = istreambuf_iterator<C>>
class time_get : public locale::facet, public time_base {
public:
    using char_type = C;
    using iter_type = In;
    // ...
};

class Date {
public:
    explicit Date(int d = {}, Month m = {}, int year = {});
    // ...
    string to_string(const locale& = locale()) const;
};

istream& operator>>(istream& is, Date& d);
ostream& operator<<(ostream& os, Date d);

string Date::to_string(const locale& loc) const
{
    ostringstream os;
    os.imbue(loc);
    return os << *this;
}

ostream& operator<<(ostream& os, Date d)
{
    return os << d.to_string(os.getloc());
}

istream& operator>>(istream& is, Date& d)
{
    if (istream::sentry guard{is}) {
        ios_base::iostate err = goodbit;
    }
    struct tm t;
    use_facet<time_get<char>>(is.getloc()).get_date(is, 0, is, err, &t) {
        if (!err) {
            Month m = static_cast<Month>(t.tm_mon+1);
            d = Date(t, tm_day, m, t.tm_year+1900);
        }
        is.setstate(err);
    }
    return is;
}


// section 39.4.5: character classification
class ctype_base {
public:
    enum mask {
        space = 1, print = 1 << 1, cntrl = 1 << 2, upper = 1 << 3, lower = 1 << 4;,
        alpha = 1 << 5, digit = 1 << 6, punct = 1 << 7, xdigit = 1 << 8, blank = 1 << 9;
        alnum = alpha | digit, graph = alnum|punct
    };
};

template<class C>
class ctype : public locale::facet, public ctype_base {
public:
    using char_type = C;
    // ...
};

table['P'] == upper|alpha
table['a'] == lower|alpha|xdigit
table['1'] == digit|xdigit
table[' '] == space|blank

int count_spaces(const string& s, const locale& loc)
{
    const ctype<char>& ct = use_facet<ctype<char>>(loc);
    int i = 0;

    for (auto p = s.begin(); p != s.end(); ++p) {
        if (ct.is(ctype_base::space, *p)) {
            ++i;
        }
    }
    return i;
}

// is c whitespace or punctuation in ct?
ct.is(ctype_base::space | ctypebase::punct, c);

template<class C>
const C* ctype<C>::do_scan_is(mask m, const C* b, const C* e)
{
    while (b != e && !is(m, *b)) {
        ++b;
    }
    return b;
}

template<class C>
const C* ctype<C>::to_upper(C* b, const C* e)
{
    for ( ; b != e; ++b) {
        *b = toupper(*b);
    }
    return e;
}

wcout << use_facet<ctype<wchar_t>>(wcout.getloc()).widen('e');
char EBCDIC_e = use_facet<ctype<char>>(ebcdic).widen('e');
// not guaranted
c == narrow(widen(c), 0);


// section 39.4.6: character code conversion
class codecvt_base {
public:
    enum result { ok, partial, error, noconv };
};

template<class In, class Ex, class SS>
class codecvt : public locale::facet, public codecvt_base {
public:
    using intern_type = In;
    using extern_type = Ex;
    using state_type = SS;
    // ...
};

class JIState { /* ... */ };
// standard char to wide char
p = new codecvt<wchar_t, char, mmbstate_t>;
// JIS to wide char
q = new codecvt<wchar_t, char, JISstate>;

class JIScvt : public codecvt<wchar_t, char, mbstate_t> {
    // ...
};


// convert to uppercase
class Cvt_to_upper : public codecvt<char, char, mbstate_t> {
public:
    explicit Cvt_to_upper(size_t r = 0) : codecvt(r) { }
protected:
    // read external representation write internal representation
    result do_in(State& s, const char* from, const char* from_end, const char*& from_next, char* to, char* to_end, char*& to_next) const override;
    // ...
};

// ...
// trivial test
int main()
{
    locale ulocale(locale(), new Cvt_to_upper);
    cin.imbue(ulocale);
    for (char ch; cin >> ch; ) {
        cout << ch;
    }
}


// section 39.4.7: messages
class message_base {
public:
    // catalog identifier type
    using catelog = /* implementation defined integer type */;
};

template<class C>
class messages : public locale::facet, public message_ base {
public:
    using char_type = C;
    using string_type = basic_string<C>
    // ...
};

struct Set {
    vector<string> msgs;
};

struct Cat {
    vector<Set> sets;
};

class My_messages : public messages<char> {
    vector<Cat>&  catalogs;
public:
    explicit My_messages(size_t = 0) : catalogs{*new vector<Cat>} { }
    // open catalog s
    catelog do_open(const string& s, const locale& loc) const;
    // get message (s, m) in cat
    string do_get(catalog cat, int s, int m, const string&) const;
    void do_close(catelog cat) const
    {
        if (catalogs.size() <= cat) {
            catalogs.erase(catalogs.begin() + cat);
        }
    }
    ~My_messages() { delete &catalogs; }
};

string My_messages::do_get(catalog cat, int set, int id, const string& def) const
{
    if (catalogs.size() <= cat) {
        return def;
    }
    Cat& c = catalogs[cat];
    if (c.sets.size() <= set) {
        return def;
    }
    Set& s = c.sets[set];
    if (s.msgs.size() <= id) {
        return def;
    }
    return s.msgs[id];
}

messages<char>::catalog My_messages::do_open(const string& n, const locale& loc) const
{
    string nn = n + locale().name();
    ifstream f(nn.c_str());
    if (!f) {
        return -1;
    }
    // make in-care catalog
    catalogs.push_back(Cat{});
    Cat& c = cagtalogs.back();
    // read Set
    for (string s; f >> s && s == "<<<") {
        c.sets.push_back(Set{});
        Set ss = c.gets.back();
        // read message
        while (getline(f, s) && s != ">>>") {
            ss.msgs.push_back(s);
        }
    }
    return catalogs.size()-1;
}

// a trivvial test
int main()
{
    if (!has_facet<My_message>(locale())) {
        cerr << "no messages facet found in " << locale().name() << '\n';
        exit(1);
    }

    const messages<char>& m = use_facet<My_messages>(locale());
    // where I keep my messages
    extern string message_directory;
    auto cat = m.open(message_directory, locale());
    if (cat < 0) {
        cerr << "no catalog found\n";
        exit(1);
    }
    cout << m.get(cat, 0, 0, "Missed again!") << endl;
    cout << m.get(cat, 3, 0, "Missed again!") << endl;
}


// section 39.4.7.1: using messages from other facets
class Season_io : public locale::facet {
    // message directory
    const messages<char>& m;
    // message catalog
    messages_base::catalog cat;
public:
    // exception class
    class Missing_messages { };
    Season_io(size_t i = 0)
        : locale::facet(i), m{use_facet<Season_messages>(locale())}, cat(m.open(message_directory.locale()))
    {
        if (cat < 0) {
            throw Missing_messages();
        }
    }
    // to make it possible to destroy Season_io objects
    ~Season_io() { }
    // string representation of x
    const string& to_str(Season x) const;
    // place Season corresponding to s in x
    bool from_str(const string& s, Season& x) const;
    // facet identifier object
    static locale::id id;
};

// define the identifier
locale::id Season_io::id;

string Season_io::to_str(Season x)
{
    return m->get(cat, 0, x, "no-such-season");
}

bool Season_io::from_str(const string& s, Season& x) const
{
    for (int i = Season::spring; i <= Season::winter; i++) {
        if (m->get(cat, 0, i, "no-such-season") == s) {
            x = Season(i);
            return true
        }
    }
    return false;
}
