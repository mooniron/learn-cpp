/**************************************************************
* Name     :  ex33-1-2.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年8月2日
**************************************************************/



/*
example 33.1: introduction
*/



// section 33.1.3: iterator traits
template<typename Iter>
struct iterator_traits {
    using value_type = typename Iter::value_type;
    using difference_type = typename Iter::difference_type;
    // pointer type
    using pointer = typename Iter::pointer;
    // reference type
    using reference = typename Iter::reference;
    // (tag)
    using iterator_category = typename Iter::iterator_category;
};

// specialization for pointers
template<typename T>
struct iterator_traits<T*> {
    using difference_type = ptrdiff_t;
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    using iterator_category = random_access_iterator_tag;
};

// not general, pointers have no value_type member
template<typename Iter>
typename Iter::value_type read(Iter p, int n)
{
    // ... do some checking ...
    return p[n];
}

// more general
template<typename Iter>
typename iterator_traits<Iter>::value_type read(Iter p, int n)
{
    // ... do some checking ...
    return p[n];
}

// alias to avoid implement details
template<typename Iter>
using Category<Iter> = typename std::iterator_traits<Iter>::iterator_category;
template<typename Iter>
using Difference_type<Iter> = typename std::iterator_traits<Iter>::difference_type;

template<typename Iter>
void f(Iter p, Iter q)
{
    // syntax error: "typename" missing
    Iter::difference_type d1 = distance(p, q);
    // doesn't work for pointers, etc
    typename Iter::difference_type d2 = distance(p, q);
    // ok but ugly
    typename iterator_traits<Iter>::difference_type d3 = distance(p, q);
    // ok, much better
    Distance_type<Iter> d4 = distance(p, q);
    // ok, if you don't need to mention the type explicitly
    auto d5 = distance(p, q);
    // ...
}

template<typename Cat, typename T, typename Dist = ptrdiff_t, typename Ptr = T*, typename Ref = T&>
struct iterator {
    using value_type = T;
    // type used by distance
    using difference_type = Dist;
    // pointer type
    using pointer = Ptr;
    // reference
    using reference = Ref;
    // category (tag)
    using iterator_category = Cat;
};


// section 33.1.4: iterator operations
