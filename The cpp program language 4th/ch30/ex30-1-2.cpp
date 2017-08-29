/**************************************************************
* Name     :  ex30-1-2.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年7月27日
**************************************************************/



/*
example 30.1: introduction
example 30.2: headers
*/



// section 30.3: language support
// section initializer_list support
template<typename T>
class initializer_list {
public:
    using value_type = T;
    // note const initializer_list elements are immutable
    using reference = const T&;
    using const_reference = const T&;
    using size_type = size_t;
    using iterator = const T*;
    using const_iterator = const T*;
    initializer_list() noexcept;
    // number of elements
    size_t size() const noexcept;
    // first element
    const T* begin() const noexcept;
    // one-past-last element
    const T* end() const noexcept;
    //
};

template<typename T>
const T* begin(initializer_list<T> lst) noexcept
{
    return lst.begin();
}

template<typename T>
const T* end(initializer_list<T> lst) noexcept
{
    return lst.end();
}


void f(initializer_list<int> lst)
{
    for (int i = 0; i < lst.size(); ++i) {
        // error
        cout << lst[i] << '\n';
    }

    const int* p = lst.begin();
    for (int i = 0; i < lst.size(); ++i) {
        // ok
        cout << p[i] << '\n';
    }
}

f2(initializer_list<int> lst)
{
    for (auto x : lst) {
        cout << x << '\n';
    }
}


// section 30.3.2 : range-for support
