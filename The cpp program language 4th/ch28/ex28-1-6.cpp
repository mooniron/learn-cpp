/**************************************************************
* Name     :  ex28-1-6.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年7月22日
**************************************************************/



/*
example 28.6 :variadic templates
*/



// section 28.6.1 : a type-safe printf()
void printf(const char* s)
{
    if (s == nullptr) {
        return;
    }
    while (*s) {
        // make sure no more arguments are expected
        // %% represents plain % in a format string
        if (*s == '%' && *++s != '%') {
            throw runtime_error("invalid format: missing arguments");
        }
        std:: cout << *s++;
    }
}

// variadic template argument list : one or more arguments
template<typename T, typename... Args>
// function argument list two or more arguments
void printf(const char* s, T value, Args... args)
{
    while (s && *s) {
        // a format specifier (ignore which one it is)
        if (*s == '%' && *++s != '%') {
            // use first non-format argument
            std::cout << value;
            // do a recursive call with the tail of the argument list
            return printf(++s, args...);
        }
        std::cout << *s++;
    }
    throw std::runtime_error("extra arguments provided to printf");
}

// variadic template argument list : one or more arguments
template<typename T, typename... Args>
// function argument list two or more arguments
void printf(const char* s, T value, Args... args)
{
    while (s && *s) {
        // a format specifier or %%
        if (*s == '%') {
            switch (*++s) {
                // not format specifier
                case '%' :
                    break;
                case 's' :
                    if (!Is_C_style_string<T>() && !Is_string<T>()) {
                        throw runtime_error("Bad printf() format");
                    }
                    break;
                case 'd' :
                    if (!Is_intergral<T>()) {
                        throw runtime_error("Bad printf() format")
                    }
                    break;
                case 'g' :
                    if (!Is_floating_point<T>()) {
                        throw runtime_error("Bad printf() format");
                    }
                    break;
            }
            // use first non-format argument
            std::cout << value;
            // do a recursive call with the tail of the argument list
            return printf(++s, args...);
        }
        std::cout << *s++;
    }
    throw std::runtime_error("extra arguments provided to printf");
}


// my own version
// variadic template argument list : one or more arguments
template<typename T, typename... Args>
// function argument list two or more arguments
void printf(const char* s, T value, Args... args)
{
    while (s && *s) {
        // a format specifier
        if (*s == '%' && *++s != '%') {
            switch (*++s) {
                case 's' :
                    if (!Is_C_style_string<T>() && !Is_string<T>()) {
                        throw runtime_error("Bad printf() format");
                    }
                    break;
                case 'd' :
                    if (!Is_intergral<T>()) {
                        throw runtime_error("Bad printf() format")
                    }
                    break;
                case 'g' :
                    if (!Is_floating_point<T>()) {
                        throw runtime_error("Bad printf() format");
                    }
                    break;
            }
            // use first non-format argument
            std::cout << value;
            // do a recursive call with the tail of the argument list
            return printf(++s, args...);
        }
        std::cout << *s++;
    }
    throw std::runtime_error("extra arguments provided to printf");
}



// section 28.6.2 : technical details
// variadic template function
template<typename... Types>
void f(Types... args);

// ok : args contains no arguments
f();
// ok : args contains one argument : int
f(1);
// ok, args contains two arguments : int and double
f(2, 1.0);
// ok : args contains three arguments : int, double, and const char*
f(2, 1.0, "Hello");

template<typename T, typename... Args>
void printf(const char* s, T value, Args... args)
{
    // ...
    // do a recursive call with the elements of args as arguments
    return printf(++s, args...);
    // ...
}

template<typename... Bases>
class X : public Bases... {
public :
    X(const Bases&... b) : Bases(b)... { }
};

X<> x0;
X<Bx> x1(1);
X<Bx, By> x2(2, 3);
X<Bx, By, Bz> x3(2, 3, 4);

template<typename... Types>
class tuple {
    // ...
    template<typename T, typename U, typename = Enable_if<sizeof...(Types) == 2>>
    tuple(const pair<T, U>&);
};


// section 28.6.3 : forwarding
template<typename F, typename... T>
void call(F&& f, T&&... t)
{
    f(forward<T>(t)...);
}

void g0()
{
    cout << "g0()\n";
}

