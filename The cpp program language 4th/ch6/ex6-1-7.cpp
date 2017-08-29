/**************************************************************
* Name     :  ex6-1-7.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年4月25日
**************************************************************/



/*
example 6.2 : types
    6.2.8 : sizes
*/


#include <iostream>
#include <limits>
#include <cstdint>

using namespace std;


int main()
{
    cout << "size of long " << sizeof(1L) << '\n';
    cout << "size of long long " << sizeof(1LL) << '\n';
    cout << "largest float == " << std::numeric_limits<float>::max() << '\n';
    cout << "char is signed == " << std::numeric_limits<char>::is_signed << '\n';

    // cstdint
    // 2 bytes
    int16_t x {0xaabb};
    // 8 bytes
    int64_t xxxx {0xaaaabbbbccccdddd};
    // at least 2 bytes
    int_least16_t y;
    // at least 4 bytes (just like long)
    int_least32_t yy;
    // the fastest int type with at least 4 bytes
    int_fast32_t z;

    // get n bytes
    void* allocate(size_t n);

    return 0;
}
