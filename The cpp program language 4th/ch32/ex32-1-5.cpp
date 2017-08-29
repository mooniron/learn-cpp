/**************************************************************
* Name     :  ex32-1-5.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年8月2日
**************************************************************/



/*
example 32.5: modifying sequence algorithms
*/



template<class In, class Out, class Op>
Out transform(In first, In last, Out res, Op op)
{
    while (first != last) {
        *res++ = op(*first++);
    }
    return res;
}

// remove case
void toupper(string& s)
{
    transform(s.begin(), s.end(), s.begin(), toupper);
}


// section 32.5.1: copy()
void f(list<Club>& lc, ostream& os)
{
    copy(lc.begin(), lc.end(), ostream_iterator<Club>(os));
}

void f(const vector<char>& vs, vector<char>& v)
{
    // might overwrite end of v
    copy(vs.begin(), vs.end(), v.begin());
    // add elements from vs to end of v
    copy(vs.begin(), vs.end(), back_inserter(v));
}

void f(list<int>& ld, int n, ostream& os)
{
    copy_if(ld.begin(), le.end(),ostream_iterator<int>(os),
        [n](int x) { return x > n; }
    );
}


// section 32.5.2: unique()
void f(list<string>& ls, vector<string>& vs)
{
    // list sort to get equal values adjacent
    ls.sort();
    // eleminate adjacent duplicates
    unique_copy(ls.begin(), ls.end(), back_inserter(vs));
}

// warning: doesn't do what it appears to do
void bad(vector<string>& vs)
{
    // sort  vector
    sort(vs.begin(), vs.end());
    // eliminate duplicates (no it doesn't!)
    unique(vs.begin(), vs.end());
}

int main()
{
    string s = "abbcccde";
    auto p = unique(s.begin(), s.end());
    cout << s << ' ' << p - s.begin() << '\n';
}


template<class C>
void eliminate_duplicates(C& c)
{
    sort(c.begin(), c.end());
    auto p = unique(e.begin(), c.end());
    // shrink
    c.erase(p, c.end());
}


// section 32.5.3: remove() and replace()
string s {"*CamelCase*IsUgly*"};
cout << s << '\n';
auto p = remove(s.begin(), s.end(), '*');
// CamelCaseIsUgly
copy(s.begin(), p, ostream_iterator<char>{cout});
// CamelCaseIsUglyly*
cout << s << '\n';


// 32.5.4: rotate(), random_shuffle(), and partition()
void f(deque<Card>& dc, My_rand& r)
{
    random_shuffle(dc.begin(), dc.end(), r);
    // ...
}


// section 32.5.5: permutations
vector<char> v {'a', 'b', 'c'};

while (next_permutation(v.begin(), v.end())) {
    cout << v[0] << v[1] << v[2] << ' ';
}


// section 32.5.6: fill()
int v1[900];
array<int, 900> v2;
vector<int> v3;

void f()
{
    // set all elements of v1 to 99
    fill(begin(v1), end(v1), 99);
    // set to random values
    generate(begin(v2), end(v2), Randint{});
    // output 200 random integers in the interval [0:100)
    generate_n(ostream_iterator<int>{cout}, 200, Urand{100});
    // add 20 elements with the value 99 to v3
    fill_n(back_inserter{v3}, 20, 99);
}

vector<string> vs {"Breugel", "ElGreco", "Delacroix", "Constable"};
vector<string> vs2 {"Hals", "Goya", "Renoir", "Turner"};
// ok
copy(vs.begin(), vs.end(), vs2.begin());
// leaks!
uninitialized_copy(vs.begin(), vs.end(), vs.begin());


// section 32.5.7: swap()
void  use(vector<int>& v, int* p)
{
    // exchange values
    swap_ranges(v.begin(), v.end(), p);
}

