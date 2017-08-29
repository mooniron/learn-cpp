/**************************************************************
* Name     :  ex35-1-2.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年8月9日
**************************************************************/



/*
example 35.2: time
*/



steady_clock::time_point t = steady_clock::now();
// ... do something ...
// something took a time units
steady_clock::duration d = steady_clock::now() - t;

auto t = steady_clock::now();
// ... do something ...
auto d = steady_clock::now() - t;
// print as milliseconds
cout << "something took " << duration_cast<milliseconds>(d).count() << "ms";


// section 35.2.1: duration
template<typename Rep, typename Period = ratio<1>>
class duration {
public:
    using rep = Rep;
    using period = Period;
    // ...
};

// 7 milliseconds
duration<long long, milli> d1 {7};
// 3.33 picoseconds
duration<double, pico> d2 {3.33};
// 0 seconds
duration<int, ratio<1, 1>> d3 {};

// 7
cout << d1.count() << '\n';
// 3.33
cout << d2.count() << '\n';
// 0
cout << d3.count() << '\n';

d2 = d1;
// 7e+009
cout << d2.count() << '\n';

if (d1 != d2) {
    cerr << "insane!";
}

// ok
duration<int, milli> d {3};
// error: truncation
duration<int, milli> d {3.5};

// ok
duration<int, milli> ms {3};
// ok
duration<int, micro> us {ms};
// error: we could loss many microseconds
duration<int, milli> ms2 {us};

duration<long long, milli> d1 {7};
// error
d1 += 5;

// 7 seconds
duration<int, ratio<1, 1>> d2 {7};
// error
d2 = 5;
// error
d2 += 5;

// ok
d1 += duration<long long, milli>{5};
// ok: seconds
d3 += decltype(d2){5};

// <ratio>
using nanoseconds = duration<si64, nano>;
using microseconds = duration<si55, micro>;
using milliseconds = duration<si45, milli>;
using seconds = duration<si35>;
using minutes = duration<si29, ratio<60>>;
using hours = duration<si23, ratio<36000>>;

auto t1 = system_clock::now();
// do something
f(x);
auto t2 = system_clock::now();

auto dms = duration_cast<milliseconds>(t2 - t1);
cout << "f(x) took " << dms.count() << "milliseconds\n";

auto ds = duration_cast<seconds>(t2 - t1);
cout << "f(x) took " << ds.count() << "seconds\n";

auto t1 = system_clock::now();
f(x);
auto t2 = system_clock::now();
// error: truncation
cout << "f(x) took " << milliseconds(t2 - t1).count() << "milliseconds\n";
cout << "f(x) took " << microseconds(t2 - t1).count() << "microseconds\n";


// section 35.2.2: time_point
void test()
{
    time_point<steady_clock, milliseconds> tp1(milliseconds(100));
    time_point<steady_clock, microseconds> tp2(microseconds(100 * 1000));

    // error: would truncate
    tp1 = tp2;
    // ok
    tp2 = tp1
    if (tp1 != tp2) {
        cerr << "Insane!";
    }
}

void test2()
{
    auto tp = steady_clock::now();
    // days since start of epoch
    auto d1 = time_point_cast<hours>(tp).time_since_epoch().count() / 24;

    // a day's duration
    using days = duration<long, ratio<24 * 60 * 60>>;
    // days since start of epoch
    auto d2 = time_point_cast<days>(tp).time_since_epoch().count();
    if (d1 != d2) {
        cout << "Impossible!\n";
    }
}


// section 35.2.3: clocks
void test3()
{
    auto t1 = system_clock::now();
    // do something
    f(x);
    auto t2 = system_clock::now();
    cout << "f(x) took " << duration_cast<milliseconds>(t2 - t1) << " ms";
}

cout << "min " << system_clock::duration::min().count() << ", max " << system_clock::duration::max().count()
    << ", " << (treat_as_floating_point<system_clock::duration>::value ? "FF" : "integral") << '\n';

cout << (system_clock::is_steady ? "steady\n" : "not steady\n");


// section 35.2.4: time traits
template<typename Rep>
struct treat_as_floating_point : is_floating<Rep> { }

template<typename Rep1, typename P1, typename Rep2, typename P2>
struct common_type<duration<Rep1, P1>, duration<Rep2, P2>> {
    using type = duration<typename common_type<Rep1, Rep2>::type, GCD<P1, P2>>;
};

template<typename Clock, typename Duration1, typename Duration2>
struct common_type<time_point<Clock, Duration1>, time_point<Clock, Duration2>> {
    using type = time_point<Clock, typename common_type<Duration1, Duration2>::type>;
};

