/**************************************************************
* Name     :  ex5-1-20.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年4月19日
**************************************************************/



/*
example 5.6 : math
    5.6.3 : random numbers

a random mechanism consists of two parts : an engine and a distribution.
*/


#include <iostream>
#include <random>
#include <vector>
// for bind
#include <functional>

using namespace std;

// type of engine
using my_engine = default_random_engine;
// type of distribution
using my_distribution = uniform_int_distribution<>;

// the default engine
my_engine re {};
// distribution that maps to the ints 1..6
my_distribution one_to_six {1, 6};
// make a generator
//auto die = bind(uniform_int_distribution<>{1, 6}, default_random_engine{});
auto die = bind(one_to_six, re);

// roll the die : x becomes a value in [1 : 6]
int x = die();


// can not make an object before the class complete definition
//class Rand_int;
// make a random number generator for [1:10]
//Rand_int rndt {1, 10};
// y is a number in [1:10]
//int y = rndt();



//
class Rand_int {
public :
    // constructor
    Rand_int(int low, int high) : dist {low, high} { }
    // draw an int
    int operator()() { return dist(re); }
private :
    default_random_engine re;
    uniform_int_distribution<> dist;
};


int main()
{
    // make a uniform random number generator
    Rand_int rnd {0, 4};
    // make a vector of size 5
    vector<int> histogram(5);
    for (int i = 0; i != 200; ++i)
    {
        // fill histogram with the frequencies of numbers [0:4]
        ++histogram[rnd()];
    }
    // write out a bar graph
    for (int i = 0; i != histogram.size(); ++i)
    {
        // print the tag
        cout << i << '\t';
        for (int j = 0; j != histogram[i]; ++j)
        {
            cout << '*';
        }
        cout << endl;
    }

    return 0;
}
