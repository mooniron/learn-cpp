/**************************************************************
* Name     :  ex40-1-5.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年8月22日
**************************************************************/



/*
example 40.5: numerical array: valarray
*/


// section 40.5.1: constructors and assignments
valarray<double> v0;    // placeholder we can assign to v0 later
// 1000 elements with 0.0F
valarray<float> v1(1000);
// 2000 elements with value -1
valarray<int> v2(-1, 2000);
// bad mistake: floating-point valarray size
valarray<double> v3(100, 9, 8064);
// v4 has v3.size() elements
valarray<double> v4 = v3;
// two elements
valarray<int> v5 {-1, 2000};

void f(const int* p, int n)
{
    const double vd[] = {0, 1, 2, 3, 4};
    const int vi[] = {0, 1, 2, 3, 4};
    // 4 elements: 0, 1, 2, 3
    valarray<double> v1 {vd, 4};
    // type error: vi is not pointer to double
    valarray<double> v2 {vi, 4};
    // undefined too few elements in initializer
    valarray<double> v3 {vd, 8};
    // p had better point to at least n ints;
    valarray<int> v4 {p, n};
}

valarray<int> v {1, 2, 3, 4, 5, 6, 7, 8};
// v == {2, 4, 6, 8, 10, 12, 14, 16}
v *= 2;
// v == {7, 7, 7, 7, 7, 7, 7, 7}
v = 7;


// section 40.5.2: subscripting
valarray<T> operator[](slice) const;
// ...
const valarray<char> v0 {"abcdefghijklmnop", 16};
// {"cfilo", 5}
valarray<char> v1 {v0[slice(2, 5, 3)]};

valarray<char> v0 {"abcdefghijklmnop", 16};
valarray<char>  v1 {"ABCDE", 5};
v0[slice(2, 5, 3)] = v1;

const valarray<char> v0 {"abcdefghijklmnop", 16};
const valarray<size_t> len {2, 3};
const valarray<size_t> str {7, 2};
// v1 == {"dfhkmo", 6}
valarray<char> v1 {v0[gslice(3, len, str)]};

const valarray<char> v0 {"abcdefghijklmnop", 16};
const size_t vi[] {7, 5, 2, 3, 8};
// v1 == {"hfcdi", 5}
valarray<char> v1 {v0[valarray<size_t>(vi, 5)]};


// section 40.5.3: operations
void f(valarray<double>& v, valarray<double>& v2, double d)
{
    // v3[i] = v[i] * v2[i] for vall i
    valarray<double> v3 = v * v2;
    valarray<double> v4 = v * d;
    valarray<double> v5 = d * v2;
    valarray<double> v6 = cos(v);
}

double incr(double d)
{
    return d + 1;
}

void f(valarray<double>& v)
{
    // produce a new valarray
    valarray<double> v2 = v.apply(incr);
}

void f()
{
    int alpha[] = {1, 2, 3, 4, 5, 6, 7, 8};
    valarray<int> v(alpha, 8);
    // 3, 4, 5, 6, 7, 8, 0, 0
    valarray<int> v2 = v.shift(2);
    // 4, 8, 12, 16, 20, 24, 28, 32
    valarray<int> v3 = v << 2;
    // 0, 0, 1, 2, 3, 4, 5, 6
    valarray<int> v4 = v.shift(-2);
    // 0, 0 ,0 ,1, 1, 1, 1, 2
    valarray<int> v5 = v >> 2;
    // 3, 4, 5, 6, 7, 8, 1, 2
    valarray<int> v6 = v.cshift(2);
    // 7, 8, 1, 2, 3, 4, 5, 6
    valarray<int> v7 = v.cshift(-2);
}

void f(valarray<int> vi, alarray<double> vd)
{
    // vi[i] <<= 2 for all elements of vi
    vi <<= 2;
    // error: not defined for floating-point values
    vd <<= 2;
}


// section 40.5.4: slices
// starting index, a length, and a stride
class std::slice {
public:
    slice();    // slice{0, 0, 0}
    slice(size_t start, size_t size, size_t stride);
    size_t start() const;
    size_t size() const;
    size_t stride() const;
};

valarray<int> v {
    {00, 01, 02, 03},
    {10, 11, 12, 13},
    {20, 21, 22, 23}
};

for (int x : v) {
    cout << x << ' ';
}

template<typename T>
class Slice_iter {
    valarray<T>* v;
    slice s;
    // index of current element
    size_t curr;
    T& ref(size_t i) const
    {
        return (*v)[s.start() + i * s.stride()];
    }
public:
    Slice_iter(valarray<T>* vv, slice ss, size_t pos = 0) : v{vv}, s{ss}, curr{pos} { }
    Slice_iter end() const { return {this, s, s.size()}; }
    Slice_iter& operator++() {
        ++curr;
        return *this;
    }
    Slice_iter operator++(int)
    {
        Slice_iter t = *this;
        ++curr;
        return t;
    }
    T& operator[](size_t i)
    {
        return ref(i);
    }
    // Fortran-style subscript
    T& operator()(size_t i)
    {
        return ref(i);
    }
    T& operator*()
    {
        return ref(curr);
    }
    bool operator==(const Slice_iter& q) const
    {
        return curr == q.curr && s.stride() == q.s.stride() && s.start() == q.s.start();
    }
    bool operator!=(const Slice_iter& q) const
    {
        return !(*this == q);
    }
    bool operator<(const Slice_iterator& q) const
    {
        return curr < q.curr && s.stride() == q.s.stride() && s.start() == q.s.start();
    }
};


// section 40.5.5: slice_array
void f(valarray<double>& d)
{
    slice_array<double>& v_even = d[slice(0, d.size()/2+d.size()%2, 2)];
    slice_array<double>& v_odd = d[slice(1, d.size()/2, 2)];
    // multiply element pairs and store results in even elements
    v_even *= v_odd;
    // assign 0 to every odd element of d
    v_odd = 0;
}

slice_array<double> row(valarray<double>& d, int i)
{
    slice_array<double> v = d[slice(0, 2,d.size()/2)];
    // ...
    return d[slice(i%2, i, d.size()/2)];
}


// section generalized slices
// instead of 1 stride and one size like slice, gslice holds n strides and n sizes
class std::gslice {
public:
    gslice();
    gslice(size_t sz, const valarray<size_t>& lengths, const valarray<size_t>& strides);
    // index of first element
    size_t start() const;
    valarray<size_t> size() const;
    // stride for index[0], index[1], ...
    valarray<size_t> stride() const;
};

// max (i, j) to their corresponding index
size_t gslice_index(const gslice& s, size_t i, size_t j)
{
    return s.start() + i * s.stride()[0] + j *s.stride()[1];
}
// 2 elements in the first dimension
// 3 elements in the second dimension
valarray<size_t> lengths {2, 3};
// 3 is the stride for the first index
// 1 is the stride for the second index
valarray<size_t> strides {3, 1};

void f()
{
    gslice s(0, lengths, strides);
    // for each row
    for (int i -= 0; i < 3; ++i) {
        // for  each element in row
        for (int j = 0; j < 2; ++j) {
            cout << "(" << i << ", " << j << ")->" << glice_index(s, i, j) << "; ";
        }
    }
}

void f(valarray<float>& v)
{
    gslice m(0, lengths, strides);
    // assign 0 to v[0], v[1], v[3], v[4], v[6], v[7]
    v[m] = 0;
}

