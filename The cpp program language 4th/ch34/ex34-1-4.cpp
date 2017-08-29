/**************************************************************
* Name     :  ex34-1-4.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年8月6日
**************************************************************/



/*
example 34.4: allocators
*/



// acquire space for n objects of type T
p = a.allocate(n);
// release space for n objects of type T pointed to by p
a.deallocate(p, n);

template<typename T>
struct Simple_alloc {
    // use new[] and delete[] to allocate and deallocate bytes
    using value_type = T;
    Simple_alloc() { }

    T* allocate(size_t n)
    {
        return reinterpret_cast<T*>(new char[n * sizeof(T)]);
    }
    void deallocate(T* p, size_t n)
    {
        delete[] reinterpret_cast<char*>(p);
    }

    // ...
};


class Arena {
    void* p;
    int s;
public:
    // allocate from p[0..ss-1]
    Arena(void* pp, int ss);
};

template<typename T>
struct My_alloc {
    // use an Area to allocate and deallocate bytes
    Arena& a;
    My_alloc(Arena& aa) : a(aa) { }
    // usual allocator stuff
    My_alloc() { }
};

constexpr int sz {100000};
Arena my_arenal{new char[sz], sz};
Arena my_arena2{new char[10*sz], 10*sz};

// allocate using default allocator
vector<int> v0;
// construct in my_arenal
vector<int, My_alloc<int>> v1 {My_alloc<int>{my_arena1}};
// construct in my_arena2
vector<int, My_alloc<int>> v2 {My_alloc<int>{my_arena2}};
// construct on free store
vector<int, Simple_alloc<int>> v3;

template<typename vec>
using Arena_vec = std::vector<T, My_alloc<T>>;
template<typename T>
using Simple_vec = std::vector<T, Simple_alloc<T>>;

// named allocator object
My_alloc<int> Alloc2 {my_arena2};
// explicit allocator
Arena_vec<complex<double>> vcd {{{1, 2}, {3, 4}}, Alloc2};
// default allocator
Simple_vec<string> vs {"Sam Vimed", "Fred Colon>", "Nobby Nobbs"};


// section 34.4.1: the default allocator
template<typename T>
class allocator {
public:
    using size_type = size_t;using difference_type = ptrdiff_t;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;
    using value_type = T;

    template<typename U>
    struct rebind { using other = allocator<U>; };

    allocator() noexcept;
    allocator(const allocator&) noexcept;
    template<typename U>

    allocator(const allocator<U>&) noexcept;
    ˜allocator();

    pointer address(reference x) const noexcept;
    const_pointer address(const_reference x) const noexcept;

    // allocate n bytes
    pointer allocate(size_type n, allocator<void>::const_pointer hint = 0);
    // deallocate n bytes
    void deallocate(pointer p, size_type n);

    size_type max_siz e() const noexcept;

    // new(p) U{args}
    template<typename U, typename ... Args>
    void construct(U* p, Args&&... args);

    // p->~U()
    template<typename U>
    void destroy(U* p);
};

template<typename U>
using other = allocator<U>;

using Link_alloc = typename A::template rebind<Link>::other;

template<typename T, typename A = allocator<T>>
class list {
private:
    class Link { /* ... */ };
    // allocator<Link>
    using Link_alloc = typename A::template rebind<Link>::other;

    // link allocator
    Link_alloc a;
    // list allocator
    A alloc;
    // ...
};


// specialization
template<>
class allocator<void> {
public:
    typedef void* pointer;
    typedef const void* const_pointer;
    typedef void value_type;
    template<typename U>
    struct rebind { typedef allocator<U> other; };
};


// section 34.4.2: allocator traits

template<typename A>
struct allocator_traits {
    using allocator_type = A;
    using value_type = A::value_type;
    using pointer = value_type;
    using const_pointer = Pointer_traits<pointer>::rebind<const value_type>;
    using void_pointer = Pointer_traits<pointer>::rebind<void>;
    using const_void_pointer = Pointer_traits<pointer>::rebind<const void>;
    using difference_type = Pointer_traits<pointer>::difference_type;
    using size_type = Make_unsigned<difference_type>;
    using propagate_on_container_copy_assignment = false_type;
    using propagate_on_container_move_assignment = false_type;
    using propagate_on_container_swap = false_type;

    template<typename T> using rebind_alloc = A<T,Args>;
    template<typename T> using rebind_traits = Allocator_traits<rebind_alloc<T>>;

    static pointer allocate(A& a, size_type n) { return a.allocate(n); }
    static pointer allocate(A& a, size_type n, const_void_pointer hint)
    { return a.allocate(n,hint); }
    static void deallocate(A& a, pointer p, size_type n) { a.deallocate(p, n); }

    template<typename T, typename ... Args>
    static void construct(A& a, T* p, Args&&... args)
    { ::new (static_cast<void*>(p)) T(std::forward<Args>(args)...); }

    template<typename T>
    static void destroy(A& a, T* p) { p−>T(); }

    static size_type max_size(const A& a)
    { return numeric_limits<siz e_type>::max() }
    static A select_on_container_copy_construction(const A& rhs) { return a; }
};


// section 34.4.3: pointer traits
template<typename T>
struct pointer_traits {
    using pointer = P;
    using element_type = T;
    using difference_type = ptrdiff_t;

    template<typename U>
    using rebind = T*;

    static pointer pointer_to(a);
};

template<typename T>
struct pointer_traits<T*> {
    using pointer = T*;
    using element_type = T;
    using difference_type = ptrdiff_t;

    template<typename U>
    using rebind = U*;

    static pointer pointer_to(x) noexcept
    {
        return addressof(x);
    }
};


// section 34.4: scoped allocators
template<typename OuterA, typename InnerA>
class scoped_allocator_adaptor : public OuterA {
private:
    using Tr = allocator_traits<OuterA>;
public:
    using outer_allocator_type = OuterA;
    using inner_allocator_type = see below;
    using value_type = typename Tr::value_type;
    using size_type = typename Tr::size_type;
    using difference_type = typename Tr::difference_type;
    using pointer = typename Tr::pointer;
    using const_pointer = typename Tr::const_pointer;
    using void_pointer = typename Tr::void_pointer;
    using const_void_pointer = typename Tr::const_void_pointer;
    using propagate_on_container_copy_assignment = //...;
    using propagate_on_container_move_assignment = //...;
    using propagate_on_container_swap = // ...;
    // ...
};


// vector and string use their own (the default) allocator
using svec0 = vector<string>;
svec0 v0;

// vector (only) uses My_alloc and string uses its own allocator (the default):
using Svec1 = vector<string, My_alloc<string>>;
Svec1 v1 {My_alloc<string>{my_arena1}};

// vector and string use My_alloc (as above)
using Xstring = basic_string<char, char_traits<char>, My_alloc<char>>;
using Svec2 = vector<Xstring, scoped_allocate_adaptor<My_alloc<Xstring>>>;
Svec2 v2 {scoped_allocator_adaptor<My_alloc<Xstring>>{my_arena1}};

// vector uses its own allocator (the default) and string uses My_alloc
using Xstring2 = basic_string<char, char_traits<char>, My_alloc<char>>;
using Svec3 = vector<Xstring2, scoped_allocator_adaptor<My_alloc<Xstring>, My_alloc<char>>>;
Svec3 v3 {scoped_allocator_adaptor<My_alloc<Xstring2>, My_alloc<char>>{my_arena1}};

