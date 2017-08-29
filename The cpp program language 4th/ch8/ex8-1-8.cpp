/**************************************************************
* Name     :  ex8-1-8.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年5月3日
**************************************************************/


/*
example 8.2 : structures
    8.2.7 : fields
*/


#include <iostream>

using namespace std;


// R6000 physical number
struct PPN {
    // page frame number
    unsigned int PFN : 23;
    // unused
    int : 3;
    // Cache coherency algorithms
    unsigned int CCA : 3;
    bool nonreachable : 1;
    bool dirty : 1;
    bool valid : 1;
    bool global : 1;
};


void part_of_VM_system(PPN* p)
{
    // ...
    // contents changed
    if (p->dirty) {
        // copy to disk
        p->dirty = 0;
    }   // end if
}   // end function
