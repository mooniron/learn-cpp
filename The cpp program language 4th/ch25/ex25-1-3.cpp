/**************************************************************
* Name     :  ex25-1-3.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年7月17日
**************************************************************/



/*
example 25.3 : specialization
*/


// general vector type
template<typename T>
class Vector {
    T* v;
    int sz;
public :
    Vector();
    explicit Vector(int);
    T& elem(int i)
    {
        return v[i];
    }
    T& operator[](int i);
    void swap(Vector&);
    // ...
};

Vector<int>vi;
Vector<Shape*> vps;
Vector<string> vs;
Vector<char*> vpc;
Vector<Node*> vpn;

// complete specialization
template<>
class Vector<void*> {
    void** p;
    // ...
    void*& operator[](int i);
};

Vector<void*> vpv;

// partial specialization
template<typename T>
class Vector<T*> : private Vector<void*> {
public :
    using Base = Vector<void*>;
    Vector() { }
    explicit Vector(int i) : Base(i) { }
    T*& elem(int i) { return reinterpret_cast<T*&>(Base::elem(i)); }
    T*& operator[](int i)
    {
        return reinterpret_cast<T*&>(Base::operator[](i));
    }

    // ...
};

// <T*> is <Shape*> so T is Shape
Vector<Shape*> vps;
// <T*> is <int**> so T is int*
Vector<int**> vppi;


// section 25.3.1 : interface specialization
template<typename T>
class complex {
public :
    complex(const T& re = T{}, const T& im = T{});
    // copy constructor
    complex(const complex&);
    template<typename X>
    // conversion from complex<X> to complex<T>
    complex(const complex<X>&);
    complex& operator=(const complex&);
    complex<T>& operator=(const T&);
    complex<T>& operator+=(const T&);
    // ...
    template<typename X>
    complex<T>& operator=(const complex<X>&);
    template<typename X>
    complex<T>& operator+=(const complex<X>&);
    // ...
};

template<>
class complex<float> {
public :
    // ...
    complex<float>& operator=(float);
    complex<float>& operator+=(float);
    // ...
    complex<float>& operator=(const complex<float>&);
    // ...
};

template<>
class complex<double> {
public :
    constexpr complex(double re = 0.0, double im = 0.0);
    constexpr complex(const complex<float>&);
    explicit constexpr complex(const complex<long double>&);
    // ...
};


// section 25.3.1.1 : implementation specialization
// N-dimensional Matrix of Ts
template<typename T, int N>
class Matrix;

// specialization for N == 0
template<typename T, 0>
class Matrix {
    T val;
    // ...
};

// specialization for N = 1
template<typename T, 1>
class Matrix {
    T* elem;
    // number of elements
    int sz;
    // ...
};

// specialization for N = 2
template<typename T, 2>
class Matrix {
    T* elem;
    // number of rows
    int dim1;
    // number of columns
    int dim2;
    // ...
};


// section 25.3.2 : the primary template
template<typename T>
class List<T*> {
    // ...
};

// error : primary template after specialization
template<typename T>
class List {
    // ...
};

template<typename T>
class List {
    static_assert(Regular<T>(), "List<T> : T must be Regular");
    // ...
};

// not a definition
template<typename T>
class List;

template<typename T>
class List<T*> {
    // ...
};


template<typename T>
class List {
    // ...
};

List<int*> li;

// error : specialization used before defined
template<typename T>
class List<T*> {
    // ...
};


// section 25.3.3 : order of specialization
// general the primary template
template<typename T>
class Vector;

// specialized for any pointer
template<typename T>
class Vector<T*>;

// specialized for void*
template<>
class Vector<void*>;


// section 25.3.4 : function template specialization

// section 25.3.4.1 : specialization and overloading
template<typename T>
bool less(T a, T b)
{
    return a < b;
}

template<typename T>
void sort(Vector<T>& v)
{
    const size_t n = v.size();

    for (int gap = n / 2; 0 < gap; gap /= 2) {
        for (int i = gap; i != n; ++i) {
            for (int j = i - gap; 0 <= j; j -= gap) {
                if (less(v[j + gap], v[j])) {
                    swap(v[j], v[j + gap]);
                }
            }
        }
    }
}

template<>
bool less<const char*>(const char* a, const char* b)
{
    return strcmp(a, b) < 0;
}

template<>
bool less<>(const char* a, const char* b)
{
    return strcmp(a, b) < 0;
}

template<>
bool less(const char* a, const char* b)
{
    return strcmp(a, b) < 0;
}

bool less(const char* a, const char* b)
{
    return strcmp(a, b) < 0;
}


// section 25.3.4.2 : specialization : that is not overloading
// no definition
template<typename T>
T max_value();

template<>
constexpr int max_value<int>()
{
    return INT_MAX;
}

template<>
constexpr char max_value<char>()
{
    return CHAR_MAX;
}

template<typename Iter>
Iter my_algo(Iter p)
{
    // works for types with specialized max_value()
    auto x = max_value<Value_type<Iter>>();
}

int max2(int)
{
    return INT_MAX;
}

char max2(char)
{
    return CHAR_MAX;
}

template<typename Iter>
Iter my_algo2(Iter p)
{
    // works for the types for which we overload max2()
    auto x = max2(Value_type<Iter>());
    // ...
}

