/**************************************************************
* Name     :  ex8-1-3.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年5月2日
**************************************************************/


/*
example 8.2 : structures
    8.2.1 : struct layout

use public, private and protected can affect the struct layout
*/


#include <iostream>

using namespace std;


// store members in the order of declaration, size of is 12 if sizeof(int) is 4
struct Readout {
    // [0 : 23]
    char hour;
    int value;
    // sequence mark : ['a': 'z']
    char seq;
};  // end struct


// minimize spaces, sizeof is 8
struct Readout_allign {
    int value;
    char hour;
    char seq;
};
