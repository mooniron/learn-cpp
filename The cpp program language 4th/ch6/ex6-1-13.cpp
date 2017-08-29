/**************************************************************
* Name     :  ex6-1-13.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年4月25日
**************************************************************/



/*
example 6.4 : objects and values
    6.4.1 lvalues and rvalues

a low-level object is a contiguous region of storage; a lvalue is an expression that refers to
an object.

lvalue
rvalue
xvalue
*/


void f(vector<string>& vs)
{
    // move vs to v2, std::move(vs) is an xvalue
    vector<string>& v2 = std::move(vs);
}
