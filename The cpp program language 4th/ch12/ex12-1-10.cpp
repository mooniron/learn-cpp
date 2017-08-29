/**************************************************************
* Name     :  ex12-1-10.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年5月18日
**************************************************************/



/*
example 12.4 : preconditions and postconditions
*/

/*
calculate the area of a rectangle
precondition : len and wid are positive
postcondition : the return value is positive
postcondition : the return value is the area of a rectange with sides len and wid
*/
int area(int len, int wid)
{
    return len * wid;
}


