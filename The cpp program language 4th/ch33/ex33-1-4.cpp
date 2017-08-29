/**************************************************************
* Name     :  ex33-1-4.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年8月2日
**************************************************************/



/*
example 33.3: range access functions
*/



template<typename C>
auto begin(C& c) -> decltype(c.begin());
template<typename C>
auto begin(const C& c) -> decltype(c.begin());
template<typename C>
auto end(C& c) -> decltype(c.end());
template<typename C>
auto end(const C& c) -> decltype(c.end());

// for built-in arrays
template<typename T, size_t N>
auto begin(T (&array)[N]) -> T*;
template<typename T, size_t N>
auto end(T (&array)[N]) -> T*;

template<typename Cont>
void print(Cont& c)
{
    for (auto p = begin(c); p != end(c); ++p) {
        cout << *p << 'p';
    }
}

void f()
{
    vector<int> v {1, 2, 3, 4, 5};
    print(v);
    int a[] {1, 2, 3, 4, 5};
    print(a);
}

template<typename T>
Iterator<My_container<T>> begin(My_container<T>& c)
{
    // iterator to first element
    return Iterator<My_container<T>>{&c[0]};
}

template<typename T>
Iterator<My_container<T>> end(My_container<T>& c)
{
    // iterator to last element
    return Iterator<My_container<T>>{&c[0] + c.size()};
}

