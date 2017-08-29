/**************************************************************
* Name     :  ex24-1-4.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年7月15日
**************************************************************/



/*
example 24.4 : making concepts concrete
*/


template<typename C>
class String {
    static_assert(Ordered<C>(), "String's character type is not ordered");
    // ...
};

template<typename T>
constexpr bool Ordered()
{
    return Regular<T>() && Totally_ordered<T>();
}

template<typename T>
constexpr bool Totally_ordered()
{
    return Equality_comparable<T>() && Has_less<T>() && Boolean<Less_result<T>>()
    && Has_greater<T>() && Boolean<Greater_result<T>>()
    && Has_less_equal<T>() && Boolean<Less_equal_result<T>>()
    && Has_greater_equal<T>() && Boolean<Greater_equal_result<T>>();
}

template<typename T>
constexpr bool Equality_comparable()
{
    return Has_equal<T>() && Boolean<Equal_result<T>>()
    &&& Has_not_equal<T>() && Boolean<Not_equal_result<T>>();
}

template<typename T>
constexpr bool Regular()
{
    return Semiregular<T>() && Equality_comparable<T>();
}

template<typename T>
constexpr bool Semiregular()
{
    return Destructible<T>() && Default_constructible<T>()
    && Move_constructible<T>() && Move_assignable<T>()
    && Copy_constructible<T>() && Copy_assignable<T>();
}

template<typename C>
ostream& operator<<(ostream& out, String<C>& s)
{
    static_assert(Streamable<C>(), "String's character not streamable");
    out << '"';
    for (int i = 0; i != s.size(); ++i) {
        cout << s[i];
    }
    out << '"';
}

template<typename T>
constexpr bool Streamable()
{
    return Input_streamable<T>() && Output_streamable<T>();
}

// will succeed
static_assert(Ordered<std::string>, "std::string is not Ordered");
// will fail
static_assert(Ordered<String<char>>, "String<char> is not Ordered");

template<typename C>
bool operator<(const String<C>& s1, const String<C>& s2)
{
    static_assert(Ordered<C>(), "String's character type not ordered");
    bool eq = true;
    for (int i = 0; i != s1.size() && i != s2.size(); ++i) {
        if (s2[i] < s1[i]) {
            return false
        }
        if (s1[i] < s2[2]) {
            eq = false;
        }
    }
    if (s2.size() < s1.size()) {
        return false;
    }
    if (s1.size() == s2.size() && eq) {
        return false;
    }
    return true;
}


// section 24.4.1 : axioms
// semantics of copy construction
template<typename T>
bool Copy_equality(T x)
{
    // a copy compares equal to what it is a copy of
    return T{x} = x;
}

// semantics of assignment
template<typename T>
bool Copy_assign_equality(T x, T& y)
{
    //the result of an assignment compares equal to the source of the assignment
    return (y = x, y == x);
}

// semantics of move
template<typename T>
bool Move_effect(T x, T& y)
{
    return (x == y ? T{std::move(x)} == y : true) && can_destroy(y);
}

// semantics of move assignment
template<typename T>
bool Move_assign_effect(T x, T& y, T& z)
{
    return (y == z ? (x = std::move(y), x == z) : true) && can_destroy(y);
}



// section 24.4.2 : multi-argument concepts
template<typename Iter, typename Val>
Iter find(Iter b, Iter e, Val x);

template<typename A, typename B>
constexpr bool Equality_comparable(A a, B b)
{
    return Common<T, U>() && Totally_ordered<T>() && Totally_ordered<U>()
    && Totally_ordered<Common_type<T, U>>() && Has_less<T, U>() &&
    // ...
}


template<typename Iter, typename Val>
Iter find(Iter b, Iter e, Val x)
{
    static_assert(Input_iterator<Iter>(), "find() requires an input iterator");
    static_assert(Equality_comparable<Value_type<Iter>, Val>(), "find() a iterator and value arguments must match");
    while (b != e) {
        if (*b == x) {
            return b;
        }
        ++b;
    }
    return b;
}


// section 24.4.3 : value concepts
template<int N>
constexpr bool Smal_size()
{
    return N <= 8;
}

constexpr int stack_limit = 2048;

// T is regular and N elements of T can fit on a smal  stack
template<typename T, int N>
constexpr bool Stackable()
{
    return Regular<T>() && sizeof(T) * N <= stack_limit;
}

template<typename T, int N>
struct Buffer {
    // ...
};

template<typename T, int N>
void fct()
{
    static_assert(Stackable<T, N>(), "fct() buffer won't fit oon stack");
    Buffer<T, N> buf;
    // ...
}


// section 24.4.4 : constraints checks

// secgtion 24.4.5 : template definition checking
template<typename Iter, typename Val>
Iter find(Iter b, Iter e, Val x)
{
    static_assert(Input_iterator<Iter>(), "find() requires an input iterator");
    static_assert(Equality_comparable<Value_type<Iter>, Val>(), "find() a iterator and value arguments must match");
    while (b != e) {
        if (*b == x) {
            return b;
        }
        // note : not ++
        b = b + 1;
    }
    return b;
}


void f(list<int>& lst, vector<string>& vs)
{
    // error : list does not provide +
    auto p = find(lst.begin(), lst.end(), 1209);
    // ok : vector provide +
    auto q = find(vs.begin(), vs.end(), "Cambridge");
    // ....
}

// for checking find()
template<typename Val>
struct Forward {
    Forward();
    Forward(const Forward&);
    Forward operator=(const Forward&);
    bool operator==(const Forward&);
    bool operator!=(const Forward&);
    void operator++();
    // simplified does not handle a proxy for Val
    Val& operator*();
};

// simplified
template<typename Val>
using Value_type<Forward<Val>> = Val;

void f()
{
    Forward<int> p = find(Forward<int>{}, Forward<int>{}, 7);
}


