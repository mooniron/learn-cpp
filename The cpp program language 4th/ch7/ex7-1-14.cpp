/**************************************************************
* Name     :  ex7-1-14.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年5月2日
**************************************************************/


/*
example 7.7 : references
    7.7.3 : references to references
*/


#include <iostream>
#include <vector>
#include <string>
#include <utility>

using namespace std;


//
using rr_i = int&&;
using lr_i = int&;
// int && && == int &&
using rr_rr_i = rr_i&&;
// int && & == int &
using lr_rr_i = rr_i &;
// int & && == int &
using rr_lr_i = lr_i&&;
// int & & == int &
using lr_lr_i = lr_i &;
//

// syntax does not allow
int && & r = i;
