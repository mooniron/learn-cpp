/**************************************************************
* Name     :  ex15-1-3.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年5月31日
**************************************************************/



/*
example 15.3 : multiple-header organization
    section 15.3.3 : include guard
*/


// error.h
#ifndef CALC_ERROR_H
#define CALC_ERROR_H

namespace Error {
    // ...
}

// CALC_ERROR_H
#endif
