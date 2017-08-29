/**************************************************************
* Name     :  ex11-1-3.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年5月10日
**************************************************************/



/*
example 11.2 : free store
*/


#include <iostream>

using namespace std;


struct Enode {
    Token_value oper;
    Enode* left;
    Enode* right;
    // ...
};

Enode* expr(bool get)
{
    Enode* left = term(get);

    for ( ; ; ) {
        switch (ts.current().kind) {
            case Kind::plus :
            case Kind::minus :
                left = new Enode {ts.current().kind, left, term(true)};
                break;
            default :
                // return node
                return left;
        }
    }
}


// code generator
void generate(Enode* n)
{
    switch (n->oper) {
        case Kind::plus :
            // use n
            // delete an Enode from the free store
            delete n;
    }
}


// very bad code
int* p1 = new int {99};
// potential trouble
int* p2 = p1;
// now p2 doesn't point to a valid object
delete p1;
// gives a false sense of safety
p1 = nullptr;
// p3 may now point to the memory pointed to by p2
char* p3 = new char {'x'};
// this may cause trouble
*p2 = 999;
// may not print x
cout << *p3 << '\n';


// very bad code
void sloppy()
{
    // acquire memory
    int* p = new int[1000];
    // ... use *p ...
    // release memory
    delete[] p;
    // ... wait a while ...
    // but sloppy() does not own *p
    delete[] p;
}


void f(const string& s)
{
    vector<char> v;
    for (auto c : s) {
        v.push_back(c);
    }
    // ...
}


Token_stream ts {new istringstream{some_string}};

string reverse(const string& s)
{
    string ss;
    for (nt i = s.size() - 1; 0 <= i; --i) {
        ss.push_back(s[i]);
    }
    return ss;
}


void f(int n)
{
    // potential trouble
    int* p1 = new int[n];
    unique_ptr<int[]> p2 {new int[n]};
    // ...
    if (n % 2) {
        throw runtime_error("odd");
    }
    // we may never get here
    delete[] p1;
}


// section 11.2.2 : arrays
char* save_string(const char* p)
{
    char* s = new char[strlen(p) + 1];
    // copy from p to s
    strcpy(s, p);
    return s;
}

string save_string(const char* p)
{
    return string {p};
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        exit(1);
    }
    char* p = save_string(argv[1]);
    // ...
    delete[] p;
    string s = save_string(argv[1]);
}


void f(int n)
{
    // individual object
    vector<int>* p = new vector<int>(n);
    // array
    int* q = new int[n];
    // ...
    delete p;
    delete[] q;
}


void f1()
{
    X* p = new X;
    // ... use *p ...
    delete p;
}

// better
void f2()
{
    X x;
}


// section 11.2.3 : getting memory space
// allocate space for individual object
void* operator new (size_t);
// if (p) deallocate space allocated using operator new()
void operator delete(void* p);
// allocate space for array
void* operator new[](size_t);
// if (p) deallocate space allocated using operator new[]()
void operator delete[](void* p);


void f()
{
    vector<char*> v;
    try {
        for ( ; ; ) {
            // acquire some memory
            char* p =new char[10000];
            // make sure the new memory is referenced
            v.push_back(p);
            // use the new memory
            p[0] = 'x';
        }
    }

    catch (bad_alloc) {
        cerr << "Memory exhausted!\n";
    }
}


// section 11.2.4 : overloading new
class X {
public :
    X(int);
    // ...
};

// explicit placement operator
void* operator new(size_t, void *p)
{
    return p;
}

// significant address
void* buf = reinterpret_cast<void* =>(0xF00F);

// construct an X at buf
X* p2 = new(buf) X;
// invokes : operator new(sizeof(X), buf)

// place object of size sz at p
void* operator new(size_t sz, void* p) noexcept;
// place object of size sz at p
void* operator new[](size_t sz, void* p) noexcept;
// if (p) make *p invalid
void operator delete(void* p, void*) noexcept;
// if (p) make *p invalid
void operator delete[](void* p, void*) noexcept;


class Arena {
public :
    virtual void* alloc(size_t) = 0;
    virtual void free(void*) = 0;
    // ...
};

void* operator new(size_t sz, Arena* a)
{
    return a->alloc(sz);
}


extern Arena* Persistent;
extern Arena* Shared;

void g(int i)
{
    // X in persistent storage
    X* p = new(Persistent) X(i);
    // X in shared memory
    X* q = new(Shared) X(i);
    // ...
}

void destroy(X* p, Arena* a)
{
    // calldestructor
    p->~X();
    // free memory
    a->free(p);
}


void f(int n)
{
    // allocate n ints on the free store
    int* p = new(nothrow) int[n];
    // no memory available
    if (p == nullptr) {
        // handle allocation error ...
    }
    // ...
    // deallocate *p
    operator delete(nothrow, p);
}


// allocate sz bytes; return nullptr if allocation failed
void* operator new(size_t sz, const nothrow_t&) noexcept;
// deallocate space allocated by new
void operator delete(void* p, const nothrow_t&) noexcept;
// allocate sz bytes; return nullptr if allocation failed
void* operator new[](size_t sz, const nothrow_t&) noexcept;
// deallocate space allocated by new
void operator delete[](void* p, const nothrow_t&) noexcept;

