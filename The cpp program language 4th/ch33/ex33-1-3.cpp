/**************************************************************
* Name     :  ex33-1-3.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年8月2日
**************************************************************/



/*
example 33.2: iterator adaptor
*/



// section 33.2.1: reverse iterator
template<typename Iter>
class reverse_iterator : public iterator<Iterator_category<Iter>, Value_type<Iter>, Difference_type<Iter>, Pointer<Iter>, Reference<Iter>> {
public:
    using iterator_type = Iter;
    reverse_iterator() : current{} { }
    explicit reverse_iterator(Iter p) : current{p} { }
    template<typename Iter2>
    reverse_iterator(const reverse_iterator<Iter2>& p) : current(p.base()) { }
    // current iterator value
    Iter base() const { return current; }
    reference operator*() const
    {
        tmp = current;
        return *--tmp;
    }
    pointer operator->() const;
    reference operator[](difference_type n) const;
    reverse_iterator& operator++()
    {
        --current;
        return *this;
    }
    reverse_iterator operator++(int)
    {
        reverse_iterator t = current;
        --current;
        return t;
    }
    reverse_iterator& operator--()
    {
        ++current;
        return *this;
    }
    reverse_iterator operator--(int)
    {
        reverse_iterator t = current;
        ++current;
        return t;
    }
    reverse_iterator operator+(difference_type n) const;
    reverse_iterator& operator+=(difference_type n);
    reverse_iterator operator-(difference_type n) const;
    reverse_iterator& operator-=(difference_type n);
    // ...
protected:
    // current points to the element after the one *this refers to
    Iterator current;
private:
    // ...
    // for temporaries that need to outlive a function scope
    iterator tmp;
};


void f(vector<int>&  v, list<char>& lst)
{
    // ok: random access iterator
    v.rbegin()[3] = 7;
    // error: bidirectional iterator doesn't support[]
    lst.rbegin()[3] = '4';
    // ok
    *(next(lst.rbegin(), 3)) = '4';
}

// last occurrence
auto ri = find(v.rbegin(), v.rend(), val);

// use C's iterator in the interface
template<typename C, typename Val>
auto find_last(C& c, Val v) -> decltype(c.begin())
{
    auto ri = find(c.rbegin(), c.rend(), v);
    if (ri == c.rend()) {
        // use c.end() to indicate "not found"
        return c.end();
    }
    return prev(ri.base());
}

// explicit version
template<typename C, typeanme Val>
auto find_last(C& c, Val v) -> decltype(c.begin())
{
    for (auto p = c.rbegin(); p != c.rend(); ++p) {
        if (*p == val) {
            return --p.base();
        }
    }
    // use c.end() to indicate not found
    return c.end();
}

template<typename C, typename Val>
auto find_last(C& c, Val v) -> decltype(c.begin())
{
    // search backward from end
    for (auto p = c.end(); p != c.begin(); ) {
        if (*--p == v) {
            return p;
        }
    }
    return c.end();
}


// section 33.2.2: insert iterators
void f(vector<int>& vi)
{
    // assign 7 to vi[0]..vvi[199]
    fill_n(vi.begin(), 200, 7);
}


void g(vector<int>& vi)
{
    // add 200 7s to the end of vi
    fill_n(back_inserter(vi), 200, 7);
}


// section 33.2.3: move iterator
vector<string> read_strings(istream&);
// get some strings
auto vs = read_strings(cin);
vector<string> vs2;
// copy strings from vs into vs2
copy(vs, back_inserter(vs2));
vector<string> vs3;
// move strings from vs2 into vs3
copy(vs2, make_move_iterator(back_inserter(vs3)));

