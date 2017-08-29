/**************************************************************
* Name     :  ex4-1-2.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年4月18日
**************************************************************/


/*
example 4.1.2 : standard-library headers and namespaces
*/

// make the standard string facilities accessible
#include <string>
#include <list>


std::string s {"Four legs Good; two legs Baaad!"};
std::list<std::string> slogans {"War is peace", "Freedom is Slavery", "Ignorance is Strength"};

// make the standard string facilities accessible
#include <string>

// make std names available without std:: prefix
using namespace std;

// OK: string is std::string
string s {"C++ is a general-purpose programming language"};


/*
selected standard-library :
    <algorithms>, <array>, <chrono>, <cmath>, <complex>, <fstream>, <future>, <iostream>,
    <map>, <memory>, <random>, <regex>, <string>, <set>, <sstream>, <thread>, <unordered_map>,
    <utility>, <vector>,
*/
