/**************************************************************
* Name     :  ex32-1-2.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年8月2日
**************************************************************/



/*
example 32.2: algorithms
*/



// section32.2.1: sequence

void user(vector<int>& v1, vector<int>& v2)
{
    // may overflow v2
    copy(v1.begin(), v1.end(), v2.begin());
    // oops!
    sort(v1.begin(), v2.end());
}

template<typename Cont>
void sort(Cont& c)
{
    static_assert(Range<Cont>(), "sort(): Cont argument not a Range");
    static_assert(Sortable<Iterator<Cont>>(), "sort(): Cont argument not Sortable");
    std::sort(begin(c), end(c));
}

// copy
template<typename Cont1, typename Cont2>
void copy(const Cont1& source, Cont2& target)
{
    static_assert(Range<Cont1>(), "copy(): Cont1 argument not a Range");
    static_assert(Range<Cont2>(), "copy(): Cont2 argument not a Range");
    if (target.size() < source.size()) {
        throw out_of_range{"copy target too small"};
    }
    std::copy(source.begin(), source.end(), target.begin());
}


template<typename Cont, typename Pred>
vector<Value_type<Cont>&> find_all(Cont& c, Pred p)
{
    static_assert(Range<Cont>(), "find_all(): Cont argument not a Range");
    static_assert(Predicate<Pred>(), "find_all(): Pred argument not a Predicate");

    vector<Value_type<Cont>*> res;
    for (auto& x : c) {
        if (p(x)) {
            res.push_back(&x);
        }
    }
    return res;
}

