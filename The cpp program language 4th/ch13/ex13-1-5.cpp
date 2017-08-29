/**************************************************************
* Name     :  ex13-1-5.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年5月23日
**************************************************************/



/*
example 13.2 : exception guarantees
*/


// (vx[i], vy[i]) is a point for all i
namespace Points {
    vector<int> vx;
    vector<int> vy;
}

void f(int i)
{
    int* p = new int[10];
    // ...
    if (i < 0) {
        // delete before the throw or leak
        delete[] p;
        throw Bad();
    }
    // ...
}
