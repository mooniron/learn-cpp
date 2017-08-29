/**************************************************************
* Name     :  ex43-1-2.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年8月27日
**************************************************************/



/*
example 44: compatibility
*/


// section 44.3.2: "Silent" differences
int x[99];
void f()
{
    struct x { int a; };
    /* size of the array in C, size of the struct in C++ */
    sizeof(x);
    /* size of the struct */
    sizeof(struct x);
}

