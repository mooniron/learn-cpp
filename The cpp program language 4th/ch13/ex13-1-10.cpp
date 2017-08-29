/**************************************************************
* Name     :  ex13-1-10.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年5月23日
**************************************************************/



/*
example 13.6 : a vector implementation
*/


// section 13.6.1 : a simple vector
template<class T, class A = allocator<T>>
class vector {
private :
    // start of allocation
    T* elem;
    // end of element sequence, start of space allocated for possible expansion
    T* space;
    // end of allocated space
    T* last;
    // allocator
    A alloc;

public :
    // type used for vector sizes
    using size_type = unsigned int;

    explicit vector(size_type n, const T& val = T(), const A& = A());
    // copy constructor
    vector(const vector& a);
    // copy assignment
    vector& operator=(const vector& a);
    // move constructor
    vector(vector&& a);
    // move assignment
    vector& operator=(vector&& a);
    // destructor
    ~vector();

    size_type size() const { return space - elem; }
    size_type capacity() const { return last - elem; }
    // increase capacity to n
    void reserve(size_type n);
    // increase size to n
    void resize(size_type n, const T& = {});
    // add an element at the end
    void push_back(const T&);

    // ...
};


// warning : naive implementation
template<class T, class A>
vector<T, A>::vector(size_type n, const T& val, const A& a)
    // copy the allocator
    : alloc {a}
{
    // get memory for elements
    elem = alloc.allocate(n);
    space = last = elem + n;
    for (T* p = elem; p != last; ++p) {
        // construct copy of val in *p
        a.construct(p, val);
    }
}


// elaborate implementation
template<class T, class A>
vector<T, A>::vector(size_type n, const T& val, const A& a)
    // copy the allocator
    : alloc {a}
{
    // get memory for elements
    elem = alloc.allocate(n);

    iterator p;
    try {
        iterator end = elem + n;
        for (p = elem; p != end; ++p) {
            // construct element
            alloc.construct(p, val);
        }
        last = space = p;
    }
    catch (...) {
        for (iterator q = elem; q != p; ++q) {
            // destroy constructed elements
            alloc.destroy(q);
        }
        // free memory
        alloc.deallocate(elem, n);
        // rethrow
        throw;
    }
}


template<class For, class T>
void uninitialized_fill(For beg, For end, const T& x)
{
    For p;
    try {
        for (p = beg; p != end; ++p) {
            // construct copy of x in *p
            ::new(static_cast<void*>(&*p)) T (x);
        }
    }
    catch (...) {
        for (For q = beg; q != p; ++p) {
            // destroy element
            (&*q)->~T();
        }
        // rethrow
        throw;
    }
}


// still abit messy
template<class T, class A>
vector<T, A>::vector(size_type n, const T& val, const A& a)
    // copy the allocator
    : alloc (a)
{
    // get memory for elements
    elem = alloc.allocate(n);

    try {
        // copy elements
        uninitialized_fill(elem, elem + n, val);
        space = last = elem + n;
    }
    catch (...) {
        // free memory
        alloc.deallocate(elem, n);
        // rethrow
        throw;
    }
}



// section 13.6.2 representing memory explicitly
template<class T, class A = allocator<T>>
// memory structure for vector
struct vector_base
{
    // allocator
    A alloc;
    // start of allocation
    T* elem;
    // end of element sequence, start of space allocated for possible expansion
    T* space;
    // end of allocated space
    T* last;

    vector_base(const A& a, typename A::size_type n)
        : alloc {a}, elem {alloc.allocate(n)}, space {elem + n}, last {elem + n}
    { }
    ~vector_base() { alloc.deallocate(elem, last - elem); }
    // no copy operations
    vector_base(const vector_base&) = delete;
    vector_base& operator=(const vector_base&) = delete;
    // move operations
    vector_vase(vector_base&&);
    vector_base& operator=(vector_base&&);
};

template<class T, class A>
vector_base<T, A>::vector_base(vector_base&& a)
    :
    alloc {a.alloc},
    elem {a.elem},
    space {a.space},
    last {a.last}
{
    // no longer owns any memory
    a.elem = a.space = a.last = nullptr;
}

template<class T, class A>
vector_base<T, A>::& vector_base<T, A>::operator=(vector_base&& a)
{
    swap(*this, a);
    return *this;
}

template<class T, class A = allocator<T>>
class vector {
    // the data is here
    vector<T, A> vb;
    void destroy_element s();
public :
    using size_type = unsigned int;
    explicit vector(size_type n, const T& val = T (), const A& = A ());
    // copy constructor
    vector(const vector& a);
    // copy assignment
    vector& operator=(const vector& a);
    // move constructor
    vector(vector&& a);
    // move assignment
    vector& operator=(vector&& a);
    // destructor
    ~vector() { destroy_element s(); }

    size_type size() const { return vb.space - vb.elem; }
    size_type capacity() const { return vb.last - vb.elem; }

    // increse capacity
    void reserve(size_type);
    // change the number of elements
    void resize(size_type, T = {});
    // make the vector empty
    void clear() { resize(0); }
    // add an element at the end
    void push_back(const T&);
    // ...
};

