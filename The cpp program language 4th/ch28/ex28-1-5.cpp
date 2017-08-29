/**************************************************************
* Name     :  ex28-1-5.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年7月22日
**************************************************************/



/*
example 28.5 : a compile-time list : tuple
*/



Tuple<double, int, char> x {1.1, 42, 'a'};
cout << x << '\n';
cout << get<1>(x) << '\n';

// layout {T2, T3, T4} before T1
template<typename T1 = Nil, typename T2 = Nil, typename T3 = Nil, typename T4 = Nil>
struct Tuple : Tuple<T2, T3, T4> {
    T1 x;
    using Base = Tuple<T2, T3, T4>;
    Base* base() { return static_case<Base*>(this); }
    const Base* base() const { return static_cast<const Base*>(this); }
    Tuple(const T1& t1, const T2& t2, const T3& t3, const T4& t4) : Base{t2, t3, t4}, x{t1} { }
};


// 0-tuple
template<>
struct Tuple<> {
    Tuple() {}
};

// 1-tuple
template<typename T1>
struct Tuple<T1> : Tuple<> {
    T1 x;
    using Base = Tuple<>;
    Base* base() { return static_cast<Base*>(this); }
    const Base* base() const { return static_cast<const Base*>(this); }
    Tuple(const T1& t1) : Base{}, x{t1} { }
};

// 2-tuple, layout : T2 before T1
template<typename T1, typename T2>
struct Tuple<T1, T2> : Tuple<T2> {
    T1 x;
    using Base = Tuple<T2>;
    Base* base() { return static_cast<Base*>(this); }
    const Base* base() const { return static_cast<const Base*>(this); }
    Tuple(const T1& t1, const T2& t2) : Base{t2}, x{t1} { }
};

// 3-tuple, layout : {T2, T3} before {T1}
template<typename T1, typename T2, typename T3>
struct Tuple<T1, T2, T3> : Tuple<T2, T3> {
    T1 x;
    using Base = Tuple<T2, T3>;
    Base* base() { return static_cast<Base*>(this); }
    const Base* base() const { return static_cast<const Base*>(this); }
    Tuple(const T1& t1, const T2& t2, const T3& t3) : Base{t2, t3}, x{t1} { }
};


class F0 { /* function object with no data members */ };

typedef Tuple<int*, int*> T0;
typedef Tuple<int*, F0> T1;
typedef Tuple<int*, F0, F0> T2;


// section 28.5.1 : asimple output function
template<typename T1, typename T2, typename T3, typename T4>
void print_elements(ostream& os, const Tuple<T1, T2, T3, T4>& t)
{
    // t's x
    os << t.x << ", ";
    print_elements(os, *t.base());
}

template<typename T1, typename T2, typename T3>
void print_elements(ostream& os, const Tuple<T1, T2, T3>& t)
{
    os << t.x << ", ";
    print_elements(os, *t.base());
}

template<typename T1, typename T2>
void print_elements(ostream& os, const Tuple<T1, T2>& t)
{
    os << t.x << ", ";
    print_elements(os, *t.base());
}

template<typename T1>
void print_elements(ostream& os, const Tuple<T1>& t)
{
    os << t.x << ", ";
}

template<>
void print_elements(ostream& os, const Tuple<>& t)
{
    os << " ";
}


template<typename T1, typename T2, typename T3, typename T4>
ostream& operator<<(ostream& os, const Tuple<T1, T2, T3, T4>& t)
{
    os << "{";
    print_elements(os, t);
    os << "}";
    return os;
}

Tuple<double, int, char> x {1.1, 42, 'a'};
cout << x << "\n";

cout << Tuple<double, int, int, int>{1.2, 3, 5, 7} << "\n";
cout << Tuple<double, int, int>{1.2, 3, 5} << "\n";
cout Tuple<double, int>{1.2, 3} << "\n";
cout << Tuple<double>{1.2} << "\n";
cout << Tuple<>{} << "\n";


// section 28.5.2 : element access
Tuple<double, int, char> x {1.1, 42, 'a'};
cout << "{ " << get<0>(x) << ", " << get<1>(x) << ", "
<< get<2>(x) << "}\n";
// xx is a double
auto xx = get<0>(x);


template<int N, typename T1, typename T2, typename T3, typename T4>
Select<N, T1, T2, T3, T4>& get(Tuple<T1, T2, T3, T4>& t)
{
    return getNth<Select<N, T1, T2, T3, T4>, N>::get(t);
}

// getNth() remembers the type (Ret) of the Nth element
template<typename Ret, int N>
struct getNth {
    // get the value element N from t's Base
    template<typename T>
    static Ret& get(T& t)
    {
        return getNth<Ret, N-1>::get(*t.base());
    }
};

template<typename Ret>
struct getNth<Ret, 0> {
    template<typename T>
    static Ret& get(T& t)
    {
        return t.x;
    }
};

// operator[]() must be a member
template<typename T>
constexpr auto operator[](T t, int N)
{
    return get<N>(t);
}


// 28.5.2.1 : const Tuples
Tuple<double, int, char> x {1.1, 42, 'a'};
// ok
get<2>(x) = 'b';

const Tuple<double, int, char> xx {1.1, 42, 'a'};
// error : xx is const
get<2>(xx) = 'b';
// error : xx is const (surprise)
char cc = get<2>(xx);

// getNth() remembers the type (Ret) of the Nth element
template<typename Ret, int N>
struct getNth {
    // get the value element N from t's Base
    template<typename T>
    static Ret& get(T& t)
    {
        return getNth<Ret, N-1>::get(*t.base());
    }
    // get the value element N from t's Base : const version
    template<typename T>
    static const Ret& get(const T& t)
    {
        return getNth<Ret, N-1>::get(*t.base());
    }
};

template<typename Ret>
struct getNth<Ret, 0> {
    template<typename T>
    static Ret& get(T& t)
    {
        return t.x;
    }
    template<typename T>
    static const Ret& get(const T& t)
    {
        return t.x;
    }
};

template<int N, typename T1, typename T2, typename T3, typename T4>
Select<N, T1, T2, T3, T4>& get(Tuple<T1, T2, T3, T4>& t)
{
    return getNth<Select<N, T1, T2, T3, T4>, N>::get(t);
}

template<int N, typename T1, typename T2, typename T3, typename T4>
const Select<N, T1, T2, T3, T4>& get(const Tuple<T1, T2, T3, T4>& t)
{
    return getNth<Select<N, T1, T2, T3, T4>, N>::get(t);
}


// section 28.5.3 : make_tuple
template<typename T1, typename T2, typename T3, typename T4>
Tuple<T1, T2, T3, T4> make_Tuple(const T1& t1, const T2& t2, const T3& t3, const T4& t4)
{
    return Tuple<T1, T2, T3, T4>{t1, t2, t3, t4};
}

// ... and the other four make_Tuples ...

auto xxx = make_Tuple(1.2, 3, 'x', 1223);
cout << "xxx : " << xxx << "\n";

