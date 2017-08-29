/**************************************************************
* Name     :  ex31-1-3.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年7月30日
**************************************************************/



/*
example 31.3 : operations overview
*/



// section 31.3.1: member types
// section 31.3.2: constructors, destructor, and assignments
void task(vector<int>&& v);

vector<int> user(vector<int>& large)
{
    vector<int> res;
    // ...
    // transfer ownership of data to task()
    task(move(large));
    // ...
    return res;
}


// section 31.3.3: size and capacity
// section 31.3.4: iterators
for (auto p v.begin(); p != v.end(); ++p)
{
    if (p != v.begin() && *(p-1) == *p) {
        cout << "duplicate " << *p << '\n';
    }
}

// use const iterators
for (auto p v.cbegin(); p != v.cend(); ++p)
{
    if (p != v.cbegin() && *(p-1) == *p) {
        cout << "duplicate " << *p << '\n';
    }
}


auto beg = v.cbegin();
auto end = v.cend();

for (auto p = beg; p != end; ++p) {
    if (p != beg && *(p-1) = *p) {
        cout << "duplicate" << *p << '\n';
    }
}


// section 31.3.5: element access
// section 31.3.6: stack operations
vector<complex<double>> vc;

// read two doubles
for (double re, im; cin >> re >> im; ) {
    // add complex<double>{re, im} at the end
    vc.emplace_back(re, im);
}


// section 31.3.7: list operations
vector<int> v {4, 3, 5, 1};
// points to v[2], that is the 5
auto p = v.begin() + 2;
// p becomes invalid; v == {4, 3, 5, 1, 6}
v.push_back(6);
// points to v[2], that is, the 5
p = v.begin() + 2;
// p2 points to v[4], that is, the 6
auto p2 = v.begin() + 4;
// v == {4, 3, 5, 6}; p is valid, p2 is invalid
v.erase(v.begin()+3);


void user(list<pair<string, double>>& lst)
{
    auto p = lst.begin();
    // find an insertion point
    while (p != lst.end() && p->first != "Denmark") {
        ;
    }
    // nice and terse
    p = lst.emplace(p, "England", 7.5);
    // helper function
    p = lst.insert(p, make_pair("France", 9.8));
    // verbose
    p = lst.insert(p, pair<string, double>{"Greece", 3.14});
}


// section 31.3.8: other operations