template<class T, class A>
void vector<T, A>::destroy_elements()
{
    for (T* p = vb.elem; p != vb.space; ++p) {
        // destroy element
        p->~T();
    }
    vb.space = vb.elem;
}

template<class T, class A>
vector<T, A>::vector(size_type n, const T& val, const A& a)
    // allocate space for n elements
    : vb {a, n};
{
    // make n copies of val
    uninitialized_fill(vb.elem, vb.elem + n, val);
}

// copy constructor
template<class T, class A>
vector<T, A>::vector(const vector<T, A>& a)
    : vb {a.alloc, a.size()}
{
    uninitialized_copy(a.begin(), a.end(), vb.elem);
}

// move constructor
template<class T, class A>
vector<T, A>::vector(vector&& a)
    // transfer ownership
    : vb {move(a.vb)}
{
}

// move assignment
template<class T, class A>
vector<T, A>::& vector<T, A>::operator=(vector&& a)
{
    // destroy elements
    clear();
    // transfer ownership
    swap(*this, a);
}



// section : 13.6.3 assignment
// offers the strong guarantee
template<class T, class A>
vector<T, A>& vector<T, A>::operator=(const vector& a)
{
    // get memory
    vector_base<T, A> b(alloc, a.size());
    // copy elements
    uninitialized_copy(a.begin, a.end(), b.elem);
    // destroy old elements
    destroy_elements();
    // transfer ownership
    swap(vb, b);
    // implicitly destroy the old value
    return *this;
}


// offers the strong guarantee
template<class T, class A>
vector<T, A>& vector<T, A>::operator=(const vector& a)
{
    // copy allocator
    vector temp {a};
    // swap representation
    std::swap(*this, temp);
    return *this;
}


// optimized basic guarantee only
template<class T, class A>
vector<T, A>& vector<T, A>::operator=(const vector& a)
{
    // allocate new vector representation
    if (capacity() < a.size()) {
        // copy allocator
        vector temp {a};
        // swap representations
        swap(*this, temp);
        // implicitly destroy the old value
        return *this;
    }

    // optimize self assignment
    if (this == &a) return *this;

    size_type sz = size();
    size_type asz = a.size();
    // copy the allocator
    vb.alloc = a.vb.alloc;
    if (asz <= sz) {
        copy(a.begin(), a.begin() + asz, vb.elem);
        // destroy surplus elements
        for (T* p = vb.elem + asz; p != vb.space; ++p) {
            p->~T();
        }
    }
    else {
        copy(a.bein(), a.begin() + sz, vb.elem);
        // construct extra elements
        uninitialized_copy(a.begin() + sz, a.end(), vb.space)
    }
    vb.space = vb.elem + asz;
    return *this;
}


// simple a = b
template<class T, class A>
void safe_assign(vector<T, A>& a, const vector<T, A>& b)
{
    // copy the elements of b into a temporary
    vector<T, A> temp {b};
    swap(a, temp);
}

// simple a = b, (note : b is passen by value
template<class T, class A>
void safe_assign(vector<T, A>& a, vector<T, A> b)
{
    swap(a, b);
}



// section 13.6.4 : changing size
// flawed first attempt
template<class T, class A>
void vector<T, A>::reserve(size_type newalloc)
{
    // never decrease allocation
    if (newalloc <= capacity) {
        return;
    }
    // make a vector with the new capacity
    vector<T, A> v(capacity());
    // copy elements
    copy(elem, elem + size(), v.begin());
    // install new value
    swap(*this v);
}   // implicitly release old

template<class T, class A>
void vector<T, A>::reserve(size_type newalloc)
{
    // never decrease allocation
    if (newalloc <= capacity()) {
        return;
    }
    // get new space
    vector_base<T, A> b {vb.alloc, newalloc};
    // move elements
    uninitialized_move(elem, elem + size(), b.elem);
    // install new base
    swap(vb, b);
}   // implicitly release old space


template<typename In, typename Out>
Out uninitialized_move(In b, In e, Out oo)
{
    for ( ; b != e; ++b, ++oo) {
        // move construct
        new (static_cast<void*>(&*oo)) T {move(*b)};
        // destroy
        b->~T();
    }
    return b;

}


// resize
template<class T, class A>
void vector<T, A>::resize(size_type newsize, const T& val)
{
    reserve(newsize);
    if (size() < newsize) {
        // construct new elements : [size(), newsize)
        uninitialized_fill(elem + size(), elem + newsize, val);
    }
    else {
        // destroy surplus elements : [newsize : size())
        destroy(elem + size(), elem + newsize);
    }
}

// destroy function
template<typename In>
void destroy(In b, In e)
{
    // destroy [b : e)
    for ( ; b != e; ++b) {
        b->~T();
    }
}


// push_back()
template<class T, class A>
void vector<T, A>::push_back(const T& val)
{
    // no more free space; relocate
    if (capacity() == size()) {
        // grow or start with 8
        reserve(sz ? 2 * sz : 8);
    }
    // add val at end
    vb.alloc.construct(&vb.elem[size()], val);
    // increment size
    ++vb.space;
}

