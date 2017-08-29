/**************************************************************
* Name     :  ex34-1-3.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年8月6日
**************************************************************/



/*
example 34.3: resource management pointers
*/



// section 34.3.1: unique_ptr
template<typename T, typename D = default_delete<T>>
class unique_ptr {
public:
    // type of the contained pointer
    // ptr is D::pointer if that is defined, otherwise T*
    using = pointer = ptr;
    using element_type = T;
    using deleter_type = D;
    // ...
};

unique_ptr<int[]> make_sequence(int n)
{
    unique_ptr<int[]> p {new int[n]};
    for (int i = 0; i < n; ++i) {
        p[i] = i;
    }
    return p;
}

// specialization for arrays
// the default D = default_deleter<T> comes from the general unique_ptr
template<typename T, typename D>
class unique_ptr<T[], D> {
public:
    // ... like the unique_ptr for individual objects, but with [] instead of * and -> ...
};

class Shape {
    // ...
};

class Circle : public Base {
    // ...
};

// ok
unique_ptr<Shape> ps {new Circle{p, 20}};
// error
unique_ptr<Shape[]> pa {new Circle[] {Circle{p, 20}, Circle{p2, 40}}};


unique_ptr<int> f(unique_ptr<int> p)
{
    ++*p;
    return p;
}

void f2(const unique_ptr<int>& p)
{
    ++*p;
}

void use()
{
    unique_ptr<int> p {new int{7}};
    // error: no copy constructor
    p = f(p);
    // transfer ownership there and back
    p = f(move(p));
    // pass a reference
    f2(p);
}

// get data from C program fragment
extern "C" char* get_data(const char* data);

using PtoCF = void(*)(void*);

void test()
{
    unique_ptr<char, PtoCF> p {get_data("my_data"), free};
    // ... use *p ...
}   // implicit free(p)

// default deleter version
template<typename T, typename... Args>
unique_ptr<T> make_unique(Args&&... args)
{
    return unique_ptr<T>{new T{args...}};
}


// section 34.3.2: shared_ptr
struct Node {
    vector<Node*> edges;
    // ...
};

struct Node {
    vector<shared_ptr<Node>> edges;
    thread worker;
    // ...
};


struct S {
    int i;
    string s;
    double d;
    // ...
};

auto p = make_shared<S>(1, "Ankh Morpork", 4.65);



// section 34.3.3: weak_ptr
template<typename T>
class weak_ptr {
public:
    using element_type = T;
    // ...
};


void owner()
{
    // ...
    vector<shared_ptr<Asteroid>> va(100);
    for (int i = 0; i < va.size(); ++i) {
        // ... calculate neighbors for new asteroid
        va[i].reset(new Asteroid(weak_ptr<Asteroid>(va[neighbor])));
        launch(i);
    }
    // ...
}

void collision(weak_ptr<Asteroid> p)
{
    if (auto q = p.lock()) {
        // ... p.lock returns a shared_ptr to p's object
        // that Asteroid still existed: calculate ...
    }
    else {
        // Oops: that Asteroid has already been destroyed
        p.reset();
    }
}

