/**************************************************************
* Name     :  ex40-1-7.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年8月22日
**************************************************************/



/*
example 40.7: random numbers
*/


auto gen = bind(normal_distribution<double>{15, 4.0}, default_random_engine{});
for (int i = 0; i < 500; ++i) {
    cout << gen();
}

void test()
{
    // uniform distribution of ints in [10, 20)
    Rand_int ri {10, 20};
    // uniform distribution of doubles in [0, 0.5)
    Rand_double rd {0, 0.5};
    for (int i = 0; i < 100; ++i) {
        cout << ri() << ' ';
    }
    for (int i = 0; i < 100; ++i) {
        cout << rd() << ' ';
    }
}

class Rand_int {
public:
    Rand_int(int lo, int hi) : p{lo, hi} { }
    int operator()() const { return r(); }
private:
    uniform_int_distriburtion<>::param_type p;
    auto r = bind(uniform_int_distribution<>{p}, default_random_engine{});
};

class Rand_double {
public:
    Rand_double(double low, double high) : r(bind(uniform_real_distribution<>(low, high), default_random_engin())) { }
    double operator()() { return r(); }
private:
    function<double()> r;
};


template<typename Iter, typename Size, typename Out, typename Gen>
Out random_sample(Iter first, Iter last, Out result, Size n, Gen&& gen)
{
    using Dist = uniform_int_distribution<Size>;
    using Param = typename Dist::param_type;
    // fill the reservoirand advance first
    copy(first, n, result);
    advance(first, n);
    // Sample the remaining values in [first +n : last) by selecting a random
    // number r in the range [0:k], and if r < n, replace it.
    // k increases with each iteration, making the probability smaller.
    // for random access iterators, k = i-first
    Dist dist;
    for (Size k = n; first != last; ++first, ++k) {
        Size r = dist(gen, Param{0, k});
        if (r < n) {
            *(result + r) = *first;
        }
    }
    return result;

}


// section 40.7.1: engines
map<int, int> m;
linear_congruential_engine<unsigned int, 17, 5, 0> linc_eng;
for (int i = 0; i < 1000000; ++i) {
    if (1 < ++m[linc_eng()]) {
        cout << i << '\n';
    }
}

independent_bits_engine<default_random_engine, 4, unsigned int> ibe;
for (int i = 0; i < 100; ++i) {
    cout << '0' + ibe() << ' ';
}

using minstd_rand0 = linear_congruential_engine<uint_fast32_t, 16807, 0, 2147483647>;
using minstd_rand = linear_congruential_engine<uint_fast32_t, 48271, 0, 2147483647>;
using mt19937 = mersenne_twister_engine<uint_fast32_t, 32, 624, 397, 31, 0x9908b0df, 11, 0xffffffff, 7, 0x9d2c5680, 15, 0xefc60000, 18, 1812433253>;
// ...

// section 40.7.2: random device
// section 40.7.3: distributions
// ok
uniform_int_distribution<int> uid1 {1, 100};
// error: a > b
uniform_int_distribution<int> uid2 {100, 1};
// use a == 0.0 and b ==  1.0
uniform_real_distribution<double> urd1;
// use a == 10.0 and b == 20.0
uniform_real_distribution<double> urd2 {10, 20};
// use double and a == 0.0 and b == 1.0
uniform_real_distribution<> urd3 {};
uniform_int_distribution<> uid3 {0, 5};
for (int i = 0; i < 20; ++i) {
    cout << uid3(e) << ' ';
}


// section 40.7.4: C-style random numbers
#define RAND_MAX /*...*/
// pseudo-random number between 0 and RAND_MAX
int rand();
// seed random number generator by i
void srand(unsigned int i);

