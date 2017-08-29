/**************************************************************
* Name     :  ex32-1-4.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年8月2日
**************************************************************/



/*
example 32.4: nonmodifying sequence algorithms
*/



// section 32.4.1: for_each()
// increment each element of v
void increment_all(vector<int>& v)
{
    for_each(v.begin(), v.end(), [](int& x)(++x;));
}


// section 32.4.2: sequence predicates
vector<double> scale(const vector<double>& val, const vector<double>& div)
{
    assert(val.size() < div.size());
    assert(all_of(div.begin(), div.end(), [](double x){ return 0 < x; }));

    vector<double> res(val.size());
    for (int i = 0; i < val.size(); ++i) {
        res[i] = val[i] / div[i];
    }
    return res;
}


// section 32.4.3: count()
void f(const string& s)
{
    auto n_space = count(s.begin(), s.end(), ' ');
    auto n_whitespace = count_if(s.begin(), s.end(), isspace);
    // ...
}


// section 32.4.4: find()
void f(const string& s)
{
    auto p_space = find(x.begin(), s.end(), ' ');
    auto p_whitespace = find_if(s.begin(), s.end(), isspace);
    // ...
}

array<int> x = {1, 3, 4};
array<int> y = {0, 2, 3, 4, 5};

void f()
{
    // p = &x[1]
    auto p = find_first_of(x.begin(), x.end(), y.begin(), y.end());
    // q = &x[2]
    auto q = find_first_of(p+1, x.end(), y.begin(), y.end());
}


// section 32.4.5: equal() and mismatch()
template<class In, class In2, class Pred = equal_to<Value_type<In>>>
pair<In, In2> mismatch(In first, In last, In2 first2, Pred p = {})
{
    while (first != last && p(*first, *first2)) {
        ++first;
        ++first2;
    }
    return {first, first2};
}


// section 32.4.6: search()
string quote {"Why waste time learning, when ignorance is instantaneous?"};
bool in_quote(const string& s)
{
    // find s in quote
    auto p = search(quote.begin(), quote.end(), s.begin(), s.end());
    return p != quote.end();
}

void g()
{
    // true
    bool b1 = in_quote("learning");
    // false
    bool b2 = in_quote("lemming");
}
