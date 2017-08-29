/**************************************************************
* Name     :  ex23-1-5.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年7月12日
**************************************************************/



/*
example 23.5 : function templates
*/


// declaration
template<typename T> void sort(vector<T>&)；

void f(vector<int>& vi, vector<string>& vs)
{
    // sort(vector<int>&)
    sort(vi);
    // sort(vector<string>&)
    sort(vs);
}

// definition
// shell sort
template<typename T>
void sort(vector<T>& v)
{
    const size_t n = v.size();
    for (int gap = n / 2; 0 < gap; gap /= 2) {
        for (int i = gap; i < n; i++) {
            for (int j = i - gap; 0 <= j; j -= gap) {
                if (v[j + gap] < v[j]) {
                    // swap v[j] and v[j + gap]
                    T temp = v[j];
                    v[j] = v[j + gap];
                    v[j + gap] = temp;
                }
            }
        }
    }
}


// definition
// Shell sort
template<typename T, typename Compare = std::less<T>>
void sort(vector<T>& v)
{
    // make a default Compare object
    Compare cmp;
    const size_t n = v.size();

    for (int gap = n / 2; 0 < gap; gap /= 2) {
        for (int i = gap; i < n; i++) {
            for (int j = i - gap; 0 <= j; j -= gap) {
                if (cmp(v[j+gap], v[j])) {
                    swap(v[j], v[j+gap]);
                }
            }
        }
    }
}


struct No_case {
    // compare case insensitive
    bool operator()(const string& a, const string& b) const;
};

void f(vector<int>& vi, vector<string>& vs)
{
    // sort(vector<int>&)
    sort(vi);
    // sort(vector<int>&) using greater
    sort<int, std::greater<int>>(vi);
    // sort(vector<str>&)
    sort(vs);
    // sort(vector<string>&) using No_case
    sort<string, No_case>(vs);
}


// section 23.5.1 : function template arguments
template<typename T, int max>
struct Buffer {
    T buf[max];
public :
    // ...
};

template<typename T, int max>
T& lookup(Buffer<T, max>& b, const char* p);

Record& f(buffer<string, 128>& buf, const char* p)
{
    // use the lookup() where T is string and i is 128
    return lookup(buf, p);
}


template<typename T1, typename T2>
pair<T1, T2> make_pair(T1 a, T2 b)
{
    return {a, b};
}

// x is a pair<int, int>
auto x = make_pair(1, 2);

// y is a pair<string, double>
auto y = make_pair(string("New York", 7.7));


// make a T and return a pointer to it
template<typename T>
T* creat();

void f()
{
    // class template argument int
    vector<int> v;
    // function template argument int
    int* p = create<int>();
    // error : can't deduce template argument
    int* q = create();
}


// section 23.5.2 function template argument deduction
template<typename T, typename U>
void f(const T*, U(*)(U));

int g(int);

void h(const char* p)
{
    // T is char, U is int
    f(p, g);
    // error : can't deduce U
    f(p, h);
}


template<typename T>
void f(T i, T* p);

void g(int i)
{
    // ok
    f(i, &i);
    // error, ambiguous : T is int or T is const char ?
    f(i, "Remember!");
}


// section 23.5.2.1 : reference deduction
template<typename T>
class Xref {
public :
    // store a pointer : Xref is the owned
    Xref(int i, T* p) : index {i}, elem {p}, owned {true} { }
    // store a pointer to r, owned by someone else
    Xref(int i, T& r) : index {i}, elem {&r}, owned {false} { }
    // move r into Xref, Xref is the owned
    Xref(int i, T&& r) : index {i}, elem {new T{move(r)}}, owned {true} { }
    // destructor
    ~Xref()
    {
        if (owned) {
            delete elem;
        }
    }
    // ....
private :
    int index;
    T* elem;
    bool owned;
};


string x {"There and back again"};
// r1 owns a copy of string{"Here"}
Xref<string> r1 {7, "Here"};
// r2 just refers to x
Xref<string> r2 {9, x};
// r3 owns the string{"There"}
Xref<string> r3 {3, new string{"There"}};


