/**************************************************************
* Name     :  ex39-1-2.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年8月20日
**************************************************************/



/*
example 39.1: handling cultural  differences
*/


// print in the appropriate format
void print_date(const Date& d)
{
    // user-defined style indicator
    switch(where_am_I) {
        case DK:
            cout << d.day() << ", " << dk_month[d.month()] << " " << d.year();
            break;
        case ISO:
            cout << d.year() << " - " << d.month() << " / " << d.day();
            break;
        case US:
            cout << d.month() << "/" << d.day() << "/" << d.year();
            break;
        // ...
    }
}

// copy (Date, double) stream
void cpy(istream& is, ostream& os)
{
    Date d;
    double volume;

    while (is >> d >> volume) {
        os << d << ' ' << volume << '\n';
    }
}

void f(istream& fin, ostream& fout, istream& fin2, ostream& fout2)
{
    // American English
    fin.imbue(locale{"en_US.UTF-8"});
    // french
    fout.imbue(locale{"fr_FR.UTF-8"});
    // Read American, write French
    cpy(fin, fout);
    // ...
    fin2.imbue(locale{"fr_FR.UTF-8"});
    fout2.imbue(locale{"en_US.UTF-8"});
    // read French, write American English
    cpy(fin2, fout2);
    // ...
}

