/**************************************************************
* Name     :  ex32-1-7.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年8月2日
**************************************************************/



/*
example 32.7: min and max
*/



int x = 7;
int y = 9;
// error: the result of min(x, y) is a const int&
++min(x, y);
// error: the result of min({x, y}) is an rvalue (an initializer_list is immutable)
++min(x, y);

string s = "Large_Hadron_Collider";
auto p = minmax_element(s.begin(), s.end(),
    [](char c1, char c2) { return toupper(c1) < toupper(c2); }
);
cout << "min == " << *(p.first) << ' ' << "max == " << *(p.second) << '\n';
