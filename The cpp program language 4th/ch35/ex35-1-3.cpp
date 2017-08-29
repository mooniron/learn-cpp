/**************************************************************
* Name     :  ex35-1-3.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年8月9日
**************************************************************/



/*
example 35.3: compile-time rational arithmetic
*/



template<intmax_t N, intmax_t D = 1>
struct ratio {
    static constexpr intmax_t num;
    static constexpr intmax_t den;

    using type = ratio<num, den>;
};

static_assert(ratio_add<ratio<1, 3>, ratio<1, 6>>::num == 1, "problem 1/3 + 1/6 != 1/2");
static_assert(ratio_add<ratio<1, 3>, ratio<1, 6>>::den == 2, "problem: 1/3 + 1/6 != 1/2");
static_assert(ratio_multiple<ratio<1, 3>, ratio<3, 2>>::num == 1, "problem: 1/3 * 3/2 != 1/2");
static_assert(ratio_multiple<ratio<1, 3>, ratio<3, 2>>::den == 2, "problem: 1/3 * 3/2 != 1/2");