template<typename T>
T&& std::forward(typename remove_reference<T>::type& t) noexcept;
template<typename T>
T&& std::forward(typename remove_reference<T>::type&& t) noexcept;

// simple variant of make_shared
template<typename TT, typename A>
unique_ptr<TT> make_unique(int i, A&& a)
{
    return unique_ptr<TT> {new TT{i, forward<A>(a)}};
}

auto p1 = make_unique<Xref<string>>(7, "Here");
auto p2 = make_unique<Xref<string>>(9, x);


// section 23.5.3 : function template overloading
template<typename T>
T sqrt(T);
template<typename T>
complex<T> sqrt(complex<T>);
double sqrt(double);

void f(complex<double> x)
{
    // sqrt<int>(int)
    sqrt(2);
    // sqrt(double)
    sqrt(2.0);
    // sqrt<double>(complex<double>)
    sqrt(z);
}


template<typename T>
T max(T, T);

const int s = 7;

void k()
{
    // ok, max<int>(1, 2)
    max(1, 2);
    // max<char>('a', 'b')
    max('a', 'b');
    // max<double>(2.7, 4.9)
    max(2.7, 4.9);
    // max<const int>(s, 7)
    max(s, 7);
    // error : ambiguous
    max('a', 1);
    // error : ambiguous
    max(2.7, 4);
}


// section 23.5.3.1 : ambiguity resolution
void f()
{
    // max<int>(int('a'), 1)
    max<int>('a', 1);
    // max<double>(2.7, double(4))
    max<double>(2.7, 4);
}


inline int max(int i, int j)
{
    return max<int>(i, j);
}

inline double max(int i, double d)
{
    return max<double>(i, d);
}

inline double max(double d, int i)
{
    return max<double>(d, i);
}

inline double max(double d1, double d2)
{
    return max<double>(d1, d2);
}

void g()
{
    // max(int('a'), 1)
    max('a', 1);
    // max(double, int)
    max(2.7, 4);
}


// section argument substitution failure
template<typename Iter>
typename Iter::value_type mean(Iter first, Iter last);

void  f(vector<int>& v, int* p, int n)
{
    // ok
    auto x = mean(v.begin(), v.end());
    // error
    auto y = mean(p, p + n)
}

// #1
template<typename Iter>
typename Iter::value_type mean(Iter first, Iter last);
// #2
template<typename T>
T mean(T*, T*);

void  f(vector<int>& v, int* p, int n)
{
    // ok, #1
    auto x = mean(v.begin(), v.end());
    // ok, #2
    auto y = mean(p, p + n)
}


// #1
template<typename Iter>
typename Iter mean(Iter first, Iter last)
{
    typename Iter::value_type = *first;
    // ...
}

// #2
template<typename T>
T* mean(T*, T*);

void f(vector<int>& v, int* p, int n)
{
    // ok : call #1
    auto x = mean(v.begin(), v.end());
    // error : ambiguous
    auto y = mean(p, p + n);
}


// section 23.5.3.3 : overloading and derivation
template<typename T>
class B { /* ... */ };
template<typename T>
class D : public B<T> { /* ... */ };
template<typename T>
void f(B<T>*);

void g(B<int>* pb, D<int>* pd)
{
    // f<int>(pb) of course
    f(pb);
    // f<int>(static_cast<B<int>*>(pd))
    // standard conversion D<int>* to B<int>* used
    f(pd);
    // ...
}


// section 23.5.3.4 : overloading and non-deduced parameters
// get the nth element
template<typename T, typename C>
T get_nth(C& p, int n);

struct Index {
    operator int();
    // ...
};

void f(vector<int>& v, short s, Index i)
{
    // exact match
    int i1 = get_nth<int>(v, 2);
    // standard conversion short to int
    int i2 = get_nth<int>(v, s);
    // user-defined conversion  Index to int
    int i3 = get_nth<int>(v, i);
}


