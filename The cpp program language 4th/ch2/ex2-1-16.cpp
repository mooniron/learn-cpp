/**************************************************************
* Name     :  ex2-1-16.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年4月7日
**************************************************************/


/*
example 2.4.3.3 :
    static assertions : check when compile time.

static_assert(A, s) :
    print s as a compile error if A is not true.
*/

// check integer size
static_assert(4 <= sizeof(int), "integers are too small");
// light speed
constexpr double c = 299792.458;     // km/s

void f(double speed) {
    // 160km/h == 160.0 / (60 * 60) km/s
    const double local_max = 160.0 / (60 * 60);
    // error : speed must be a const
    static_assert(speed < c, "can't go that fast");
    // ok
    static_assert(local_max < c, "can't go that fast");
    }   // end function f
