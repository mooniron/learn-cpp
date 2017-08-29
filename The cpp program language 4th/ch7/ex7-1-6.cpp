/**************************************************************
* Name     :  ex7-1-6.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年4月25日
**************************************************************/



/*
example 7.4 : pointers and arrays
    7.4.2 : multidimensional arrays
*/


#include <iostream>

using namespace std;


int ma[3][5];

void init_ma()
{
    for (int i = 0; i != 3; i++)
    {
        for (int j = 0; j != 5; j++)
        {
            ma[i][j] = 10 * i + j;
        }
    }
}   // end function init_ma


void print_ma()
{
    for (int i = 0; i != 3; i++)
    {
        for (int j = 0; j != 5; j++)
        {
            cout << ma[i][j] << '\t';
        }
        // add '\n' to end of each row
        cout << '\n';
    }
}   // end function print_ma


// error : comma not allowed in constant expression
int bad[3, 5];
// 3 arrays with 5 ints each
int good[3][5];
// error : int initialized by int*      (good[1,4] means good[4], which is an int*)
int ouch = good[1, 4];
int nice = good[1][4];
