/**************************************************************
* Name     :  ex7-1-9.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年4月25日
**************************************************************/



/*
example 7.6 : pointers and ownership
*/


#include <iostream>

using namespace std;


void confused(int* p)
{
    // delete p?
}


int global {7};

void f()
{
    X* pn = new int{7};
    int i {7};
    int q = &i;
    confused(pn);
    confused{q};
    confused(&global);
}
