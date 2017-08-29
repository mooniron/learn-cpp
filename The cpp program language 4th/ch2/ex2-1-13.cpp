/**************************************************************
* Name     :  ex2-1-13.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年4月7日
**************************************************************/


/*
example 2.4.2 :
    namespaces
*/


#include <iostream>
#include <cmath>

namespace My_code {
    class complex { /* .. */ };
    complex sqrt(complex);
    // ...

    int main();
    }   // end namespace My_code


int My_code::main() {
    complex z {1, 2};
    auto z2 = sqrt(z);
    std::cout << '{' << z2.real() << ',' << z2.imag() << "}\n";
    // ...
    };


int main() {
    return My_code::main();
    }   // end function main
