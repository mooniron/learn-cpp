/**************************************************************
* Name     :  ex4-1-9.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年4月19日
**************************************************************/


/*
example 4.4 : containers
    4.4.3 : map

a linear search is inefficient for all but the shortest lists.

map : an associative array or a dictionary, a search tree (a red-black tree) called map.
    it is implemented as a balanced binary tree.

the cost of a map lookup is O(log(n)) where n is the number of elements in the map.

unordered map : hashed lookup rather than comparison using an ordering function.
*/

// initialize a map
map<string, int> phone_book {
    { "David Hume", 123456},
    {"Karl Popper", 234567},
    {"Bertrand Arthur William Russell", 345678}
};

// get key, return value
int get_number(const string& s)
{
    // if not found, s is added into the map with the default value
    return phone_book[s];
}



/*  unordered map  */
#include <unordered_map>

// initialize an unordered_map
unordered_map<string, int> phone_book_hash {
    { "David Hume", 123456},
    {"Karl Popper", 234567},
    {"Bertrand Arthur William Russell", 345678}
};

// subscript an unordered_map, input key, return value
int get_number(const string& s)
{
    // if not found, s is added into the map with the default value
    return phone_book_hash[s];
}



