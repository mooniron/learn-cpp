/**************************************************************
* Name     :  ex38-1-4.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年8月14日
**************************************************************/



/*
example 38.3: error handling
*/


// read into an input buffer of type X
for (X x; cin >> x; ) {
    // ... do something with x ...
}
// we get here when >> couldn't read another X from cin

int i;
if (cin >> i) {
    // ... use i ...
}
else if (cin.fail()) {
    // possibly a formatting error
    cin.clear();

    string s;
    if (cin >> s) {
        // we might be able to use a string to recover
        // ... use s ...
    }
}


// RAII class for iostream exceptions
struct Io_guard {
    iostream& s;
    auto old_e = s.exceptions();
    Io_guard(iostream& ss, ios_base::iostate e) : s{ss}
    {
        s.exceptions(s.exceptions() | e);
    }

    ~Io_guard()
    {
        s.exceptions(old_e);
    }
};


void use(istream& is)
{
    Io_guard guard(is, ios_base::badbit);
    // ... use is ...
}
catch (ios_base::badbit) {
    // ... bail out! ...
}

