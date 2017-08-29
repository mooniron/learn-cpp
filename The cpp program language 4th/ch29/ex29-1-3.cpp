/**************************************************************
* Name     :  ex29-1-3.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年7月25日
**************************************************************/



/*
example 29.2 : a matrix template
*/



template<typename T, size_t N>
class Matrix {
public :
    static constexpr size_t order = N;
    using value_type = T;
    using iterator = typename std::vector<T>::iterator;
    using const_iterator = typename std::vector<T>::const_iterator;

    Matrix() = default;
    // move
    Matrix(Matrix&&) = default;
    Matrix& operator=(Matrix&&) = default;
    // copy
    Matrix(const Matrix&) = default;
    Matrix& operator=(Matrix const&) = default;
    ~Matrix() = default;
    // construct from Matrix_ref
    template<typename U>
    Matrix(const Matrix_ref<U, N>&);
    // assign from Matrix_ref
    template<typename U>
    Matrix& operator=(const Matrix_ref<U, N>&);
    // specify the extents
    template<typename... Exts>
    explicit Matrix(Exts exts);
    // initialize fromlist
    Matrix(Matrix_initializer<T, N>);
    // assign from list
    Matrix& operator=(Matrix_initializer<T, N>);
    // don't use {} except for elements
    template<typename U>
    Matrix(initializer_list<U>) = delete;
    template<typename U>
    Matrix& operator=(initializer_list<U>) = delete;

    // number of dimensions
    static constexpr size_t order() { return N; }
    // #elements in the nth dimension
    size_t extent(size_t n) const { return desc.extents[n]; }
    // total number of elements
    size_t size() const { return elems.size(); }
    // the slice defining subscripting
    const Matrix_slice<N>& descriptor() const { return desc; }

    // "flat" element access
    T* data() { return elems.data(); }
    const T* data() const { return elems.data(); }
    // ...
private :
    // slice defining extents int the N dimensions
    Matrix_slice<N> desc;
    // the elements
    vector<T> elems;
};


// section 29.2.1 : construction and assignment
template<typename T, size_t N>
template<typename... Exts>
Matrix<T, N>::Matrix(Exts... exts)
    // copy extents
    : desc{exts...},
    // allocate desc.size elements and default initialize them
    elems(desc.size)
{
}

template<typename T, size_t N>
Matrix<T, N>::Matrix(Matrix_initializer<T, N>& init)
{
    // deduce extents from initializer list
    Matrix_impl::derive_extents(init, desc.extents);
    // make room for slices
    elems.reserve(desc.size);
    // initialize from initializer list
    Matrix_impl::insert_flat(init, elems);
    assert(elems.size() == desc.size);
}

enum class Piece { none, cross, naught };

Matrix<Piece,2> board1 {
{Piece::none, Piece::none , Piece::none},
{Piece::none, Piece::none , Piece::none},
{Piece::none, Piece::none ,Piece::cross}

};
Matrix<Piece,2> board2(3,3); // OK
Matrix<Piece,2> board3 {3,3}; // error : constr uctor from initializer_list<int> deleted


template<typename T, size_t N>
template<typename U>
Matrix<T, N>::Matrix(const Matrix_ref<U, N>& x)
    // copy desc and elements
    : desc{x.desc}, elems{x.begin(), x.end()}
{
    static_assert(Convertible<U, T>(), "Matrix constructor: incompatible element types");
}

template<typename T, size_t N>
template<typename U>
Matrix<T, N>& Matrix<T, N>::operator=(const Matrix_ref<U, N>& x)
{
    static_assert(Convertible<U, T>(), "Matrix =: incompatible element types");
    desc = x.desc;
    elems.assign(x.begin(), x.end());
    return *this;
}


// section 29.2.2 : subscripting and slicing
template<typename T, size_t N>
class Matrix {
public :
    // ...
    template<typename... Args>    // m(i,j,k) subscripting with integers
    Enable_if<Matrix_impl::Requesting_element<Args...>(), T&>
    operator()(Args... args);

    template<typename... Args>
    Enable_if<Matrix_impl::Requesting_element<Args...>(), const T&>
    operator()(Args... args) const;

    template<typename... Args>    // m(s1,s2,s3) subscripting with slices
    Enable_if<Matrix_impl::Requesting_slice<Args...>(), Matrix_ref<T, N>>
    operator()(const Args&... args);

    template<typename... Args>
    Enable_if<Matrix_impl::Requesting_slice<Args...>(), Matrix_ref<const T,N>>
    operator()(const Args&... args) const;

    Matrix_ref<T,N−1> operator[](size_t i) { return row(i); }   // m[i] row access
    Matrix_ref<const T,N−1> operator[](size_t i) const { return row(i); }

    Matrix_ref<T,N−1> row(size_t n);    // row access
    Matrix_ref<const T,N−1> row(size_t n) const;

    Matrix_ref<T,N−1> col(size_t n);    // column access
    Matrix_ref<const T,N−1> col(size_t n) const;

    // ...
};


template<typename T, size_t N>
Matrix_ref<T, N-1> Matrix<T, N>::operator[](size_t n)
{
    return row(n);
}


Matrix<int> m3 {
    {01, 02, 03},
    {11, 12, 13},
    {21, 22, 23}
};

// m31 becomes {{12}, {22}}
auto m31 = m(slice{1, 2}, 1);
// m32 becomes : {11}, {21}
auto m32 = m(slice{1, 2}, 0);
// x = 13
auto x = m(1, 2);

