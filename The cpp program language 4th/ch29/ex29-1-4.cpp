/**************************************************************
* Name     :  ex29-1-4.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年7月25日
**************************************************************/



/*
example Matrix arithmetic operations
*/


// 2-by-3
Matrix<int, 2> mi {
    {1, 2, 3},
    {4, 5, 6}
};
// copy
Matrix<int, 2> m2 {mi};
// scale
mi *= 2;
// add
Matrix<int, 2> m3 = mi + m2;
//
Matrix<int, 2> m4 {
    {1, 2},
    {3, 4},
    {5, 6}
};
// multiply {{18, 24, 30}, {38, 52, 66}, {58, 80, 102}} ?
Matrix<int, 1> v = mi * m4;


template<typename T, size_t N>
class Matrix {
    // ...

    template<typename F>
    Matrix& apply(F f);

    template<typename M, typename F>
    Matrix& apply(const M& m, F f);

    Matrix& operator=(const T& value);

    Matrix& operator+=(const T& value);
    Matrix& operator−=(const T& value);
    Matrix& operator*=(const T& value);
    Matrix& operator/=(const T& value);
    Matrix& operator%=(const T& value);

    template<typename M>
    Matrix& operator+=(const M& x);
    template<typename M>
    Matrix& operator-=(const M& x);

    // ...
};


// section 29.3.1 : scalar operations
template<typename T, size_t N>
Matrix<T, N>& Matrix<T, N>::operator+=(const T& val)
{
    return apply([&](T& a){ return a += val; });
}

template<typename T, size_t N>
template<typename F>
Matrix<T, N>& Matrix<T, N>::apply(F f)
{
    for (auto& x : elems) {
        f(x);
    }
    return *this;
}

m.apply(abs).apply(sqrt);

template<typename T, size_t N>
Matrix<T, N> operator+(const Matrix<T, N>& m, const T& val)
{
    Matrix<T, N> res = m;
    res += val;
    return res;
}


// section 29.3.2 : addition
template<typename T, size_t N>
template<typename M>
Enable_if(Matrix_type<M>(), Matrix<T, N>&) Matrix<T, N>::operator+=(const M& m)
{
    static_assert(m.order() == N, "+=: mismatched Matrix dimensions");
    // make sure sizes match
    assert(same_extents(desc, m.descriptor()));
    return apply(m, [](T& a, Value_type<M>&b) { return a+=b; });
}

template<typename T, size_t N>
template<typename M, typename F>
Enable_if<Matrix_type<M>(), Matrix<T, N>&> Matrix<T, N>::apply(M& m, F f)
{
    // make sure sizes match
    assert(same_extents(desc, m.descriptor()));
    for (auto i = begin(), j = m.begin(); i != end(); ++i, ++j) {
        f(*i, *j);
    }
    return *this;
}

template<typename T, size_t N>
Matrix<T, N> operator+(const Matrix<T, N>& a, const Matrix<T, N>& b)
{
    Matrix<T, N> res = a;
    res += b;
    return res;
}

// general version
template<typename T,typename T2, size_t N, typename RT = Matrix<Common_type<Value_type<T>, Value_type<T2>>, N>>
Matrix<RT, N> operator+(const Matrix<T, N>& a, const Matrix<T2, N>& b)
{
    Matrix<RT, N> res = a;
    res += b;
    return res;
}


template<>
struct common_type<Quad, long double>
{
    using type = Quad;
}

template<typename T, size_t N>
Matrix<T, N> operator+(const Matrix_ref<T, N>& x, const T& n)
{
    Matrix<T, N> res = x;
    res += n;
    return res;
}


// section 29.3.3 : multiplication
template<typename T>
Matrix<T, 2> operator*(const Matrix<T, 1>& u, const Matrix<T, 1>& v)
{
    const size_t n = u.extent(0);
    const size_t m = v.extent(0);
    // an n-by-m matrix
    Matrix<T, 2> res(n, m);
    for (size_t i = 0; i != n; ++i) {
        for (size_t j = 0; j != m; ++j) {
            res(i, j) = u[i] * v[j];
        }
    }
    return res;
}

template<typename T>
Matrix<T, 1> operator*(const Matrix<T, 2>& m, const Matrix<T, 1>& v)
{
    assert(m.extent(1) == v.extent(0));
    const size_t n = m.extent(0);
    Matrix<T, 1> res(n);
    for (size_t i = 0; i != n; ++ i) {
        for (size_t j = 0; j != n; ++j) {
            res(i) += m(i, j) * v(j);
        }
    }
    return res;
}

// N-M * M-P = N-P
template<typename T>
Matrix<T, 2> operator*(const Matrix<T, 2>& m1, const Matrix<T, 2>& m2)
{
    const size_t n = m1.extent(0);
    const size_t m = m1.extent(1);
    // columns must match rows
    assert(m == m2.extent(0));
    const size_t p = m2.extent(1);
    Matrix<T, 2> res(n, p);
    for (size_t i = 0; i !=n; ++i) {
        for (size_t j = 0; j != p; ++j) {
            // == res(i, j) = dot_product(m1[i], m2.column(j));
            for (size_t k = 0; k != m; ++k) {
                res(i, j) = m1(i, k) * m2(k, j);
            }
        }
    }
    return res;
}

template<typename T>
T dot_product(const Matrix_ref<T, 1>& a, const Matrix_ref<T, 1>& b)
{
    return inner_product(a.begin(), a.end(), b.begin(), 0.0);
}

