/**************************************************************
* Name     :  ex29-1-2.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年7月24日
**************************************************************/



/*
example 29.1 : introduction
*/



// section 29.1.1 : basic matrix uses
// N-dimensions matrix with T value-type
Matrix<T, N>
// zero dimensions: a scalar
Matrix<double, 0> m0{1};
// one dimension : a vector (4 elements)
Matrix<double, 1> m1{1, 2, 3, 4};
// two dimensions (4*3 elements)
Matrix<double, 2> m2 {
    // row 0
    {00, 01, 02, 03},
    // row 1
    {10, 11, 12, 13},
    // row 2
    {20, 21, 22, 23}
};
// three dimensions (4*7*9 elements), all 0-initialized
Matrix<double, 3> m3(4, 7, 9);
// 17 dimensions (no elements so far)
Matrix<complex<double>, 17> m17;

// ok
Matrix<double, 2> md;
// ok : just don't try arithmetic operations
Matrinx<string, 2> ms;
// 3-by-2 matrix of 2-by-2 matrices
Matrix<Matrix<int, 2>, 2> mm {
    // a matrix is a plausible "number"
    {   // row 0
        {{1, 2}, {3, 4}},
        {{4, 5}, {6, 7}},
    },
    {   // row 1
        {{1, 2}, {3, 4}},
        {{4, 5}, {6, 7}},
    },
    {   // row 2
        {{1, 2}, {3, 4}},
        {{4, 5}, {6, 7}},
    },
};

// error : too many dimension sizes
Matrix<char, 2> mc1(2, 3, 4);
// error : initializer missing for second dimension
Matrix<char, 2> mc2 {
    {'1', '2', '3'}
};
// error : element missing for third column
Matrix<char, 2> mc2 {
    {'1', '2', '3'},
    {'4', '5'}
};

// one dimension: a vector (100 elements)
Matrix<double, 1> m1(100);
// two dimensions 50 * 6000 elements
Matrix<double, 2> m2(50, 6000);
// 1
auto d1 = m1.order();
// 2
auto d2 = m2.order();
// 100
auto  e1 = m1.extent(0);
// error : m1 is one-dimensional
auto e1 = m1.extent(1);
// 50
auto e2 = m2.extent(0);
// 6000
auto e2 = m2.extent(1);
// 100
auto s1 = m1.size();
// 50 * 6000
auto s2 = m2.size();

// two-dimensions 3 * 4 elements
Matrix<double, 2> m {
    {00, 01, 02, 03},
    {10, 11, 12, 13},
    {20, 21, 22, 23}
};
// d1 = 12
double d1 = m(1, 2);
double d2 = m[1][2];
// row 1 : {10, 11, 12, 13}
Matrix<double, 1> m1 = m[1];
// d3 == 12
double d3 = m1[2];

template<typename M>
Enable_if<Matrix_type<M>(), ostream&> operator<<(ostream& os, const M& m)
{
    os << '{';
    for (size_t i = 0; i != rows(m); ++i) {
        os << m[i];
        if (i+1 != rows(m)) {
            os << ',';
        }
    }
    return os << '}';
}


// section 29.1.2 : Matrix requirements