template<typename T>
void g1(const T& t)
{
    cout << "g1(): " << t << '\n';
}

void g1d(double t)
{
    cout << "g1d(): " << t << 't';
}

template<typename T, typename T2>
void g2(const T& t, T2&& t2)
{
    cout << "g2(): " << t << ' ' << t2 << '\n';
}

void test()
{
    call(g0);
    // error : too few arguments
    call(g1);
    call(g1<int>, 1);
    call(g1<const char*>, "hello");
    call(g1<double>, 1.2);
    call(g1d, 1.2);
    // error : wrong argument type for g1d()
    call(g1d, "No way!");
    // error : too many arguments for g1d()
    call(g1d, 1.2, "I can't count");
    //
    call(g2<double, string>, 1.2, "world");
    // testing with lvalues
    int i = 99;
    const char* p = "Trying";
    call(g2<double, string>, i, p);
    call([](){cout << "ll()\n"});
    call([](int i){cout << "10(); "<< i << "\n";}, 17);
    call([i]() {cout << "11(): " << i << "\n";});
}


// section 28.6.4 : the standard-library tuple
// here is the recursion
/*
    Basically a tuple stores its head (first(type, value)pairs) and derives from
the tuple of its tail (the rest of the (type/value)pairs).
    Note that the type is encoded in the type, not stored as data
*/
template<typename Head, typename... Tail>
class tuple<Head, Tail...> : private tuple<Tail...> {
    typedef tuple<Tail...> inherited;
public :
    // default the empty tuple
    constexpr tuple() { }
    // construct tuple from separate arguments :
    tuple(Add_const_reference<Head> v, Add_const_reference<Tail>... vtail)
        : m_head(v), inherited(vtail...) { }
    // construct tuple from another tuple :
    template<typename... VValues>
    tuple(const tuple<VValues...>& other) : m_head(other.head()), inherited(other.tail()) { }
    // assignment
    template<typename... VValues>
    tuple& operator=(const tuple<VValues...>& other)
    {
        m_head = other.head();
        tail() = other.tail();
        return *this;
    }
    // ...
protected :(
    Head m_head;
private :
    Add_reference<Head> head() { return m_head; }
    Add_const_reference<const Head> head() const { return m_head; }
    inherited& tail() { return *this; }
    const inherited& tail() const { return *this; }
};

template<typename Head, typename... Tail>
Head head(tuple<Head, Tail...>& t)
{
    // get first element of t
    return std::get<0>(t);
}

template<typename Head, typename... Tail>
tuple<T&...> tail(tuple<Head, Tail...>& t)
{
    return /* details */;
}

tuple<string, vector<int>, double> tt("hello", {1, 2, 3, 4}, 1.2);
string h = head(tt.head);
tuple<vector<int>, double> t2 = tail(tt.tail);

// simplified
template<typename... Types>
tuple<Types...> make_tuple(Types&&... t)
{
    return tuple<Types...>(t...);
}

string s = "Hello";
vector<int> v = {1, 2, 3, 4, 5};
auto x = make_tuple(s, v, 1.2);

auto t = make_tuple("Hello tuple", 43, 3.15);
// d becomes 3.15
double d = get<2>(t);


// print element N and following elements
template<size_t N>
struct print_tuple {
    template<typename... T>
    // non-empty tuple
    typename enable_if<N < sizeof...(T)>::type print(ostream& os, const tuple<T...>& t) const
    {
        // print an element
        os << ", " << get<N>(t);
        // print the rest of the elements
        print_tuple<N+1>()(os, t);
    }
    // empty tuple
    template<typename... T>
    typename enable_if<!(N < sizeof...(T))>::type print(ostream&, const tuple<T...>&) const
    {
    }
};

// the empty tuple
std::ostream& operator << (ostream& os, const tuple<>&)
{
    return os << "{}";
}

// a nonempty tuple
template<typename T0, typename... T>
ostream& operator<<(ostream& os, const tuple<T0, T...>& t)
{
    // print first element
    os << '{' << std::get<0>(t);
    // print the rest of the elements
    print_tuple<1>::print(os, t);
    return os << "}";
}

void user()
{
    cout << make_tuple() << '\n';
    cout << make_tuple("one meatball!") << '\n';
    cout << make_tuple(1, 1.2, "Tail!") << '\n';
}

