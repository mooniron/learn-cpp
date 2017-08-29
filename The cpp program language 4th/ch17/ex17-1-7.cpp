/**************************************************************
* Name     :  ex17-1-7.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年6月10日
**************************************************************/



/*
example 17-5 : copy and move
    section 17.5.2 : move
*/


// section 17.5.2 : move
// bad implementation : copy
template<class T>
void swap(T& a, T& b)
{
    // put a copy of a into tmp
    const T tmp = a;
    // put a copy of b into a
    a = b;
    // put a copy of tmp into b
    b = tmp;
}


// two dimensional Matrix
template<class T>
class Matrix {
    std::array<int, 2> dim;
    // pointer to sz elements of type T
    T* elem;

    Matrix(int d1, int d2) : dim {d1, d2}, elem {new T[d1 * d2]} { }
    int size() const { return dim[0] * dim[1]; }
    // copy constructor
    Matrix(const Matrix&);
    // move constructor
    Matrix(Matrix&&);
    // copy assignment
    Matrix& operator=(const Matrix&);
    // move assignment
    Matrix& operator=(Matrix&&);
    // destructor
    ~Matrix();
    // ...
};

// move constructor
template<class T>
Matrix<T>::Matrix(Matrix&& a)
    // grab a's representation
    : dim {a.dim}, elem {a.elem}
{
    // clear a 's representation
    a.dim = {0, 0};
    a.elem = nullptr;
}

// move assignment
template<class T>
Matrix<T>& Matrix<T>::operator=(Matrix&& a)
{
    // swap representations
    swap(dim, a.dim);
    swap(elem, a.elem);
    return *this;
}


// "perfect swap"
template<class T>
void swap(T& a, T& b)
{
    T tmp = std::move(a);
    a = std::move(b);
    b = std::move(tmp);
}

// res[i][j] = a[i][j] + b[i][j] for each i and j
Matrix operator+(const Matrix& a, const Matrix& b)
{
    if (a.dim[0] != b.dim[0] || a.dim[1] != b.dim[1]) {
        throw std::runtime_error("unequal Matrix sizes in +");
    }

    Matrix res {a.dim[0], a.dim[1]};
    constexpr auto n = a.size();
    for (int i = 0; i!= n; ++i) {
        res.elem[i] = a.elem[i] + b.elem[i];
    }
    return res;
}

// beware!
Matrix& operator+(const Matrix& a, const Matrix& b)
{
    // allocate on free store
    Matrix& res = *new Matrix;
    // res[i][j] = a[i][j] + b[i][j] for each i and j
    return res;
}
