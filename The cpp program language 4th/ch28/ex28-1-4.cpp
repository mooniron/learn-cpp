/**************************************************************
* Name     :  ex28-1-4.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年7月22日
**************************************************************/



/*
example 28.4 : conditional definition : enable_if
*/



template<typename T>
class Smart_pointer {
    // ...
    // return reference to whole object
    T& operator*();
    // select a member (for classes only)
    T* operator->();
    // ...
};

template<typename T>
class Smart_pointer {
    // ...
    // return reference to whole object
    T& operator*();
    // syntax error
    if (Is_class<T>()) {
        // select a member (for classes only)
        T* operator->();
    }
    // ...
};

template<typename T>
class Smart_pointer {
    // ...
    // return reference to whole object
    T& operator*();
    // select a member (for classes only)
    Enable_if<Is_class<T>(), T>* operator->();
    // ...
};

template<bool B, typename T>
using Enable_if = typename std::enable_if<B, T>::type;

template<typename T>
bool Is_class()
{
    return std::is_class<T>::value;
}


void f(Smart_pointer<double> p, Smart_pointer<complex<double>> q)
{
    // ok
    auto d0 = *p;
    // ok
    auto c0 = *q;
    // ok
    auto d1 = q->real();
    // error : p doesn't point to a class object
    auto d2 = p->real();
    //...
}


// section 28.4.1 : use of enable_if
template<typename T>
class vector<T> {
public :
    // n elements of type T with value val
    vector(size_t n, const T& val);
    // initialize from [b:e)
    template<typename Iter>
    vector(Iter b, Iter e);
    // ...
};

template<typename T>
class vector<T> {
public :
    // n elements of type T with value val
    vector(size_t n, const T& val);
    // initialize from [b:e)
    template<typename Iter, typename = Enable_if<Input_iterator<Iter>(), Iter>>
    vector(Iter b, Iter e);
    // ...
};

template<typename T>
class vector<T> {
public :
    // n elements of type T with value val
    vector(size_t n, const T& val);
    // initialize from [b:e)
    template<typename Iter>
    vector(Enable_if<Input_iterator<Iter>(), Iter>b, Iter e);
    // ...
};


// error : not a template
Enable_if<(version2_2_3 < config), M_struct>* make_default()
{
    return newMystruct{};
}

template<typename T>
void f(const T& x)
{
    // error : tmp is not a function
    Enable_if<(20 < sizeof<T>), T> tmp = x;
    // error : tmp is not a function
    Enable_if<(20 < sizeof<T>), T&> tmp = *new T{x};
    // ...
}


// section 28.4.2 : implementing Enable_if
template<bool B, typename T = void>
struct std::enable_if {
    typedef T type;
};

// no ::type if B == false
template<typename T>
struct std::enable_if<false, T> { };

template<bool B, typename T = void>
using Enable_if = typename std::enable_if<B, T>::type;


// section 28.4.3 : Enable_if and concepts
// optimized implementation
template<typename T>
Enable_if<Ordered<T>()> fct(T*, T*);

// nonoptimized implementation
template<typename T>
Enable_if<!Ordered<T>()> fct(T*, T*);

void f(vector<int>& vi, vector<complex<int>>& vc)
{
    if (vi.size() == 0 || vc.size() == 0) {
        throw runtime_error("bad fct arg");
    }
    // call optimized
    fct(&vi.front(), &vi.back());
    // call nonoptimized
    fct(&vc.front(), &vc.back());
}


// section 28.4.4 : more enable_if examples
// represent a failure to declare something
struct substitution_failure { };

//
template<typename T>
struct substitution_succeeded : std::true_type { };

template<>
struct substitution_succeeded<substitution_failure> : std::false_type { };

std::true_type::value == true
std::false_type::value == false

template<typename T>
struct has_f : substitution_succeded<typename get_f_result<T>::type> {};

template<typename T>
struct get_f_result {
private :
    template<typename X>
    // can call f(x)
    static auto check(const X& x) -> decltype(f(x));
    // can not call f(x)
    static substitution_failure check(...);
public :
    using type = decltype(check(std::declval<T>()));
};


template<typename T>
constexpr bool Has_f()
{
    return has_f<T>::value;
}

template<typename T>
class X {
    // ...
    Enable_if<Has_f<T>()> use_f(const T& t)
    {
        // ...
        f(t);
        // ...
    }
    // ...
};


template<typename Iter, typename Val>
Enable_if<Has_not_equals<Iter>(), Iter> find(Iter first, Iter last, Val v)
{
    while (first != last && !(*first == v)) {
        ++first;
    }
    return first;
}

template<typename Iter, typename Val>
Enable_if<!Has_not_equals<Iter>(), Iter> find(Iter first, Iter last, Val v)
{
    while (!(first == last) && !(*first == v)) {
        ++first;
    }
    return first;
}

template<typename T>
auto operator!=(const T& a, const T& b) -> decltype(!(a == b))
{
    return !(a == b);
}

