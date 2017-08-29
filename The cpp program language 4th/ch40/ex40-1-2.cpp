/**************************************************************
* Name     :  ex40-1-2.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年8月22日
**************************************************************/



/*
example 40.1: introduction
example 40.2: numerical limits
*/


void f(double d, int i)
{
    char classification[numeric_limits<unsigned char>::max()];
    if (numeric_limits<unsigned char>::digits == numeric_limits<char>::digits) {
        // chars are unsigned
    }
    if (i < numeric_limits<short>::min() || numeric_limits<short>::max() < i) {
        // i cannot be stored in a short without loss of digits
    }
    if (0 < d && d < numeric_limigts<double>::epsilon()) {
        d = 0;
    }
    if (numeric_limits<Quad>::is_specialized) {
        // limits information is available for type Quad
    }
}

template<typename T>
class numeric_limits {
public:
    // is information available for numeric_limits<T>?
    static const bool is_specialized = false;
    // ... uninteresting defaults ...
};

template<>
class numeric_limits<char> {
public:
    static const bool is_specialized =  true;
    // number of bits excluding sign
    static const int digits = 7;
    static const bool is_signed = true;
    static const bool is_integer = true;
    static constexpr char min() noexcept noexcept { return -128; }
    static constexpr char max() noexcept { return 127; ]
    // ...
};

template<>
class numeric_limits<float> {
public:
    static const bool is_specialized  = true;
    // base of exponent
    static const int radix = 2;
    static const int digits = 24;
    static const int digits10 = 9;
    static const bool is_signed = true;
    static const bool is_integer = false;
    static const bool is_exact = false;
    static constexpr float min() noexcept { return 1.17549435E-38F; }
    // ...
};


// section 40.2.1: limit macros
