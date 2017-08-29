/**************************************************************
* Name     :  ex39-1-4.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年8月20日
**************************************************************/



/*
example 39.3: class facet
*/


class locale::facet {
protected:
    explicit facet(size_t refs = 0);
    virtual ~facet();
    facet(const facet&) = delete;
    void operator=(const facet&) = delete;
};

class locale::id {
public:
    id();
    void operator=(const id&) = delete;
    id(const id&) = delete;
};


// section 39.3.1: accessing facets in a locale
void f(const locale& my_locale)
{
    // use standard facet
    char c = use_facegt<mumpunct<char>>(my_locale).decimal_point();
    // ...
    // does my_locale contain an Encrypt facet?
    if (has_facet<Encrypt>my_locale) {
        // retrieve Encrypt facet
        const Encrypt& f = use_facet<Encrypt>(my_locale);
        // use Encrypt facet
        const Crypto c = f.get_crypto();
        // ...
    }
    // ...
}


// section 39.3.2: a simple user-defined facet
// very simple user-defined type
enum Season {spring, summer, fall, winter};

class Season_io : public locale::facet {
public:
    Season_io(int i = 0) : locale::facet{i} { }
    // to make it possible to destroy Season_io objects
    ~Season_io() { }
    // string representation of x
    virtual const string& to_str(Season x) const = 0;
    // place Season for s in x
    virtual bool from_str(const string& s, Season& x) const = 0;
    // facet identifier object
    static locale::id id;
};

// define the identifier object
locale::id Season_io::id;

ostream& operator<<(ostream& os, Season x)
{
    // extract the stream's locale
    locale loc {os.getloc()};

    if (has_facet<Season_io>(loc)) {
        // string representation
        return os << use_facet<Season_io>(loc).to_str(x);
    }
    // integer representation
    return os << static_cast<int>(x);
}

istream& operator>>(istream& is, Season& x)
{
    // extract the stream's locale
    const locale& loc {is.getloc()};

    if (has_facet<Season_io>(loc)) {
        // get hold of the locale's Season_io facet
        const Season_io& f{use_facet<Season_io>(loc)};
        string buf;
        // read alphabetic representation
        if (!(is >> buf && f.from_str(buf, x))) {
            is.setstate(ios_base::failbit);
        }
        return is;
    }

    int i;
    // read numeric representation
    is >> i;
    x = static_cast<Season>(i);
    returnis;
}

// a trivial test
int main()
{
    Season x;
    // use the default locale (no Season_io facet) implies integer I/O:
    cin >> x;
    cout << x << endl;

    locale loc(locale(), new US_season_io{});
    // use locale with Season_io facet
    cout.imbue(loc);
    // use locale with Season_io facet
    cin.imbue(loc);
    cin >> x;
    cout << x << endl;
}

class US_season_io : public Season_io {
    static const string seasons[];
public:
    const string& to_str(Season) const;
    bool from_str(const string&, Season&) const;
    // note no US_season_io::id
};

const string US_season_io::seasons[] = {
    "spring",
    "summer",
    "fall",
    "winter"
};

const string& US_season_io::to_str(Season x) const
{
    if (x < spring || x > winter) {
        static const string ss = "no-such-season";
        return ss;
    }
    return seasons[x];
}

bool US_season_io::from_str(const string& s, Season& x) const
{
    const string* p = find(begin(seasons), end(seasons), s);
    if (p == end(seasons)) {
        return false;
    }
    x = Season(p-begin(seasons));
    return true;
}


// section 39.3.3: uses locales and facets
