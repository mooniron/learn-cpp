/**************************************************************
* Name     :  ex12-1-3.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年5月18日
**************************************************************/



/*
example 12.2 : argument passing
*/

// find v in [first : last)
int* find(ing* first, int* last, int v)
{
    while (first != last && *first != v) {
        ++first;
    }
    return first;
}

void g(int* p, int* q)
{
    int* pp = find(p, q, 'a');
    // ...
}


