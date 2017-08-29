/**************************************************************
* Name     :  ex11-1-5.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年5月10日
**************************************************************/



/*
example 11.4 : lambda
*/


#include <iostream>

using namespace std;


// output v[i] to os if v[i] % m == 0
void print_modulo(const vector<int>& v, ostream& os, int m)
{
    for_each(begin(v), end(v),
        [&os, m](int x) { if (x % m == 0) os << x << '\n'; }
    );
}

class Modulo_print {
    // members to hold the capture list
    ostream& os;
    int m;
public :
    // capture
    Modulo_print(ostream& s, int mm) os(s), m(mm) { }
    void operator()(int x) const { if (x % m == 0) os << x << '\n'; }
};

// output v[i] to os if v[i] % m == 0
void print_modulo(const vector<int>& v, ostream& os, int m)
{
    for_each(begin(v), end(v), Modulo_print{os, m});
}


// output v[i] to os if v[i] % m == 0
void print_modulo(const vector<int>& v, ostream& os, int m)
{
    class Modulo_print {
        // members to hold the capture list
        ostream& os;
        int m;
    public :
        // capture
        Modulo_print(ostream& s, int mm) os(s), m(mm) { }
        void operator()(int x) const { if (x % m == 0) os << x << '\n'; }
    };

    for_each(begin(v), end(v), Modulo_print{os, m});
}


// output v[i] to os if v[i] % m == 0
void print_modulo(const vector<int>& v, ostream& os, int m)
{
    auto Modulo_print = [&os, m] (int x) { if (x%m==0) os << x << '\n'; }
    for_each(begin(v), end(v), Modulo_print);
}


// output v[i] to os if v[i] % m == 0
void print_modulo(const vector<int>& v, ostream& os, int m)
{
    for (auto x : v) {
        if (x%m==0) {
            os << x << '\n';
        }
    }
}


template<class C>
// output v[i] to os if v[i]%m==0
void print_modulo(const C& v, ostream& os, int m)
{
    for (auto x : v) {
        if (x%m==0) {
            os << x << '\n';
        }
    }
}


template<class C>
// output v[i] to os if v[i]%m==0
void print_modulo(const C& v, ostream& os, int m)
{
    breadth_first(begin(v), end(v),
        [&os, m](int x) { if (x % m == 0) os << x << '\n'; }
    );
}


void algo(vector<int>& v)
{
    // sort values
    sort(v.begin(), v.end());
    // ...
    // sort absolute values
    sort(v.begin(), v.end(), [](int x, int y) { return abs(x) < abs(y); });
}


void f(vector<int>& v)
{
    bool sensitive = true;
    // ...
    // error
    sort(v.begin(), v.end(),
        [](int x, int y) { return sensitive ? x < y : abs(x) < abs(y) }
    );
}


void f(vector<int>& v)
{
    bool sensitive = true;
    // ...
    sort(v.begin(), v.end(),
        [sensitive](int x, int y) { return sensitive ? x < y : abs(x) < abs(y); }
    );
}


template<typename... Var>
void algo(int s, Var... v)
{
    auto helper = [&s, &v...] { return s * (h1(v...) + h2(v...)); }
    // ...
}


// a lambda may outlive its caller
void setup(Menu& m)
{
    // ...
    // compute positions of p1, p2 and p3
    Point p1, p2, p3;
    // probable disaster
    m.add("draw triangle", [&]{ m.draw(p1, p2, p3); });
    // ok
    m.add("draw triangle", [=]{ m.draw(p1, p2, p3); });
    // ...
    m.add
}


template<typename U, typename V>
ostream& operator<<(ostream& os, const pair<U, V>& p)
{
    return os << '{' << p.first << ',' << p.second << '}';
}

void print_all(const map<string, int>& m, const string& label)
{
    cout << label << ":\n{\n";
    for_each(m.begin(), m.end(),
        [](const pair<string, int>& p) { cout << p << '\n'; }
    );
    cout << '}\n';
}


class Request {
    // operation
    function<map<string, string>(const map<string, string&>)> oper;
    // arguments
    map<string, string> values;
    // targets
    map<string, string> results;
public :
    // parse and store request
    Request(const string& s);
    //
    void execute() {
        // do oper to values yielding results
        [this]() { results = oper(values); }
    }
};


// mutable lambdas
void algo(vector<int>& v)
{
    int count = v.size();
    std::generate(v.begin(), v.end(),
        [count]() mutable { return --count; }
    );
}


// explicitly supply a return type
void g(double y)
{
    // return type is void
    [&] { f(y); }
    // return type is double
    auto z1 = [=](int x) { return x + y };
    // error : body too complicated
    auto z2 = [=, y] {
        if (y) {
            return 1;
        }
        else {
            return 2;
        }
    }

    // return type is int
    auto z3 = [y]() { return 1 : 2; }
    // ok : explicit return type
    auto z4 = [=, y]() -> int {
        if (y) {
            return 1;
        }
        else {
            return 2;
        }
    }
}



// the type of a lambda
// reverse the characters in a C-style string
// error
auto rev = [&rev](char* b, char* e) {
    if (1 < e - b) {
        swap(*b, *--e);
        rev(++b, e);
    }
};

void f(string& s1, string& s2)
{
    function<void(char* b, char* e)> rev = [&](char* b, char* e) {
        if (1 < e - b) {
            swap(*b, *--e);
            rev(++b, e);
        }
    };
    rev(&s1[0], &s1[0] + s1.size());
    rev(&s2[0], &s2[0] + s2.size());
}

void g(vector<string>& vs1, vector<string>& vs2)
{
    auto rev = [&](char* b, char* e) {
        while (1 < e - b) {
            swap(*b++, *--e);
        }
    };
    rev(&s1[0], &s1[0] + s1.size());
    rev(&s2[0], &s2[0] + s2.size());
}


// assign to a pointer to function of an appropriate type
double (*p1)(double) = [](double a) { return sqrt(a); }
// error : the lambda captures
double (*p2)(double) = [&](double a) { return sqrt(a); }
// error : argument types do not match
double (*p3)(int) = [](int a) { return sqrt(a); }
