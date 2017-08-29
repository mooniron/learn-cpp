/**************************************************************
* Name     :  ex20-1-5.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年7月2日
**************************************************************/



/*
example 20.5 : access control
*/


template<class T>
class List {
public :
    void insert(T);
    T get();
    // ...
private :
    struct Link {
        T val;
        Link* next;
    }

    struct Chunk {
        enum {chunk_size = 15};
        Link v[chunk_size];
        Chunk* next;
    };

    Chunk* allocated;
    Link* free;
    Link* get_free();
    Link* head;
};


// public member functions
template<class T>
void List<T>::insert(T val)
{
    Link* lnk = get_free();
    lnk->val = val;
    lnk->next = head;
    head = lnk;
}

template<class T>
T List<T>::get()
{
    if (head == 0) {
        // Underflow is my exception class
        throw Underflow {};
    }

    Link* p = head;
    head = p->next;
    p->next = free;
    free = p;
    return p->val;
}


// private functions
template<class T>
typename List<T>::Link* List<T>::get_free()
{
    if (free == 0) {
        // ... allocate a new chunk and place its Links on the free list ...
    }
    Link* p = free;
    free = free->next;
    return p;
}

template<class T>
auto List<T>::get_free() -> Link*
{
    // ...
}


template<class T>
struct Link2 {
    T val;
    Link2* next;
};

template<class T>
class List {
private :
    Link2<T>* free;
    // ...
};


template<class T> class List;
template<class T>
class Link3 {
    // only List<T> can access Link<T>
    friend class List<T>;
    T val;
    Link3* next;
};

template<class T>
class List {
private :
    Link3<T>* free;
    // ...
};


class S {
public :
    int m1;
public :
    int m2;
};



// section 20.5.1 : protected members
class Buffer {
    // checked access
    char& operator[](int i);
    // ...
protected :
    // unchecked access
    char& access(int i);
    // ...
};

class Circular_buffer : public Buffer {
public :
    // change location and size
    void reallocate(char* p, int s);
    // ...
};

// change location and size
void Circular_buffer::reallocate(char* p, int s)
{
    // ...
    for (int i = 0; i != old_sz; ++i) {
        // no redundant checking
        p[i] = access(i);
    }
    // ...
}


void f(Buffer& b)
{
    // ok, checked
    b[3] = 'b';
    // error : Buffer::access() is protected
    b.access(3) = 'c';
}


class Buffer {
protected :
    //
    char a[128];
    // ...
};

class Linked_buffer : public Buffer {
    // ...
};

class Circular_buffer : public Buffer {
    // ...
    void f(Linked_buffer* p)
    {
        // ok : access to Circular_buffer's own protected member
        a[0] = 0;
        // error : access to protected type of different type
        p->a[0] = 0;
    }
};


// section 20.5.1 : use of protected members
// not use protected data, use protected member functions


// section 20.5.2 : access to base classes
class X : public B { /* ... */ };
class Y : protected B { /* ... */ };
class Z : private B { /* ... */ };

// B is a private base
class XX : B { /* ... */ };
// B is a public base
struct YY : B { /* ... */ };


// section 20.5.2.1 : multiple inheritance and access control
structt B {
    int m;
    static int sm;
    // ...
};

class D1 : public virtual B { /* ... */ };
class D2 : public virtual B { /* ... */ };
class D12 : public D1, private D2 { /* ... */ };

D12* pd = new D12;
// ok : accessible through D1
B* pb = pd;
// ok : accessible through D1
int i1 = pd->m;

class X1 : public B { /* ... */ };
class X2 : public B { /* ... */ };
class XX : public X1, public X2 { /* ... */ };

XX* pxx = new XX;
// error, ambiguous, XX::X1::B::m or XX::X2::B::m
int i1 = pxx->m;
// ok : there is only one B::sm in an XX (sm is a static member)
int i2 = pxx->sm;


// section 20.5.3 : using-declarations and access control
class B {
private :
    int a;
protected :
    int b;
public :
    int c;
};

class D : public B {
public :
    // error : B::a is private
    using B::a;
    // make B::b publicly available through D
    using B::b;
};

class BB : private B {
    // give access to B::b and B::c, but not B::a
public :
    using B::b;
    using B::c;
};

