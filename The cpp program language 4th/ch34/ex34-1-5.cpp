/**************************************************************
* Name     :  ex34-1-5.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年8月8日
**************************************************************/



/*
example 34.5: the garbage collection interface
*/



int* p = new int[100];
p += 10;
// ... collector may run here
p -= 10;
// can we be sure that the int is still there?
*p = 10;

int* p = new int;
// not even portable
int x = reinterpret_cast<int>(p);
p = null ptr;
// collector may run here
p = reinterpret_cast<int*>(x);
// can we be sure that the int is still there?
*p = 10;

int* p = new int;
cout << p;
p = nullptr;
// ... collector may run here...
cin >> p;
// can we be sure that the int is still there?
*p = 10;

using Link = pair<Value, long>;

long xor(Link* pre, Link* suc)
{
    static_assert(sizeof(Link*) <= sizeof(long), "a long is smaller than a pointer");
    return long{pre} ^ long{suc};
}

void insert_between(Value val, Link* pre, Link* suc)
{
    Link* p = new Link{val, xor(pre, suc)};
    pre->second = xor(xor(pre->second, suc), p);
    suc->second = xor(p, xor(suc->second, pre));
}


// the object pointed to by p must not be collected
void declare_reachable(void* p);
// undo a declare_reachable()
template<typename T>
T* undeclare_reachable(T* p);

// p[0:n) holds no pointers
void declare_no_pointers(char* p, size_t n);
// undo a declare_no_pointers()
void undeclare_no_pointers(char* p, size_t n);

enum class pointer_safety {relaxed, preferred, strict};
pointer_safety get_pointer_safety();

