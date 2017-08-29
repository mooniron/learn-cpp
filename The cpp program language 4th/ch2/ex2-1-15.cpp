/**************************************************************
* Name     :  ex2-1-15.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年4月7日
**************************************************************/


/*
example 2.4.3.2 :
    invariants
*/


Vector::Vector(int s) {
    if (s < 0) {
        throw length_error {};
        }   // end if
    elem = new double[s];
    sz = s;
    }   // end comstructor Vector

void test() {
    try {
        // ...
        Vector v[-27];
        }
    // handle negative length
    catch(std::length_error) {
        // ...
        }
    // handle memory exhaustion
    catch(std::bad_alloc) {
        // ...
        }
    }   // end function test
