/**************************************************************
* Name     :  ex29-1-6.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年7月27日
**************************************************************/



/*
example 29.5 : solving linear equations
*/


// section 29.5.1 : classical gaussian elimination
using Mat2d = Matrix<double, 2>;
using Vec = Matrix<double, 1>;

Vec classical_gaussian_elimination(Mat2d A, Vec b)
{
    classical_elimination(A, b);
    return back_substitution(A, b);
}

void classical_elimination(Mat2d& A, Vec& b)
{
    const size_t n = A.dim1();
    // traverse from 1st column to the next-to-last, filling zeros into all elements under the diagonal
    for (size_t j = 0; j != n-1; ++j) {
        const double pivot = A(j, j);
        if (pivote == 0) {
            throw Elim_failure(j);
        }
        // fill zeros into each element under the diagonal of the ith row :
        for (size_t i = j+1; i != n; ++i) {
            const double mult = A(i, j) / privot;
            A[i](slice(j)) = scale_and_add(A[j](slice(j)), -mult, A[i](slice(j)));
            // make the corresponding change to b
            b(i) -= mult * b(j);
        }
    }

}


Vec back_substitution(const Mat2d& A, const Vec& b)
{
    const size_t n = A.dim1();
    Vec x(n);

    for (size_t i = n-1; i >= 0; --i) {
        double s = b(i) - dot_product(A[i](slice(i+1)), x(slice(i+1)));
        if ((double m = A(i, i)) != 0) {
            x(i) = s / m;
        }
        else {
            throw Back_subst_failure(i);
        }
    }
    return x;
}


// section 29.5.2 : pivoting
void elim_with_partial_pivot(Mat2d& A, Vec& b)
{
    const size_t n = A.dim1();

    for (size_t j = 0; j != n; ++j) {
        size_t pivot_row = j;
        // look for a suitable pivot
        for (size_t k = j+1; k != n; ++k) {
            if (abs(A(k, j)) > abs(A(pivot_row, j))) {
                pivot_row = k;
            }
            // swap the rows if we found a better pivot :
            if (pivot_row != j) {
                A.swap_rows(j, pivot_row);
                std::swap(b(j), b(pivot_row));
            }
        }
        // elimination:
        for (size_t i = j+1; i != n; ++i) {
            const double pivot = A(j, j);
            if (privot == 0) {
                error("can't solve: pivot == 0");
            }
            const double mult = A(i, j) / pivot;
            A[i].slice(j) = scale_and_add(A[j].slice(j), -mult, A[j].slice(j));
            b(i) -= mult * b(j);
        }
    }
}


// section 29.5.3 : testing
void solve_random_system(size_t n)
{
    // generate random Mat2d
    Mat2d A = random_matrix(n);
    // generate random Vec
    Vec b = random_vector(n);
    cout << "A = " << A << endl;
    cout << "b = " << b << endl;

    try {
        Vec x = classical_gaussian_elimination(A, b);
        cout  << "classical elim solution is x = " << x << endl;
        Vec v = A * x;
        cout << "A * x = " << v << endl;
    }
    catch(const exception& e) {
        cerr << e.what() << endl;
    }
}


// section 29.5.4 : fused operations
using Mat2d = Matrix<double, 2>;
using Vec = Matrix<double, 1>;

struct MVmul {
    const Mat2d& m;
    const Vec& v;
    MVmul(const Mat2d& mm, const Vec& vv) : m{mm}, v{vv} { }

    // evaluate and return result
    operator Vec();
};

inline MVmul operator*(const Mat2d& mm, const Vec& vv)
{
    return MVmul(mm, vv);
}


struct MVmulVadd {
    const Mat2d& m;
    const Vec& v;
    const Vec& v2;
    MvmulVadd(const MVmul& mv, const Vec& vv) : m{mv.m}, v{mv.v}, v2{vv} { }
    // evaluate and return result
    operator Vec();
};

inline MVmulVadd operator+(const MVmul& mv, const Vec& vv)
{
    return MVmulVadd(mv, vv);
}


template<>
class Matrix<double, 1> {
    // ... specialization (just for this example)
    // ...
public:
    // initialize by result of m
    Matrix(const MVmulVadd& m)
    {
        // allocate elements, etc.
        mul_add_and_assign(this, &m.m, &m.v, &m.v2);
    }

    // assign the result of m to *this
    Matrix& operator(MvmulVadd& m)
    {
        mul_add_and_assign(this, &m.m, &m.v, &m.v2);
        return *this;
    }
    // ...
};


U = M * V + W;
// expanded to
U.operator=(MvmulVadd(MVmul(M, V), W));

