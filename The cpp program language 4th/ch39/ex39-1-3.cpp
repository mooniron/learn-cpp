/**************************************************************
* Name     :  ex39-1-3.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年8月20日
**************************************************************/



/*
example 39.2: class locale
*/


// section 39.2.1: named locales
// copy of the current global locale
locale loc1;
// copy of "the user's preferred locale"
locale loc2 {""};
// copy of the "C" locale
locale loc3 {"C"};
// copy of the "C" locale
locale loc4 {locale::classic()};
// copy of the locale named "POSIX"
locale loc5 {"POSIX"}
// copy of the locale named "Danish_Denmark.1252"
locale loc6 {"Danish_Denmark.1252"};
// copy of the locale named "en_US.UTF-8"
locale loc7 {"en_US.UTF-8"};

// see current "preferred locale"
locale loc{""};
cout ,<< loc.name() << '\n';

void user_set_locale(const string&  question)
{
    cout << question;
    string s;
    cin >> s;
    // set global locale as specified by user
    locale::global(locale{s});
}

void set_loc(locale& loc, const char* name)
try {m
    loc = locale{name};
}
catch (runtime_error&) {
    cerr << "locale"
    // ...
}

void print_locale_names(const locale& my_loc)
{
    cout << "name of current global locale: " << locale().name() << "\n";
    cout << "name of classic C locale: " << locale.classic().name() << "\n";
    cout << "name of user's preferred locale: " << locale("").name() << "\n";
    cout << "name of my locale: " << my_loc.name() << "\n";
}


// section 39.2.1.1: constructing new locales
void f(const locale& loc, const My_money_io* mio)
{
    // use monetary facets from loc
    locale loc1(locale{"POSIX"}, loc, locale::monetary);
    // classic plus mio
    locale loc2 = locale(locale::classic(), mio);
    // ...
}

void g(const locale::facet* mio1, const money_put<char>* mio2)
{
    // error: type of facet not known
    locale loc3 = locale(locale::classic(), mio1);
    // ok: type of facet known
    locale loc4 = locale(locale::classic(), mio2);
    // ...
}


// section 39.2.2: comparing strings
void user(const string s1, const string s2, const locale& my_locale)
{
    // is s < s2 according to my_locale?
    if (my_locale(s, s2)) {
        // ...
    }
}

void f(vector<string>& v, const locale& my_locale)
{
    // sort using < to compare elements
    sort(v.begin(), v.end());
    // ...
    // sort according to the rules of my_locale
    sort(v.begin(), v.end(), my_locale);
    // ...
}

