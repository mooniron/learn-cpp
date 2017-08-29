/**************************************************************
* Name     :  ex16-1-4.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年6月5日
**************************************************************/



/*
example 16.3 : concrete classes
*/


namespace Chrono {
    enum class Month { jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec };
    class Date {
    // public interface
    public :
        // exception class
        class Bad_date {};
        // constructor, {} means "pick a default"
        explicit Date(int dd = {}, Month mm = {}, int yy = {});
        // nonmodifying functions for examining the Date :
        int day() const;
        Month month() const;
        int year() const;
        // string representation
        string string_rep() const;
        // C-style string representation
        void char_rep(char s[], int max) const;

        // (modifying) functions for changing the Date:
        // add n years
        Date& add_year(int n);
        // add n months
        Date& add_month(int n);
        // add n days
        Date& add_day(int n);
    private :
        // check if this Date represents a date
        bool is_valid();
        // representation
        int d, m, y;
    };

    int diff(Date a, Date b);
    // true for valid date
    bool is_date(int d, Month m, int y);
    // true if y is a leap year
    bool is_leapyear(int y);
    Date next_weekday(Date d);
    Date next_saturday(Date d);

    //
    bool operator==(const Date& a, const Date& b);
    bool operator!=(const Date& a, const Date& b);
    // the default date
    const Date& default_date();
    // print Date d to os
    ostream& operator<<(ostream& os, const Date& d);
    // read Date from is into d
    istream& operator>>(istream& is, Date& d);
}   // Chrono


void f(Date& d)
{
    Date lvb_day {16, Month::dec, d.year};
    if (d.day() == 29 && d.month() == Month::feb) {
        // ...
    }
    if (midnight()) {
        d.add_day(1);
    }

    cout << "day after :" << d + 1 << '\n';
    // initialized to the default date
    Date dd;
    cin >> dd;
    if (dd == d) {
        cout << "Hurray!\n";
    }
}


const Date& Chrono::default_date();


// section 16.3.1 : member functions
// constructor
Date::Date(int dd, Month mm, int yy)
    : d {dd}, m {mm}, y {yy}
{
    if (y == 0) {
        y = default_date().year();
    }
    if (m == Month {}) {
        m = default_date().month();
    }
    if (d == 0) {
        d = default_date().day();
    }

    if (!is_valid()) {
        throw Bad_date();
    }
}


void fill(vector<Date>& aa)
{
    while (cin) {
        Date d;
        try {
            cin >> d;
        }
        catch (Date::Bad_date) {
            // ... my error handling ...
            continue;
        }
        aa.push_back(d);
    }
}


bool Date::is_valid()
{
    return is_date(d, m, y);
}

inline int Date::day() const
{
    return d;
}

Date& Date::add_month(int n)
{
    if (n == 0) {
        return *this;
    }

    if (n > 0) {
        // number of whole years
        int delta_y = n / 12;
        // number of months ahead
        int mm = static_cast<int>(m) + n % 12;
        // note : dec is represented by 12
        if (mm > 12) {
            ++delta_y;
            mm -= 12;
        }

        // handle the cases where the month mm doesn't have day d ...
        y += delta_y;
        m = static_cast<Month>(mm);
        return *this;
    }

    // ... handle negativve n ...

    return *this;
}


// 16.3.2 helper functions
// number of days in the range [a,b) or [b, a)
int diff(Date a, Date b);
bool is_leapyear(int y);
bool is_date(int d, Month m, int y);

const Date& default_date();
Date next_weekday(Date d);
Date next_saturday(Date d);


bool Chrono::is_date(int d, Month m, int y)
{
    int ndays;

    switch (m) {
        case Month::feb :
            ndays = 28 + is_leapyear(y);
            break;
        case Month::apr :
        case Month::jun :
        case Month::sep :
        case Month::nov :
            ndays = 30;
            break;
        case Month::jan :
        case Month::mar :
        case Month::may :
        case Month::jul :
        case Month::aug :
        case Month::oct :
        case Month::dec :
            ndays = 31;
            break;
        default :
            return false;
    }

    return 1 <= d && d <= ndays;
}


const Date& Chrono::default_date()
{
    static Date d {1, Month::jan, 1970};
    return d;
}



// section 16.3.3 : overloaded operators
// equality
inline bool operator==(Date a, Date b)
{
    return a.day() == b.day() && a.month() == b.month() && a.year() == b.year();
}


namespace Chrono {
// inequality
bool operator!=(Date, Date);
// less than
bool operator<(Date, Date);
// greater than
bool operator>(Date, Date);

// increase Date by one day
Date& operator++(Date& d)
{
    return d.add_day(1);
}

// decrease Date by one day
Date& operator--(Date& d)
{
    return d.add_day(-1);
}

// add n days
Date& operator+=(Date& d, int n)
{
    return d.add_day(n);
}

// subtract n days
Date& operator-=(Date& d, int n)
{
    return d.add_day(-n);
}

// add n days
Date operator+(Date d, int n)
{
    return d += n;
}

// subtract n days
Date operator-(Date d, int n)
{
    return d -=n;
}

// output d
ostream& operator<<(ostream&, Date d);
// read into d
istream& operator>>(istream&, Date& d);
}   // Chrono



// section 16.3.4 : the significance of concrete classes
class Date_and_time {
private :
    Date d;
    Time t;
public :
    Date_and_time(Date d, Time t);
    Date_and_time(int d, Date::Month m, int y, Time t);
    // ...
};

