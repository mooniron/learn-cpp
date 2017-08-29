/**************************************************************
* Name     :  ex28-1-7.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年7月22日
**************************************************************/



/*
example SI Units example
*/



// 10 meters
auto distance = 10_m;
// 20 seconds
auto time = 20_s;
// .5 m/s (meters per second)
auto speed = distance / time;
// error : 20 is dimensionless
if (speed == 20)
// error : can't compare m to m/s
if (speed == distance)
// ...
// ok : the units match
if (speed == 10_m / 20_s)
// ...
// MpS2 means m/(s*s)
Quantity<Mps2> acceleration = distance / square(time);
cout << "speed == " << speed << "acceleration == " << acceleration << "\n";


// section 28.7.1 : units
template<int M, int K, int S>
struct Unit {
    enum { m = M, kg = K, s = S};
};

// meters
using M = Unit<1, 0, 0>;
// kilograms
using Kg = Unit<0, 1, 0>;
// seconds
using S = Unit<0, 0, 1>;
// meters per second (m/s)
using Mps = Unit<1, 0, -1>;
// meters per square second (m/(s*s))
using Mps2 = Unit<1, 0, -2>;

template<typename U1, typename U2>
struct Uplus {
    using type = Unit<U1::m + U2::m, U1::kg+U2::kg, U1::s+U2::s>;
};

template<typename U1, typename U2>
using Unit_plus = typename Uplus<U1, U2>::type;

template<typename U1, typename U2>
struct Uminus {
    using type = Unit<U1::m - U2::m, U1::kg - U2::kg, U1::s - U2::s>;
};

template<typename U1, typename U2>
using Unit_minus = typename Uminus<U1, U2>::type;


// section 28.7.2 : quantitys
template<typename U>
struct Quantity {
    double val;
    explicit Quantity(double d) : val{d} { }
};

// x is 10.5 meters
Quantity<M> x {10.5};
// y is 2 seconds
Quantity<S> y {2};
// error : attempt to convert an int to meters/second
Quantity<Mps> s = 7;
Quantity<M> comp(Quantity<M>);
// ...
// error : comp() requires a distance
Quantity<M> n = comp(7);

// same dimension
template<typename U>
Quantity<U> operator+(Quantity<U> x, Quantity<U> y)
{
    return Quantity<U>{x.val + y.val};
}

// same dimension
template<typename U>
Quantity<U> operator-(Quantity<U> x, Quantity<U> y)
{
    return Quantity<U>{x.val - y.val};
}

template<typename U1, typename U2>
Quantity<Unit_plus<U1, U2>> operator*(Quantity<U1> x, Quantity<U2> y)
{
    return Quantity<Unit_plus<U1, U2>>{x.val * y.val};
}

template<typename U1, typename U2>
Quantity<Unit_minus<U1, U2>> operator/(Quantity<U1> x, Quantity<U2> y)
{
    return Quantity<Unit_minus<U1, U2>>{x.val / y.val};
}


Quantity<MpS> speed {10};
auto double_speed = Quantity<Unit<0, 0, 0>>{2} * speed;

template<typename U>
Quantity<U> operator*(Quantity<U> x, double y)
{
    return Quantity<U>{x.val * y};
}

template<typename U>
Quantity<U> operator*(double x, Quantity<U> y)
{
    return Quantity<U>{x * y.val};
}

Quantity<MpS> speed {10};
auto = double_speed = 2 * speed;
// error : can't add a dimensionless scalar to a speed
auto increased_speed = 2.3 + speed;


// section 28.7.3 : unit literals
// 10 meters
auto distance = Quantity<M>{10};
// 20 seconds
auto time = Quantity<S>{20};
// 0.5 m/s (meters per second)
auto speed = distance / time;

// 10.0 meters
auto distance = 10.0;
// 20 seconds
double time = 20;
auto speed = distance / time;

// user-defined literals
constexpr Quantity<M> operator""_m(double d)
{
    return Quantity<M>{d};
}

constexpr Quantity<Kg> operator""_kg(double d)
{
    return Quantity<Kg>{d};
}

constexpr Quntity<S> operator""_s(double d)
{
    return Quantity<S>{d};
}

// 10meters
auto distance = 10_m;
// 0 seconds
auto time = 20_s;
// 0.5 m/s (meters per second)
auto speed = distance / time;
// ...
if (speed == 10_m / 20_s)

constexpr Quantity<M> operator""_km(double d)
{
    return 1000 *d;
}

constexpr Quantity<Kg> operator""_g(double d)
{
    return d / 1000;
}

// milligram
constexpr Quantity<Kg> operator""_mg(double d)
{
    return d / 1000000;
}

// milliseconds
constexpr Quantity<S> operator""_ms(double d)
{
    return d / 1000;
}

// microseconds
constexpr Quantity<S> operator""_us(double d)
{
    return d / 1000000;
}

// nanoseconds
constexpr Quantity<S> operator""_ns(double d)
{
    return d / 1000000000;
}
// ...


// section 28.7.4 : utility functions
template<typename U>
Quantity<Unit_plus<U, U>> square(Quantity<U> x)
{
    return Quantity<Unit_plus<U, U>>(x.val * x.val);
}

template<typename U>
bool operator==(Quantity<U> x, Quantity<U> y)
{
    return x.val == y.val;
}

template<typename U>
bool operator!=(Quantity<U> x, Quantity<U> y)
{
    return x.val != y.val;
}

// helper function
string suffix(int u, const char* x)
{
    string suf;
    if (u) {
        suf += x;
        if (1 < u) {
            suf += '0' + u;
        }
        if (u < 0) {
            suf += '-';
            suf += '0' - u;
        }
    }
    return suf;
}

template<typename U>
ostream& operator<<(ostream& os, Quantity<U> v)
{
    return os << v.val << suffix(U::m, "m") << suffix(U::kg, "kg") << suffix(U::s, "s");
}

// 10 meters
auto distance = 10_m;
// 20 seconds
auto time = 20_s;
// .5 m/s (meters per second)
auto speed = distance / time;
// error : 20 is dimensionless
if (speed == 20)
// error : cna't compare m to m/s
if (speed == distance)
//...
// ok : the units match
if (speed == 10_m / 20_s)
// ...

// MpS2 means m/(s*s)
Quantity<MpS2> acceleration = distance/square(time);
//
cout << "speed == " << speed << "acceleration == " << acceleration << "\n";

