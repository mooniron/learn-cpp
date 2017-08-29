/**************************************************************
* Name     :  ex41-1-4.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年8月23日
**************************************************************/



/*
example 41.4: volatile
*/


// updated by the hardware clock
volatile const long clock_register;

auto t1 {clock_register};
// ... no use of clock_register here ...
auto t2 {clock_register};
