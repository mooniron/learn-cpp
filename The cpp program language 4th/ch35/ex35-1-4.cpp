/**************************************************************
* Name     :  ex35-1-4.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年8月9日
**************************************************************/



/*
example 35.4: type functions
*/



// section 35.4.1: type traits
class X {
public:
    void inside();
private:
    X& operator=(const X&);
    ~X();
};

void X::inside()
{
    cout << "inside =: " << is_copy_assignable<X>::value << '\n';
    cout << "inside ~: " << is_destructible<X>::value << '\n';
}

void outside()
{
    cout << "outside =: " << is_copy_assignable<X>::value << '\n';
    cout << "outside ~: " << is_destructible<X>::value << '\n';
}

// destructor for a container Cont
template<typename T>
Cont::~Cont()
{
    if (!Is_trivially_destructible<T>()) {
        for (T* p = elem; p != p + sz; ++p) {
            p->~T();
        }
    }
}


template<typename T>
void f(T a)
{
    static_assert(Is_array<T>(), "f(): not an array");
    // the number of elements in the 2nd dimension (zero based)
    constexpr int dn {Extent<a, 2>()};
    //  ...
}

template<typename T>
void draw(T t)
{
    static_assert(Is_same<Shape*, T>() || Is_base_of<Shape*, Remove_pointer<T>>(), "");
    t->draw();
}


// section 35.4.2: type generators
template<typename K, typename V>
class My_map {
    pair<typename add_const<K>::type, V> default_node;
    // ...
};

template<typename T>
using Add_const = typename add_const<T>::type;

template<typename T>
void f(T v)
{
    // copy of v
    Remove_reference<T> x = v;
    // maybe copy of v; maybe a reference to x
    T y = v;
    // increment local variable
    ++x;
    ++y;
    // ...
}

void user()
{
    int val = 7;
    // call f<int&>(): the ++y in f() will increment val
    f(val);
    // call f<int>(): the ++y in f will increment a local cop0y
    f(7);
}

int a[10][20];
// an array[10]
Remove_extent<decltype(a)> a10;
// an int
Remove_all_extents<decltype(a)> i;


template<typename T>
void f(T x)
{
    Add_pointr<T> p = new Remove_reference<T>{};
    // would not work if T is a reference
    T* p = new T{};
    // ...
}


template<std::size_t N, std::size_t A>
struct aligned_storage {
    using type = struct {
        // N chars aligned to A
        allignas(A) unsigned char data[N];
    };
};

template<typename... T>
struct common_type;

template<typename T>
struct common_type<T> {
    using type = T;
};

template<typename T, typename U>
struct common_type<T, U> {
    using type = decltype(true ? declval<T>() : declval<U>());
};

template<typename T, typename U, typename... V>
struct common_type<T, U, V...> {
    using type = typename common_type<typename common_type<T, U>::type, V...>::type;
};

template<typename T, typename U>
using Common_type = typename common_type<T, U>::type;

// x1 is a double
Common_type<int, double> x1;
// error: no common type
Common_type<int, string> x2;
// x3 is a long long
Common_type<int, short, long, long long> x3;
// x4 is a Shape*
Common_type<Shape*, Circle*> x4;
// x5 is a void*
Common_type<void*, double*, Shape*> x5;

// function
int ff(int)
{
    return 2;
}

// pointer to function
typedef bool (*PF)(int);

// function object
struct Fct {
    // ...
    double operator()(string);
    string operator()(int, int);
};

// lambda
auto fx = [](char ch) { return tolower(ch); }

// r1 is a int
Result_of<decltype(&ff)(int)> r1 = 7;
// r2 is a bool
Result_of<PF(int)> r2 = true;
// r3 is  a double
Result_of<Fct(string)> r3 = 9.9;
// r4 is a string
Result_of<Fct(int, int)> r4 = "Hero";
// r5 is a char
Result_of<decltype(fx)(char)> r5 = 'a';

// function
int f();
string f(int);
// error: no overload resolution for pointer to function
Result_of<decltype(&f)()> r1 = 7;

// error: no argument specification,
// and ff is function rather than a type
Result_of<ff> r1 = 7;
// error: the argument to Result_of must be a type
Result_of<ff()> r1 = 7;
// error: decltype(f) is a function type
// rather than a pointer to function type
Result_of<decltype(f)()> r2 = 7;
// ok: r3 is an int
Result_of<decltype(f)*()> r3 = 7;

template<typename F, typename A>
auto temp(F f, A a) -> Result_of<F(A)>
{
    // ...
}

void f4()
{
    temp(ff, 1);
    temp(fx, 'a');
    temp(Fct(), "Ulysses");
}


template<typename T, size_t N>
void array<T, N>::swap(array& y) noexcept(noexcept(swap(declval<T&>(), declval<T&>())))
{
    for (int i = 0; i < a.size(); ++i) {
        swap((*this)[i], a[i]);
    }
}


