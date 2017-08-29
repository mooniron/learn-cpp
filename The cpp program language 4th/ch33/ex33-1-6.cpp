/**************************************************************
* Name     :  ex33-1-6.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年8月2日
**************************************************************/



/*
example 33.5: function adaptors
*/



// section 33.5.1: bind()
double cube(double);
auto cube2 = bind(cube, 2);

using namespace placeholders;

void f(int, const string&);
// bind f()'s first argument to 2
auto g = bind(f, 2, _1);
f(2, "hello");
// also calls f(2, "hello");
g("hello");
// also calls f(2, "hello")
bind(f)(2, "hello");
// also calls f(2, "hello");
bind(f, _1, _2)(2, "hello");
// reverse order of arguments also calls f(2, "hello")
bind(f, _2, _1)("hello", 2);
// reverse order of arguments
auto g = [](const string& s, int i) { f(i, s); }
// also calls f(2, "hello")
g("hello", 2);


int pow(int, int);
// pow() is overloaded
double pow(double, double);

// error: which pow()?
auto pow2 = bind(pow, _1, 2);
// ok but ugly
auto pow2 = bind((double(*)(double, double))pow, _1, 2);


void incr(int& i)
{
    ++i;
}

void user()
{
    int i = 1;
    // i becomes 2
    incr(i);
    auto inc = bind(incr, _1);
    // i stays 2; inc(i) incremented a local copy of i
    inc(i);
    // i becomes 3
    inc(ref(i));
}


// section 33.5.2: mem_fn()
void user(Shape* p)
{
    p->draw();
    auto draw = mem_fn(&Shape::draw);
    draw(p);
}

void draw_all(vector<Shape*>& v)
{
    for_each(v.begin(), v.end(), mem_fn(&Shape::draw));
}

// lambdas is better
void draw_all(vector<Shape*>& v)
{
    for_each(v.begin(), v.end(), [](Shape* p){ p->draw(); });
}


// section 33.5.3: function
int f(double);
// initialize to f
function<int(double)> fct {f};
int g(int);

void user()
{
    // assign lambda to fct
    fct = [](double d) { return round(d); };
    // assign function to fct
    fct = f;
    // error: incorrect return type
    fct = g;
}

int round(double x)
{
    // conventional 4/5 rounding
    return static_cast<int>(floor(x + 0.5));
}

// f can hold anything that can be called with a double and return an int
function<int(double)> f;

enum class Round_style {
    truncate, round
};

// function object carrying a state
struct round {
    Round_style s;
    Round(Round_style ss) : s {ss} { }
    int operator()(double x) const { return (s == Round_style::round) ? (x+0.5) : x; }
};

void t1()
{
    f = round;
    // call through f to the function round
    cout << f(7.6) << '\n';
    f = Round(Round_style::truncate);
    // call the function object
    cout << f(7.6) << '\n';
    Round_style style = Round_style::round;
    f = [style](double x){ return (style == Round_style::round) ? x+0.5 : x; };
    // call the lambda
    cout << f(7.6) << '\n';

    vector<double> v {7.6};
    f = Round(Round_style::round);
    // pass to algorithm
    std::transform(v.begin(), v.end(), v.begin(), f);
    // transformed by the function object
    cout << v[0] << '\n';
}

