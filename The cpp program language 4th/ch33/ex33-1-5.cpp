/**************************************************************
* Name     :  ex33-1-5.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年8月2日
**************************************************************/



/*
example 33.4: function objects
*/



// sort v into decreasing order
vector<int> v;
// ...
sort(v.begin(), v.end(), greater<int>{});
//
sort(v.begin(), v.end(), [](int a, int b) { return a > b; });
