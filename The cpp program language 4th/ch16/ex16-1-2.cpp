/**************************************************************
* Name     :  ex16-1-2.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年6月5日
**************************************************************/



/*
example 16.1 : introduction
example 16.2 : class basics
*/


 class X {
private :
    // the representation (implementation) is private
    int m;
public :
    // the user interface is public
    // a constructor (initializes the member data m)
    X(int i = 0) : m {i} { }
    // a member function
    int mf(int i)
    {
        int old = m;
        // set a value
        m = i;
        // return the old value
        return old;
    }
 };


// a var variable of type X initialized  to 7
X var {7};
int user(X var, X* ptr)
{
    // access using .(dot)
    int x = var.mf(7);
    // access using ->(arrow)
    int y = ptr->(9);
    // error : can not access private member
    int z = var.m;
}


// section 16.2.1 : member functions
// representation
struct Date {
    int d, m, y;
};

// initialize d
void init_date(Date& d, int, int, int);
// add n years to d
void add_year(Date& d, int n);
// add n months to d
void add_month(Date& d, int n);
// add n days to d
void add_day(Date& d, int n);


struct Date {
    int d, m, y;

    void init(int dd, int mm, int yy);
    // add n years
    void add_year(int n);
    // add n months
    void add_month(int n);
    // add n days
    void add_day(int n);
};


Date my_birthday;
void f()
{
    Date today;
    today.init(16, 10, 1996);
    my_birthday.init(12, 12, 1999);
    Date tomorrow = today;
    tomorrow.add_day(1);
    // ...
}

void Date::init(int dd, int mm, int yy)
{
    d = dd;
    m = mm;
    y = yy;
}



// section 16.2.2 : default copying
// initialization by copying
Date d1 = my_birthday;
// initialization by copying
Date d2 {my_birthday};

void f(Date& d)
{
    // assignment by copying
    d = my_birthday;
}



// section 16.2.3 : access control
class Date {
    int d, m, y;
public :
    // initialize
    void init(int dd, int mm, int yy);
    // add n years
    void add_year(int n);
    // add n months
    void add_month(int n);
    // add n days
    void add_day(int n);
};

void Date::add_year(int n)
{
    y += n;
}

void timewarp(Date& d)
{
    // error : Date::y is private
    d.y -= 200;
}


Date dx;
// error : m is private
dx.m = 3;
// ok
dx.init(23. 3. 2017);


// section 16.2.4 : class and struct
struct S { /* ... */ };
// a shorthand
class S { public : /* ... */ };

// members of class are private by default
class Date1 {
    // private by default
    int d, m, y;
public :
    Date1(int dd, int mm, int yy);
    // add n years
    void add_year(int n);
};


struct Date2 {
private :
    int d, m, y;
public :
    //
    Date2(int dd, int mm, int yy);
    // add n years
    void add_year(int n);
};


class Date3 {
public :
    Date3(int dd, int mm, int yy);
    // add n years
    void add_year(int n);
private :
    int d, m, y;
};

class Date4 {
public :
    Date4(int dd, int mm, int yy);
private :
    int d, m, y;
public :
    // add n years
    void add_year(int n);
};



// section 16.2.5 : constructors
class Date {
    int d, m, y;
public :
    // constructor
    Date(int dd, int mm, int yy);
    // ...
};

Date today = Date(05, 6, 2017);
Date christmas(25, 12, 2017);
// error : initializer missing
Date my_birthday;
// error : third argument missing
Date release1_0(10, 12);
Date today = Date{05, 6, 2017};
Date christmas {25, 12, 2017};
// error : third argument missing
Date release1_0 {10, 12};


class Date {
    int d, m, y;
public :
    // ...
    // day, month, year
    Date(int, int, int);
    // day, month, today's year
    Date(int, int);
    // day, today's month and year
    Date(int);
    // default date : today
    Date();
    // date in string representation
    Date(const char*);
};

// 4, today.m, today.y
Date today {4};
// string format date
Date july4 {"july 4, 1983"};
// 5, november, today.y
Date guy {5, 11};
// default initialized as today
Date now;
// default initialized as today
Date start {};


class Date {
    int d, m, y;
public :
    Date(int dd = 0, int mm = 0, int yy = 0);
    // ...
};

Date::Date(int dd, int mm, int yy)
{
    // check that the date is valid
    d = dd ? dd : today.d;
    m = mm ? mm : today.m;
    y = yy ? yy : today.y;
}


class Date {
    int d, m, y;
public :
    Date(int dd = today.d, int mm = today.m, int yy = today.y);
    // ...
};

Date::Date(int dd, int mm, int yy)
{
    // check that the Date is valid
}



// section 16.2.6 : explicit constructors
// d == {1, 0}
complex<double> d {1};

void my_fct(Date d);

void f()
{
    // plausible : x becomes {15, today.m, today.y}
    Date d {15};
    // ...
    // obscure
    my_fct(15);
    // obscure
    d = 15;
    // ...
}


class Date {
    int d, m, y;
public :
    explicit Date(int dd = 0, int mm = 0, int yy = 0);
    // ...
};

// ok : considered explicit
Date d1 {15};
// ok : explicit
Date d2 = Date{15};
// error : = initialization does not do implicit conversions
Date d3 = {15};
// error : = initialization does not do implicit conversions
Date d4 = 15;

void f()
{
    // error : argument passing does not do implicit conversions
    my_fct(15);
    // error : argument passing does not do implicit conversions
    my_fct({15});
    // ok : explicit
    my_fct(Date{15});
}


class Date {
    int d, m, y;
public :
    explicit Date(int dd);
    // ...
};

// ok
Date::Date(int dd)
{
    /* ... */
}

// error
explicit Date::Date(int dd)
{
    /* ... */
}


struct X {
    explicit X();
    explicit X(int, int);
};

// error : implicit
X x1 = {};
// error : implicit
X x2 = {1, 2};
// ok : explicit
X x3 {};
// ok : explicit
X x4 {1, 2};

int f(X);
// error : implicit
int i1 = f({});
// error : implicit
int i2 = f({1, 2});
// ok : explicit
int i3 = f(X{});
// ok: explicit
int i4 = f(X{1, 2});


