/**************************************************************
* Name     :  ex29-1-5.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年7月25日
**************************************************************/



/*
example 29.4 matrix implementation
*/


// section 29.4.1 : slice()
struct slice {
    slice() : start(-1), length(-1), stride(1) { }
    explicit slice(size_t s) : start(s), length(-1), stride(1) { }
    slice(size_t s, size_t l, size_t n = 1) : start(s), length(l), stride(n) { }
    size_t operator()(size_t i) const { return start + i * stride; }
    static slice all;
    // first index
    size_t start;
    // number of indices included (can be used for range checking)
    size_length;
    // distance between elements in sequence
    size_t stride;
};


// section 29.4.2 : matrix slices
template<size_t N>
struct Matrix_slice {
    // an empty matrix : no elements
    Matrix_slice() = default;
    // extents)
    Matrix_slice(size_t s, initializer_list<size_t> exts);
    // extents and strides
    Matrix_slice(size_t s, initializer_list<size_t> exts, initializer_list<size_t> strs);
    template<typename... Dims>
    // N extents
    Matrix_slice(Dims... dims);
    template<typename... Dims, typename = Enable_if<All(Convertible<Dims, size_t>()...)>>
    // calculate index from a set of subscripts
    size_t operator()(Dims... dims) const;

    // total number of elements
    size_t size;
    // stating offset
    size_t start;
    // number of elements in each dimension
    array<size_t, N> extents;
    // offsets between elements in each dimension
    array<size_t, N> strides;
};


template<size_t N>
template<typename... Dims>
size_t Matrix_slice<N>::operator()(Dims... dims) const
{
    static_assert(sizeof...(Dims) == N, "");
    // copy arguments into an array
    size_t args[N] {size_t(dims)...};
    return inner_product(args, args+N, strides.begin(), size_t(0));
}


// specialization for operator()
template<>
struct Matrix_slice<1> {
    // ...
    size_t operator()(size_t i) const
    {
        return i;
    }
    // ...
};

template<>
struct Matrix_slice<2> {
    // ...
    size_t operator()(size_t i, size_t j) const
    {
        return i * stides[0] + j;
    }
    // ...
};


// section 29.4.3 : matrix_ref
template<typename T, size_t N>
class Matrix_ref {
public :
    Matrix_ref(const Matrix_slice<N>& s, T* p) : desc{s}, ptr{p} { }
    // ... mostly like Matrix ...
private :
    // the shape of the matrix
    Matrix_slice<N> desc;
    // the first element in the matrix
    T* ptr;
};


Matrix_ref<double, 1> user()
{
    Matrix<double, 2> m = {{1, 2}, {3, 4}, {5, 6}};
    return m.row(1);
}

// trouble
auto mr = user();

template<typename T, size_t N>
class Matrix_base {
    // ... common stuff ...
};

template<typename T, size_t N>
class Matrix : public Matrix_base<T, N> {
    // ... special to Matrix ...
private :
    // the shape of the matrix
    Matrix_slice<N> desc;
    vector<T> elements;
};

template<typename T, size_t N>
class Matrix_ref : public Matrix_base<T, N> {
    // ... special to Matrix_ref ...
private :
    // the shape of the matrix
    Matrix_slice<N> desc;
    T* ptr;
};


// section 29.4.4 : matrix list initialization
template<typename T, size_t N>
using Matrix_initializer = typename Matrix_impl::Matrix_init<T, N>::type;

template<typename T, size_t N>
struct Matrix_init {
    using type = initializer_list<typename Matrix_init<T, N-1>::type>;
};

template<typename T>
struct Matrix_init<T, 1> {
    using type = initializer_list<T>;
};

template<typename T>
// undefined on purpose
struct Matrix_init<T,0>;


template<typename T, size_t N>
Matrix<T, N>::Matrix(Matrix_initializer<T,N> init)
{
    // deduce extents from initializer list
    Matrix_impl::derive_extents(init, desc.extents);
    // make room for slices
    elems.reserve(desc.size);
    // initialize from initializer list
    Matrix_impl::insert_flat(init, elems);
    assert(elems.size() == desc.size);
}

template<size_t N, typename List>
array<size_t, N> derive_extents(const List& list)
{
    array<size_t, N> a;
    auto f = a.begin();
    // put extents from list into f[]
    add_extents<N>(f, list);
    return a;
}

