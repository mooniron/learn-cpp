/**************************************************************
* Name     :  ex7-1-7.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年4月25日
**************************************************************/



/*
example 7.4 : pointers and arrays
    7.4.3 : passing arrays
*/


#include <iostream>

using namespace std;


// arg is a double*
// void comp(double* arg)
void comp(double arg[10])
{
    for (int i = 0; i != 10; ++i)
    {
        arg[i] += 99;
    }
}   // end function comp

void one_test(double* argu, int dim)
{
    for (int i = 0; i != dim; ++i) {
        cout << argu[i] << '\t';
    }
    cout << '\n';
}


void f()
{
    double a1[10];
    double a2[5];
    double a3[100];

    comp(a1);
    one_test(a1, 10);
    // disaster!
    comp(a2);
    one_test(a2, 10);
    // uses only the first 10 elements
    comp(a3);
    one_test(a3, 10);
}





// dimensions is known at compile-time
void print_m35(int m[3][5])
{
    for (int i = 0; i != 3; i++)
    {
        for (int j = 0; j != 5; j++)
        {
            cout << m[i][j] << '\t';
        }
        cout << '\n';
    }
}


void print_mi5(int m[][5], int dim1)
{
    for (int i = 0; i != dim1; i++) {
        for (int j = 0; j != 5; j++) {
            cout << m[i][j] << '\t';
        }
        cout << '\n';
    }
}   // end function print_mi5


/*
// does not behave as most people would think; a two-dimension array is int*, not int**
void print_mij(int m[][], int dim1, int dim2)
{
    for (int i = 0; i != dim1; i++) {
        for (int j = 0; j != dim2; j++) {
            // surprise!
            cout << m[i][j] << '\t';
        }
        cout << '\n';
    }   // end for
}   // end function print_mij
*/


// a correct solution
void print_mij_ok(int* m, int dim1, int dim2)
{
    for (int i = 0; i != dim1; i++) {
        for (int j = 0; j != dim2; j++) {
            // obscure
            cout << m[i * dim2 + j] << '\t';
        }
        cout << '\n';
    }
}


// a matrix is just an ordinary pointer
int test()
{
    int v[3][5] = {
        {0, 1, 2, 3, 4},
        {10, 11, 12, 13, 14},
        {20, 21, 22, 23, 24}
    };

    print_m35(v);
    print_mi5(v, 3);
    print_mij_ok(&v[0][0], 3, 5);
    // error: cannot convert 'int (*)[5]' to 'int*' for argument '1' to 'void print_mij_ok(int*, int, int)'
    //print_mij_ok(v, 3, 5);

    return 0;
}


// main function
int main()
{
    f();
    test();

    return 0;
}
