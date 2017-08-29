/**************************************************************
* Name     :  ex16-1-3.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年6月5日
**************************************************************/



/*
example 16.1 : introduction
example 16.2 : class basics
    section 16.2.7 : in-class initializers
*/



// section 16.2.7 in-class initializers
class Date {
    int d, m, y;
public :
    // day, month, year
    Date(int, int, int);
    // day, month, today's year
    Date(int, int);
    // day, today's month, today's year
    Date(int);
    // default Date : today
    Date();
    // date in string representation
    Date(const char*);
    // ...
};


class Date {
    int d {today.d};
    int m {today.m};
    int y {today.y};
public :
    // day, month, year
    Date(int, int, int);
    // day, month, today's year
    Date(int, int);
    // day, today's month and year
    Date(int);
    // default Date : today
    Date();
    // date in string representation
    Date(const cahr*);
    // ...
};


Date::Date(int dd)
    : d {dd};
{
    // check that the date is valid
}

// is equivalent to
Date::Date(int dd)
    : d {dd},
    m {today.m},
    y {today.y}
{
    // check that the Date is valid
}



// section 16.2.8 in-class function definitions
class Date {
public :
    // increment the Date's m
    void add_month(int n) { m += n; }
    // ...
private :
    int d, m, y;
};


// add n months
inline void Date::add_month(int n)
{
    // increment the Date's m
    m += n;
}



// section 16.2.9 : mutability
// section 16.2.9.1 : constant member functions
class Date {
    int d, m, y;
public :
    int day() const { return d; }
    int month() const { return m; }
    int year() const;
    // add n years
    void add_year(int n);
    // ...
};

int Date::year() const
{
    // error : attempt to change member value in const function
    return ++y;
}

// error : const missing in member function type
int Date::year()
{
    return y;
}


void f(Date& d, const Date& cd)
{
    // ok
    int i = d.year();
    // ok
    d.add_year(1);
    // ok
    int j = cd.year();
    // error : cannot change value of a const Date
    cd.add_year(1);
}


// section 16.2.9.2 : physical and logical constness
class Date {
public :
    // ...
    // string representation
    string string_rep() const;
private :
    bool cache_valid;
    string cache;
    // fill cache
    void dompute_cache_value();
    // ...
};


// section 16.2.9.3 : mutable
class Date {
public :
    // ...
    // string representation
    string string_rep() const;
private :
    mutable bool cache_valid;
    mutable string cache;
    // fill (mutable) cache
    void compute_cache_value() const;
};

string Date::string_rep() const
{
    if (!cache_valid) {
        compute_cache_value();
        cache_valid = true;
    }
    return cache;
}

void f(Date d, const Date cd)
{
    string s1 = d.string_rep();
    // ok
    string s2 = cd.string_rep();
    // ...
}


// section 16.2.9.4 : mutability through indirection
struct cache {
    bool valid;
    string rep;
};

class Date {
public :
    // ...
    // string representation
    string string_rep() const;
private :
    // initialize in constructor
    cache* c;
    // fill what cache refers to
    void compute_cache_value() const;
    // ...
};


string Date::string_rep() const
{
    if (!c->valid) {
        compute_cache_value();
        c->valid = true
    }
    return c->rep;
}


// section 16.2.10 : self-reference
void f(Date& d)
{
    // ...
    d.add_day(1).add_month(1).add_year(1);
}

class Date {
    // ...
    // add n years
    Date& add_year(int n);
    // add n months
    Date& add_month(int n);
    // add n days
    Date& add_day(int n);
};

Date& Date::add_year(int n)
{
    // beware of February 29
    if (d == 29 && m == 2 && !leapyear(y + n)) {
        d = 1;
        month = 3;
    }
    y += n;
    return *this;
}

// tedious version
Date& Date::add_year(int n)
{
    // beware of February 29
    if (d == 29 && m == 2 && !leapyear(this->y + n)) {
        this->d = 1;
        this->month = 3;
    }
    this->y += n;
    return *this;
}


struct Link {
    Link* pre;
    Link* suc;
    int data;

    // insert x before this
    Link* insert(int x)
    {
        return pre = new Link {pre, this, x};
    }
    // remove and destroy this
    void remove()
    {
        if (pre) {
            pre->suc = suc;
        }
        if (suc) {
            suc-pre = pre;
        }
        delete this;
    }
    // ...
};



// section 16.2.11 : member access
struct X {
    void f();
    int m;
};

void user(X x, X* px)
{
    // error : there is no m in scope
    m = 1;
    // ok
    x.m = 1;
    // error : x is not a pointer
    x->m = 1;
    // ok
    px->m = 1;
    // error : px is a pointer
    px.m = 1;
}


void X::f()
{
    // ok : "this->m = 1;"
    m = 1;
}

struct X {
    // fine : return this X's m
    int f() { return m; }
    int m;
};


struct S {
    int m;
    int f();
    static int sm;
};

// X's f()
int X::f()
{
    return m;
}

// X's static member sm
int X::sm {7};
// X's member f()
int (S::*) pmf() {&S::f};


// section 16.2.12 : [static] members
class Date {
    int d, m, y;
    static Date default_date;
public :
    //
    Date(int dd = 0, int mm = 0, int yy = 0);
    // ...
    // set default_date to Date(dd, mm, yy)
    static void set_default(int dd, int mm, int yy);
};

Date::Date(int dd, int mm, int yy)
{
    d = dd ? dd : default_date.d;
    m = mm ? mm : default_date.m;
    y = yy ? yy : default_date.y;
    // ... check that the Date is valid ...
}

void f()
{
    // call Date's static member set_default()
    Date::set_default(4, 5, 1945);
}

// definition of Date::default_date
Date Date::default_date {16, 12, 1770};

// definition of Date::set_default
void Date::set_default(int d, int m, int y)
{
    // assign new value to default_date
    default_date = {d, m, y};
}


Date copy_of_default_date = Date {};

void f(Date);

void g()
{
    f(Date{});
}

void f1(Date);
void f2(Date);
void f2(int);

void g()
{
    // ok : equivalent to f1(Date{})
    f1({});
    // error : ambiguous : f2(int) or f2(Date)?
    f2({});
    // ok
    f2(Date{});
}



// section 16.2.13 : member types
template<typename T>
class Tree {
    // member alias
    using value_type = T;
    // member enum
    enum Policy { rb, splay, treeps };
    // member class
    class Node {
        Node* right;
        Node* left;
        value_type value;
    public :
        void f(Tree*);
    };
    Node* top;
public :
    void g(const T&);
    // ...
};


template<typename T>
void Tree::Node::f(Tree* p)
{
    // error : no object of type Tree specified
    top = right;
    // ok
    p->top = right;
    // ok : value_type is not associated with an object
    value_type v = left->value;
}


template<typename T>
void Tree::g(Tree::Node* p)
{
    // error : noobject of type Tree::Node
    value_type val = right->value;
    // error : Node::right is private
    value_type v = p->right->value;
    // ok
    p->f(this);
}