template<size_t N, typename I, typename List>
Enable_if<(N > 1), void> add_extents(I& first, const List& list)
{
    assert(check_non_jagged(list));
    *first = list.size();
    add_extent<N-1>(++first, *list.begin());
}

template<size_t N, typename I, typename List>
Enable_if<(N==1), void> add_extents(I& first, const List& list)
{
    // we reached the deepest nesting
    *first++ = list.size();
}

template<typename List>
bool check_non_jagged(const List& list)
{
    auto i = list.begin();
    for (auto j = i+1; j != list.end(); ++j) {
        if (i->size() != j->size()) {
            return false;
        }
    }
    return true;
}

template<typename T, typename Vec>
void insert_flat(initializer_list<T> list, Vec& vec)
{
    add_list(list.begin(), list.end(), vec);
}

// nested initializer_lists
template<typename T, typename Vec>
void add_list(const initializer_list<T>* first, const initializer_list<T>* last, Vec& vec)
{
    for ( ; first != last; ++first) {
        add_list(first->begin(), first->end(), vec);
    }
}

template<typename T, typename Vec>
void add_list(const T *first, const T *last, Vec& vec)
{
    vec.insert(vec.end(), first, last)
}


// section 29.4.5 : matrix access
template<typename T, size_t N>
Matrix_ref<T, N-1> Matrix<T, N>::row(size_t n)
{
    assert(n < rows());
    Matrix_slice<N-1> row;
    Matrix_impl::slice_dim<0>(n, desc, row);
    return {row, data()};
}

template<typename T>
T& Matrix<T,1>::row(size_t i)
{
    return &elems[i];
}

template<typename T>
T& Matrix<T, 0>::row(size_t n) = delete;


// select a column
template<typename T, size_t N>
Matrix_ref<T, N-1> Matrix<T, N>::comumn(size_t n)
{
    assert(n < cols());
    Matrix_slice<N-1> col;
    Matrix_impl::slice_dim<1>(n, desc, col);
    return {col, data()};
}


// subscripting with integers
template<typename T, size_t N>
template<typename... Args>
Enable_if<Matrix_impl::Requesting_elements<Args...>(), T&> Matrix<T, N>::operator()(Args... args)
{
    assert(Matrix_impl::check_dounds(desc, args...));
    return *(data() + desc(args...));
}

template<size_ t N, typename... Dims>
bool check_bounds(const Matrix_slice<N>& slice, Dims... dims)
{
    size_t indexes[N] {size_t(dims)...};
    return equal(indexes, indexes+N, slice.extents, less<size_t>());
}

template<typename... Args>
constexpr bool Requesting_element()
{
    return ALL(convertible<Args, size_t>()...);
}

constexpr bool All() { return true; }

template<typename... Args>
constexpr bool All(bool b, Args... args)
{
    return b && All(args...);
}

template<typename... Args>
constexpr bool Requesting_slice()
{
    return All((Convertible<Args, size_t>() || Same<Args, slice>())...) && Some(Same<Args, slice>()...);
}

// subscripting with slices
template<typename T, size_t N>
template<typename... Args>
Enable_if<Matrix_impl::Requesting_slice<Args...>(), Matrix_ref<T, N>> Matrix<T, N>::operator()(const Args&... args)
{
    Matrix_slice<N> d;
    d.start = Matrix_impl::do_slice(desc, d, args...);
    return {d, data{}};
}

template<size_t N, typename T, typename... Args>
size_t do_slice(const Matrix_slice<N>& os, Matrix_slice<N>& ns, const T& s, const Args&... args)
{
    size_t m = do_slice_dim<sizeof...(Args)+1>(os, ns, s);
    size_t n = do_slice(os, ns, args...);
    return m + n;
}

template<size_t N>
size_t do_slice(const Matrix_slice<N>& os, Matrix_slice<N>& ns)
{
    return 0;
}


// section 29.4.6 : Zero-Dimensional matrix
template<typename T>
class Matrix<T, 0> {
public :
    static constexpr size_t order = 0;
    using value_type = T;
    Matrix(const T& x) : elem(x) { }
    Matrix& operator=(const T& value)
    {
        elem = value;
        return *this;
    }
    T& operator()()
    {
        return elem;
    }
    const T& operator()() const
    {
        return elem;
    }

    operator T&()
    {
        return elem;
    }
    operator const T&()
    {
        return elem;
    }
private :
    T elem;
};

