/**************************************************************
* Name     :  ex32-1-6.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年8月2日
**************************************************************/



/*
example 32.6: sorting and searching
*/



template<typename List>
void sort_list(List& lst)
{
    // initialize from lst
    vector v {lst.begin(), lst.end()};
    sort(v);
    copy(v, lst);
}

// find the top ten books
void f(const vector<Book>& sales)
{
    vector<Book> bestsellers(10);
    partial_sort_copy(sales.begin(), sales.end(), bestsellers.begin(), bestsellers.end(),
        [](const Book& b1, const Book& b2) { return b1.copies_sold() > b2.copies_sold(); }
    );

    copy(bestsellers.begin(), bestsellers.end(), ostream_iterator<Book>{cout, "\n"});
}


vector<int> v;
for (int i = 0; i < 1000; ++i) {
    v.push_back(randint(1000));
}
constexpr int n = 30;
nth_element(v.begin(), v.begin() + n, v.end());
cout << "nth: " << v[n] << '\n';
for (int i = 0; i < n; ++i) {
    cout << v[i] << ' ';
}

vector<string> vs = {
    "Helsinki",
    "Copenhagen",
    "Oslo",
    "Stockholm"
};

vector<char*> vcs = {
    "Helsinki",
    "Copenhagen",
    "Oslo",
    "Stockholm"
};

void use()
{
    sort(vs);
    sort(vcs);

    for (auto& x : vs) {
        cout << x << ' ';
    }
    cout << '\n';

    for (auto& x : vcs) {
        cout << x << ' ';
    }

    sort(vcs, [](const char* p, const char* q) { return strcmp(p, q) < 0; })
}


// section 32.6.1: binary search
void f(vector<int>& c)
{
    if (binary_search(c.begin(), c.end(), 7)) {
        // is 7 in c?
        // ...
    }
    // ...
}

void g(vector<int>& c)
{
    // probably slow: O(N); c needn't be sorted
    auto p = find(c.begin(), c.end(), 7);
    // probably fast: O(log(N)); c must be sorted
    auto q = lower_bound(c.begin(), c.end(), 7);
    // ...
}


// section 32.6.2: merge()
vector<int> v {3, 1, 4, 2};
// lst is in order
list<double> lst {0.5, 1.5, 2, 2.5};
sort(v.begin(), v.end());

vector<double> v2;
// merger v and lst into v2
merge(v.begin(), v.end(), lst.begin(), lst.end(), back_inserter(v2));
for (double x : v2) {
    cout << x << ", ";
}


// section 32.6.3: set algorithms
string s1 = "qwertyasdfgzxcvb";
string s2 = "poiuyasdfg/..mnb";
// the set algorithms require sorted sequences
sort(s1.begin(), s1.end());
sort(s2.begin(), s2.end());
// set aside enough space for the targest possible result
string s3(s1.size() + s2.size(), '*');
cout << s3 << '\n';
auto up = set_union(s1.begin(), s1.end(), s2.begin(). s2.end(). s3.begin());
cout << s3 << '\n';
for (auto p = s3.begin(); p != up; ++p) {
    cout << *p;
}
cout << '\n';
s3.assign(s1.size() + s2.size(), '+');
up = set_difference(s1.begin(), s1.end(), s2.begin(), s2.end(), s3.begin());
cout << s3 << '\n';
for (auto p = s3.begin(); p != up; ++p) {
    cout << *p;
}
cout << '\n';

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;



int main() {
    // section 32.6.4: heaps
    string s = "herewego";
    // worheege
    make_heap(s.begin(), s.end());
    cout << s << "\n";
    // rogheeew
    pop_heap(s.begin(), s.end());
    cout << s << "\n";
    // ohgeeerw
    pop_heap(s.begin(), s.end()-1);
    cout << s << "\n";
    // hegeeorw
    pop_heap(s.begin(), s.end()-2);
    cout << s << "\n";
    // hegeefrw
    *(s.end()-3) = 'f';
    cout << s << "\n";
    push_heap(s.begin(), s.end()-2);
    // hegeefrw
    cout << s << "\n";
    *(s.end()-2) = 'x';
    // hegeefxw
    cout << s << "\n";
    push_heap(s.begin(), s.end()-1);
    // xeheefgw
    cout << s << "\n";
    *(s.end()-1) = 'y';
    // xeheefgy
    cout << s << "\n";
    // yxheefge
    push_heap(s.begin(), s.end());
    cout << s << "\n";
    // eeefghxy
    sort_heap(s.begin(), s.end());
    // yxhgfeee
    reverse(s.begin(), s.end());
}

// section 32.6.5: lexicographical_compare()
template<class In, class In2>
bool lexicographical_compare(In first, In last, In2 first2, In2 last2)
{
    for ( ; first != last && first2 != last2; ++ first, ++first2) {
        if (*first < *first2) {
            // [first:last) < [first2:last2)
            return true;
        }
        if (*first2 < *first) {
            // [first2:last2) < [first:last)
            return false;
        }
    }
    // [first:last) < [first2:last2) if [first:last) is shorter
    return first == last && first2 != last2;
}

string n1 {"1000"};
string n2 {"999"};
//  b1 == true
bool b1 = lexicographical_compare(n1.begin(), n1.end(), n2.begin(), n2.end());
n1 = "Zebra";
n2 = "Aardvark";
// b2 == false
bool b2 = lexicographical_compare(n1.begin(), n1.end(), n2.begin(), n2.end());
