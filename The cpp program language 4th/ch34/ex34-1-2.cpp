/**************************************************************
* Name     :  ex34-1-2.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年8月5日
**************************************************************/



/*
example 34.1: introduction
example 34.2: "almost containers"
*/



// section 34.2.1: array
// an array of N Ts
template<typename T, size_t N>
struct array {
    /*
    types and operations like vector's except operations that change the container size,
    constructors, and assign() functions
    */

    // assign N copies of v
    void fill(const T& v);
    void swap(array&) noexcept(noexcept(swap(declval<T&>(), declval<T&>())));
    // implementation detail
    T __elem[N];
};


void f()
{
    array<string, 4> aa = {"Churchill", "Clare"};
    // ...
}

// error: size not specified
array<int> ax = {1, 2, 3};
array<int, 0> a0;

void f(int n)
{
    // error: size not a constant expression
    array<string, n> aa = {"John's", "Queens"};
    // ...
}

void f()
{
    // uninitialized so far
    array<int, 8> aa;
    // assign eight copies of 99
    aa.fill(99);
    // ...
}

// C-style interface
void f(int* p, int sz);

void g()
{
    array<int, 10> a;
    // error: no conversion
    f(a, a.size());
    // C-style use
    f(&a[0], a.size());
    // C-style use
    f(a.data(), a.size());
    // C+++/STL-style use
    auto p = find(a.begin(), a.end(), 777);
    // ...
}


void h()
{
    Circle a1[10];
    array<Circle, 10> a2;
    // ...
    // ok: disaster waiting to happen
    Shape* p1 = a1;
    // error: no conversion of array<Circle, 10> to Shape*
    // disaster
    p1[3].draw();
}


// N
tuple_size<array<T,N>>::value;
// T
tuple_element<S, array<T,N>>::type

template<size_t index, typename T, size_t N>
T& get(array<T, N>& a) noexcept;
template<size_t index, typename T, size_t N>
T&& get(array<T, N>&& a) noexcept;
template<size_t index, typename T, size_t N>
const T& get(const array<T, N>& a) noexcept;

array<int, 7> a = {1, 2, 3, 5, 8, 13, 25};
// 13
auto x1 = get<5>(a);
// 13
auto x2 = a[5];
// 7
auto sz = tuple_size<decltype(a)>::value;
// x3 is an int
typename tuple_element<5, decltype(a)>::type x3 = 13;

template<typename Tuple>
constexpr size_t Tuple_size()
{
    return tuple_size<Tuple>::value;
}

template<size_t n, typename T>
using Tuple_element = typename tuple_element<n, T>::type;
// 7
auto sz = Tuple_size<decltype(a)>();
Tuple_element<5, decltype(a)> x3 = 13;



// section 34.2.2: bitset
template<size_t N>
class bitset {
public:
    // reference to a single bit
    class reference {
        friend class bitset;
        reference() noexcept;
    public:
        // support zero-based subscripting in [0 : b.size())
        ~reference() noexcept;
        // for b[i] = x
        reference& operator=(bool x) noexcept;
        // for b[i] = b[j]
        reference& operator=(const reference&) noexcept;
        // return ~b[i]
        bool operator~() const noexcept;
        // for x = b[i];
        operator bool() const noexcept;
        // b[i].flip();
        reference& flip() noexcept;
    };
    // ...
};


// section 34.2.2.1: constructors
void f()
{
    // all 0
    bitset<10> b1;
    // 1010101010101010
    bitset<16> b2 = 0xaaaa;
    // 00000000000000001010101010101010
    bitset<32> b3 = 0xaaaa;
    // 1010101010
    bitset<10> b4 {"1010101010"};
    // 0111011110
    bitset<10> b5 {"10110111011110", 4};
    // 1010101010
    bitset<10> b6 {string{"1010101010"}};
    // 0111011110
    bitset<10> b7 {string{"10110111011110"}, 4};
    // 0011011101
    bitset<10> b8 {string{"10110111011110"}, 2, 8};
    // invalid_argument thrown
    bitset<10> b9 {string{"n0g00d"}};
    // error: no implicit string to bitset conversion
    bitset<10> b10 = string{"101001"};
}


// section 24.2.2.2: bitset operations
bitset<9> bs {"110001111"};
// write "110001111" to cout
cout << bs << '\n';
// bs2 == "00111000";
auto bs2 = bs << 3;
// write "001111000" to cout
cout << bs2 << '\n';
// read from cin
cin >> bs;
// bs2 == "000110001" if the input were "110001111"
bs2 = bs >> 3;
cout << bs2 << '\n';

void binary(int i)
{
    // assume 8-bit byte
    bitset<8 * sizeof(int)> b = i;
    // general and verbose
    cout << b.to_string<char, char_traits<char>, allocator<char>>() << '\n';
    // use default traits and allocator
    cout << b.to_string<char>();
    // use all defaults
    cout << b.tostring<>() << '\n';
    // use all defaults
    cout << b.tostring() << '\n';
}

void binary2(int i)
{
    biiset<8 * sizeof(int)> b = i;
    cout << b << '\n';
}


// section 34.2.3: vector<bool>
template<typename A>
// specialization of vector<T, A>
class vector<bool, A> {
public:
    using const_reference = bool;
    using value_type = bool;
    // like vector<T, A>

    // support zero-based subscripting in [0, v.size())
    class reference {
        friend class vector;
        reference() noexcept;
    public:
        ~reference();
        operator bool() const noexcept;
        reference& operator=(const bool x) noexcept;
        reference& operator=(const reference& x) noexcept;
        // for v[i] = ~v[i][
        void flip() noexcept;
    };

    // flip all bits of v
    void flip() noexcept;
    // ...
};


// section 34.2.4: tuples
// section 34.2.4.1: pair
template<typename T, typename U>
struct pair {
    // the type of the first element
    using first_type = T;
    // the type of the second element
    using second_type = U;

    // first element
    T first;
    // second element
    U second;
    // ...
};

void f()
{
    pair<string, int> p {"Cambridge", 1209};
    cout << p.first;
    p.second += 800;
    // ...
}

struct Univ {
    Univ(const string& n, int r) : name{n}, rank{r} { }
    string name;
    int rank;
    string city = "unknown";
};

using Tup = tuple<string, int>;

Tup t1 {"Columbia", 11};
Tup t2 {"Cambridge", 2};
// pair of tuples
pair<Tup, Tup> p1 {t1, t2};
// pair of Univs
pair<Univ, Univ> p2 {piecewise_construct, t1, t2};

auto p = make_pair("Harvard", 1736);


// section 34.2.4.2: tuple
tuple<string, vector<double>, int> t2 = make_tuple("Hello, tuples!", vector<int>{1, 2, 3}, 'x');

tuple<int, int, int> rotate(tuple<int, int, int> t)
{
    // error: explicit tuple constructor
    return {t.get<2>(), t.get<0>(), t.get<1>()};
}

// error: explicit tuple constructor
auto t2 = rotate({3, 7, 9});

pair<int, int> rotate(pair<int, int> p)
{
    return {p.second, p.first};
}

auto p2 = rotate({3, 7});

auto t = make_tuple(2.71828, 299792458, "Hannibal");
double c;
string name;
// c = 2.71828, name = "Hannibal"
tie(c, ignore, name) = t;

double c = get<0>(t);
string name = get<2>(t);

tuple<int, int, double, string> compute();
// ...
double c;
string name;
// results in c and name
tie(c, ignore, name) = t;

