/**************************************************************
* Name     :  ex3-1-14.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年4月7日
**************************************************************/


/*
example 3.4 : templates
    3.4.5 : aliases
*/


#include <iostream>

using namespace std;


// using size_t = unsigned int;
template<typename T>

class Vector {
public :
    //
    using value_type = T;
    // ...
};


//
template<typename C>
using element_type = typename C::value_type;

//
template<typename Container>

void algo(Container& c)
{
    // keep results here
    Vector<element_type<Container>> vec;
    // ...
}


/*  */
template<typename Key, typename Value>

class Map {
    // ...
};

template<typename Value>
using String_map = Map<string, Value>;
// m is a Map<string, int>
String_map<int> m;
